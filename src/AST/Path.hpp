#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include "RxParser.h"
#include "Type.hpp"
#include <tree/ParseTreeVisitor.h>
#include <type_traits>
class ASTPathSeg : public ASTnode {
  public:
    string id;
    vector<ASTType *> args;
    using ASTnode::ASTnode;
    virtual ~ASTPathSeg();
};
template <
    typename T,
    std::enable_if_t<std::is_same_v<T, RxParser::PathExprSegmentContext> ||
                         std::is_same_v<T, RxParser::TypePathSegmentContext>,
                     int> = 0>
class BuildPathSeg {
  public:
    BuildPathSeg() = delete;
    static any build(T *ctx, antlr4::tree::ParseTreeVisitor *visitor) {
        ASTPathSeg *res = new ASTPathSeg(Span::getRuleSpan(ctx));
        res->id = any_cast<string>(ctx->pathIdentSegment()->accept(visitor));
        if (ctx->genericArgs())
            res->args = any_cast<vector<ASTType *>>(
                ctx->genericArgs()->accept(visitor));
        return ASTtool::pack(res);
    }
};
template <
    typename T,
    std::enable_if_t<std::is_same_v<T, RxParser::TypePathContext> ||
                         std::is_same_v<T, RxParser::PathInExpressionContext>,
                     int> = 0>
class BuildPath {
  public:
    BuildPath() = delete;
    using U = std::conditional_t<std::is_same_v<T, RxParser::TypePathContext>,
                                 ASTTPath, ASTEPath>;
    static any build(T *ctx, antlr4::tree::ParseTreeVisitor *visitor) {
        U *res = new U(Span::getRuleSpan(ctx));
        for (auto &i : ctx->children) {
            if (i->getTreeType() == antlr4::tree::ParseTreeType::RULE)
                res->path.push_back(
                    ASTtool::unpack<ASTPathSeg>(i->accept(visitor)));
        }
        return ASTtool::pack(res);
    }
};