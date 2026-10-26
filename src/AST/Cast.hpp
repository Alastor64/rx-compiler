#pragma once
#include "Expr.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "Type.hpp"
class BuildCast {
  public:
    BuildCast() = delete;
    static any build(antlr4::tree::ParseTreeVisitor *visitor,
                     antlr4::ParserRuleContext *ctx) {
        if (ctx->children.size() == 1)
            return ctx->children[0]->accept(visitor);
        Span p = Span::getRuleSpan(
            dynamic_cast<antlr4::ParserRuleContext *>(ctx->children[0]));
        ASTExpr *res =
            ASTtool::unpack<ASTExpr>(ctx->children[0]->accept(visitor));
        for (int i = 1; i < ctx->children.size(); i += 2) {
            auto e = ctx->children[i + 1];
            p.end =
                Span::getRuleSpan(dynamic_cast<antlr4::ParserRuleContext *>(e))
                    .end;
            ASTOCast *tmp = new ASTOCast(p);
            tmp->value = res;
            tmp->type = ASTtool::unpack<ASTType>(e->accept(visitor));
            tmp->op = "as";
            res = tmp;
        }
        return ASTtool::pack(res);
    }
};