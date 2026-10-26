#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include "MyDef.hpp"
#include "RxParser.h"
#include <ParserRuleContext.h>
#include <tree/ParseTreeVisitor.h>
class BuildUnary {
  public:
    BuildUnary() = delete;
    template <typename T>
    static any build(antlr4::tree::ParseTreeVisitor *visitor, T *ctx) {
        if (ctx->children.size() == 1)
            return ctx->children.front()->accept(visitor);
        ASTOUnary *res = new ASTOUnary(Span::getRuleSpan(ctx));
        res->inner =
            ASTtool::unpack<ASTExpr>(ctx->children[1]->accept(visitor));
        if (ctx->unaryOperator()->MUT())
            res->if_mut = 1;
        if (ctx->unaryOperator()->ANDAND()) {
            ASTOUnary *tmp = new ASTOUnary(res->pos);
            res->pos.begin++;
            tmp->inner = res;
            tmp->if_mut = 0;
            tmp->op = res->op = "&";
            res = tmp;
        } else {
            res->op = ctx->unaryOperator()->getText();
        }
        return ASTtool::pack(res);
    }
};