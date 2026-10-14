#include "AST.hpp"
#include "Expr.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
any MyParserVisitor::visitLiteralExpression(
    RxParser::LiteralExpressionContext *ctx) {
    ASTELiteral *res = new ASTELiteral(Span::getRuleSpan(ctx));
    if (ctx->INTEGER_LITERAL()) {
        res->if_int = 1;
        res->integer = ctx->INTEGER_LITERAL()->getText();
    }
    if (ctx->TRUE()) {
        res->if_true = 1;
    }
    if (ctx->FALSE()) {
        res->if_false = 1;
    }
    return ASTtool::pack(res);
}