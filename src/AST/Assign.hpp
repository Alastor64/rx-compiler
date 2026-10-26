#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
class BuildAssign {
  public:
    BuildAssign() = delete;
    static any build(antlr4::tree::ParseTreeVisitor *visitor,
                     antlr4::ParserRuleContext *ctx) {
        if (ctx->children.size() == 1)
            return ctx->children[0]->accept(visitor);
        Span p = Span::getRuleSpan(ctx);
        ASTOAssign *res = new ASTOAssign(p);
        res->op = dynamic_cast<antlr4::ParserRuleContext *>(ctx->children[1])
                      ->getText();
        res->place =
            ASTtool::unpack<ASTExpr>(ctx->children[0]->accept(visitor));
        res->value =
            ASTtool::unpack<ASTExpr>(ctx->children[2]->accept(visitor));
        return ASTtool::pack(res);
    }
};