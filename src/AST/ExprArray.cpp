#include "AST.hpp"
#include "Expr.hpp"
#include "MyParserVisitor.hpp"

any MyParserVisitor::visitArrayExpression(
    RxParser::ArrayExpressionContext *ctx) {
    ASTExpr *res;
    if (ctx->constValue()) {
        ASTERepeat *tmp = new ASTERepeat(Span::getRuleSpan(ctx));
        tmp->elem =
            ASTtool::unpack<ASTExpr>(ctx->expression().front()->accept(this));
        tmp->len = ASTtool::unpack<ASTExpr>(ctx->constValue()->accept(this));
        res = tmp;
    } else {
        ASTEArray *tmp = new ASTEArray(Span::getRuleSpan(ctx));
        for (auto &i : ctx->expression()) {
            tmp->elem.push_back(ASTtool::unpack<ASTExpr>(i->accept(this)));
        }
        res = tmp;
    }
    return ASTtool::pack(res);
}
