#pragma once
#include "Expr.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
class BuildShift {
  public:
    BuildShift() = delete;
    static any build(antlr4::tree::ParseTreeVisitor *visitor,
                     antlr4::ParserRuleContext *ctx) {
        if (ctx->children.size() == 1)
            return ctx->children[0]->accept(visitor);
        Span p = Span::getRuleSpan(
            dynamic_cast<antlr4::ParserRuleContext *>(ctx->children[0]));
        ASTExpr *res =
            ASTtool::unpack<ASTExpr>(ctx->children[0]->accept(visitor));
        for (int i = 1; i < ctx->children.size(); i += 2) {
            auto o = ctx->children[i];
            auto e = ctx->children[i + 1];
            p.end =
                Span::getRuleSpan(dynamic_cast<antlr4::ParserRuleContext *>(e))
                    .end;
            ASTOShift *tmp = new ASTOShift(p);
            tmp->base = res;
            tmp->expo = ASTtool::unpack<ASTExpr>(e->accept(visitor));
            if (dynamic_cast<antlr4::tree::TerminalNode *>(o))
                tmp->op = "<<";
            else
                tmp->op = ">>";
            res = tmp;
        }
        return ASTtool::pack(res);
    }
};