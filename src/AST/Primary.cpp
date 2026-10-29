#include "Primary.hpp"
#include "AST.hpp"
#include "Block.hpp"
#include "Expr.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "Type.hpp"
any MyParserVisitor::visitNonBlockPrimary(
    RxParser::NonBlockPrimaryContext *ctx) {
    if (ctx->literalExpression())
        return ctx->literalExpression()->accept(this);
    else if (ctx->LPAREN()) {
        if (ctx->expression())
            return ctx->expression()->accept(this);
        else
            return ASTtool::pack(new ASTEUnit(Span::getRuleSpan(ctx)));
    } else if (ctx->arrayExpression())
        return ctx->arrayExpression()->accept(this);
    else if (ctx->LBRACE()) {
        return ASTtool::pack(BuildPrimary::buildStruct(this, ctx));
    } else if (ctx->BREAK() || ctx->RETURN() || ctx->CONTINUE()) {
        return ASTtool::pack(BuildPrimary::buildBranch(this, ctx));
    } else if (ctx->pathInExpression()) {
        return ctx->pathInExpression()->accept(this);
    }
    unreachable();
    return nullptr;
}

any MyParserVisitor::visitPrimaryExpression(
    RxParser::PrimaryExpressionContext *ctx) {
    if (ctx->nonBlockPrimary())
        return ctx->nonBlockPrimary()->accept(this);
    else if (ctx->expressionWithBlock())
        return ctx->expressionWithBlock()->accept(this);
    unreachable();
    return nullptr;
}
any MyParserVisitor::visitConditionPrimary(
    RxParser::ConditionPrimaryContext *ctx) {
    if (ctx->conditionPrimaryWithoutBareBlock())
        return ctx->conditionPrimaryWithoutBareBlock()->accept(this);
    else if (ctx->blockExpression())
        return ctx->blockExpression()->accept(this);
    unreachable();
    return nullptr;
}
any MyParserVisitor::visitConditionPrimaryWithoutBareBlock(
    RxParser::ConditionPrimaryWithoutBareBlockContext *ctx) {
    if (ctx->literalExpression())
        return ctx->literalExpression()->accept(this);
    else if (ctx->pathInExpression())
        return ctx->pathInExpression()->accept(this);
    else if (ctx->LPAREN()) {
        if (ctx->expression())
            return ctx->expression()->accept(this);
        else
            return ASTtool::pack(new ASTEUnit(Span::getRuleSpan(ctx)));
    } else if (ctx->arrayExpression())
        return ctx->arrayExpression()->accept(this);
    else if (ctx->ifExpression())
        return ctx->ifExpression()->accept(this);
    else if (ctx->WHILE() || ctx->LOOP()) {
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
    } else if (ctx->BREAK() || ctx->RETURN() || ctx->CONTINUE()) {
        ASTEBranch *res = new ASTEBranch(Span::getRuleSpan(ctx));
        if (ctx->BREAK())
            res->kind = ASTEBranch::BREAK;
        if (ctx->RETURN())
            res->kind = ASTEBranch::RETURN;
        if (ctx->CONTINUE())
            res->kind = ASTEBranch::CONTINUE;
        if (ctx->conditionBreakExpression())
            res->value = ASTtool::unpack<ASTExpr>(
                ctx->conditionBreakExpression()->accept(this));
        if (ctx->conditionExpression())
            res->value = ASTtool::unpack<ASTExpr>(
                ctx->conditionExpression()->accept(this));
        return ASTtool::pack(res);
    }
    unreachable();
    return nullptr;
}