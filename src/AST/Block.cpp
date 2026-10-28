#include "Block.hpp"
#include "AST.hpp"
#include "Expr.hpp"
#include "MyParserVisitor.hpp"
ASTBlock::ASTBlock(Span p) : ASTExpr(p) { tail = nullptr; }
ASTBlock::~ASTBlock() {
    delete tail;
    tail = nullptr;
    for (auto &i : statement) {
        delete i;
        i = nullptr;
    }
}
any MyParserVisitor::visitIfExpression(RxParser::IfExpressionContext *ctx) {
    ASTEIf *res = new ASTEIf(Span::getRuleSpan(ctx));
    res->condition =
        ASTtool::unpack<ASTExpr>(ctx->conditionExpression()->accept(this));
    res->truestat =
        ASTtool::unpack<ASTBlock>(ctx->blockExpression().front()->accept(this));
    if (ctx->ELSE()) {
        if (ctx->ifExpression()) {
            res->falsestat =
                ASTtool::unpack<ASTExpr>(ctx->ifExpression()->accept(this));
        } else {
            res->falsestat = ASTtool::unpack<ASTExpr>(
                ctx->blockExpression().back()->accept(this));
        }
    }
    return ASTtool::pack(res);
}

any MyParserVisitor::visitExpressionWithBlock(
    RxParser::ExpressionWithBlockContext *ctx) {
    if (ctx->ifExpression())
        return ctx->ifExpression()->accept(this);
    if (ctx->WHILE() || ctx->LOOP()) {
        ASTEWhile *res = new ASTEWhile(Span::getRuleSpan(ctx));
        if (ctx->WHILE())
            res->kind = ASTEWhile::WHILE;
        if (ctx->LOOP())
            res->kind = ASTEWhile::LOOP;
        if (ctx->conditionExpression())
            res->condition = ASTtool::unpack<ASTExpr>(
                ctx->conditionExpression()->accept(this));
        res->block =
            ASTtool::unpack<ASTBlock>(ctx->blockExpression()->accept(this));
        return ASTtool::pack(res);
    }
    return ctx->blockExpression()->accept(this);
}

any MyParserVisitor::visitBlockExpression(
    RxParser::BlockExpressionContext *ctx) {
    ASTBlock *res = new ASTBlock(Span::getRuleSpan(ctx));
    for (auto i : ctx->statement()) {
        res->statement.push_back(
            ASTtool::unpack<ASTStatement>(i->accept(this)));
    }
    if (ctx->statementExpression())
        res->tail = ASTtool::unpack<ASTExpr>(ctx->statementExpression());
    return ASTtool::pack(res);
}
