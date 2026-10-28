#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include "RxParser.h"
#include "RxParserVisitor.h"
#include <tree/ParseTreeVisitor.h>
class BuildPrimary {
  public:
    BuildPrimary() = delete;
    static ASTEStruct *buildStruct(antlr4::tree::ParseTreeVisitor *visitor,
                                   RxParser::NonBlockPrimaryContext *ctx) {
        ASTEStruct *res = new ASTEStruct(Span::getRuleSpan(ctx));
        res->path =
            ASTtool::unpack<ASTEPath>(ctx->pathInExpression()->accept(visitor));
        if (ctx->structExprFields()) {
            for (auto i : ctx->structExprFields()->structExprField()) {
                res->member.push_back(ASTEStruct::Field(
                    Span::getRuleSpan(i), i->identifier()->getText(),
                    ASTtool::unpack<ASTExpr>(
                        i->expression()->accept(visitor))));
            }
        }
        return res;
    }
    static ASTEBranch *buildBranch(antlr4::tree::ParseTreeVisitor *visitor,
                                   RxParser::NonBlockPrimaryContext *ctx) {
        ASTEBranch *res = new ASTEBranch(Span::getRuleSpan(ctx));
        if (ctx->BREAK()) {
            res->kind = ASTEBranch::BREAK;

        } else if (ctx->CONTINUE()) {
            res->kind = ASTEBranch::CONTINUE;
        } else if (ctx->RETURN()) {
            res->kind = ASTEBranch::RETURN;
        }
        if (ctx->expression()) {
            res->value =
                ASTtool::unpack<ASTExpr>(ctx->expression()->accept(visitor));
        }
        return res;
    }
};