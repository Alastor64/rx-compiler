#include "AST.hpp"
#include "Expr.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
any MyParserVisitor::visitLiteralExpression(
    RxParser::LiteralExpressionContext *ctx) {
    ASTELiteral *res = new ASTELiteral(Span::getRuleSpan(ctx));
    if (ctx->INTEGER_LITERAL()) {
        res->type = ASTELiteral::INT;
        res->int_text = ctx->INTEGER_LITERAL()->getText();
    }
    if (ctx->TRUE()) {
        res->type = ASTELiteral::BOOL;
        res->if_true = 1;
    }
    if (ctx->FALSE()) {
        res->type = ASTELiteral::BOOL;
        res->if_true = 0;
    }
    return ASTtool::pack(res);
}