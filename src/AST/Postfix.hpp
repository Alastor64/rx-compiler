#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "Path.hpp"
#include "RxParser.h"
#include <ParserRuleContext.h>
#include <tree/ParseTreeVisitor.h>
#include <type_traits>
#include <vector>
class BuildPostfix {
  public:
    BuildPostfix() = delete;
    static ASTExpr *buildIndex(antlr4::tree::ParseTreeVisitor *visitor,
                               ASTExpr *left,
                               RxParser::PostfixSuffixContext *ctx) {
        ASTOIndex *res = new ASTOIndex(Span::getRuleSpan(ctx));
        res->pos.begin = left->pos.begin;
        res->array = left;
        res->index =
            ASTtool::unpack<ASTExpr>(ctx->expression()->accept(visitor));
        return res;
    }
    static ASTExpr *
    buildField([[maybe_unused]] antlr4::tree::ParseTreeVisitor *visitor,
               ASTExpr *left, RxParser::DotSuffixContext *ctx) {
        ASTOField *res = new ASTOField(Span::getRuleSpan(ctx));
        res->pos.begin = left->pos.begin;
        res->owner = left;
        res->id = ctx->identifier()->getText();
        return res;
    }
    static ASTExpr *buildMethod(antlr4::tree::ParseTreeVisitor *visitor,
                                ASTExpr *left,
                                RxParser::DotSuffixContext *ctx) {
        ASTOMethod *res = new ASTOMethod(Span::getRuleSpan(ctx));
        res->pos.begin = left->pos.begin;
        res->owner = left;
        res->func = ASTtool::unpack<ASTPathSeg>(
            ctx->pathExprSegment()->accept(visitor));
        res->args = buildArgs(visitor, ctx->callArguments());
        return res;
    }
    static ASTExpr *buildCall(antlr4::tree::ParseTreeVisitor *visitor,
                              ASTExpr *left,
                              RxParser::PostfixSuffixContext *ctx) {
        ASTOCall *res = new ASTOCall(Span::getRuleSpan(ctx));
        res->pos.begin = left->pos.begin;
        res->func = left;
        res->args = buildArgs(visitor, ctx->callArguments());
        return res;
    }

    static vector<ASTExpr *> buildArgs(antlr4::tree::ParseTreeVisitor *visitor,
                                       RxParser::CallArgumentsContext *ctx) {
        vector<ASTExpr *> tmp;
        for (auto i : ctx->expression()) {
            tmp.push_back(ASTtool::unpack<ASTExpr>(i->accept(visitor)));
        }
        return tmp;
    }

    static ASTExpr *buildSuffix(antlr4::tree::ParseTreeVisitor *visitor,
                                ASTExpr *left,
                                RxParser::PostfixSuffixContext *ctx) {
        if (ctx->LBRACKET())
            return buildIndex(visitor, left, ctx);
        else if (ctx->callArguments())
            return buildCall(visitor, left, ctx);
        else if (ctx->dotSuffix()) {
            if (ctx->dotSuffix()->identifier())
                return buildField(visitor, left, ctx->dotSuffix());
            else if (ctx->dotSuffix()->pathExprSegment())
                return buildMethod(visitor, left, ctx->dotSuffix());
        }
        MyParserVisitor::unreachable();
        return nullptr;
    }
    template <typename T>
    static any build(antlr4::tree::ParseTreeVisitor *visitor, T *ctx) {
        ASTExpr *res =
            ASTtool::unpack<ASTExpr>(ctx->children[0]->accept(visitor));
        if constexpr (std::is_same_v<
                          T, RxParser::StatementPostfixExpressionContext>) {
            if (ctx->dotSuffix()) {
                if (ctx->dotSuffix()->identifier())
                    res = buildField(visitor, res, ctx->dotSuffix());
                else if (ctx->dotSuffix()->pathExprSegment())
                    res = buildMethod(visitor, res, ctx->dotSuffix());
                else
                    MyParserVisitor::unreachable();
            }
        }
        for (auto i : ctx->postfixSuffix()) {
            res = buildSuffix(visitor, res, i);
        }
        return ASTtool::pack(res);
    }
};