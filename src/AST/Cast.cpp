#include "Cast.hpp"
#include "AST.hpp"
#include "Expr.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "Path.hpp"
#include "Type.hpp"
any MyParserVisitor::visitCastExpression(RxParser::CastExpressionContext *ctx) {
    return BuildCast::build(this, ctx);
}
any MyParserVisitor::visitConditionCastExpression(
    RxParser::ConditionCastExpressionContext *ctx) {
    return BuildCast::build(this, ctx);
}
any MyParserVisitor::visitConditionBreakCastExpression(
    RxParser::ConditionBreakCastExpressionContext *ctx) {
    return BuildCast::build(this, ctx);
}
any MyParserVisitor::visitStatementCastExpression(
    RxParser::StatementCastExpressionContext *ctx) {
    return BuildCast::build(this, ctx);
}
any MyParserVisitor::visitClosedCastExpression(
    RxParser::ClosedCastExpressionContext *ctx) {
    return BuildCast::build(this, ctx);
}
any MyParserVisitor::visitConditionClosedCastExpression(
    RxParser::ConditionClosedCastExpressionContext *ctx) {
    return BuildCast::build(this, ctx);
}
any MyParserVisitor::visitConditionBreakClosedCastExpression(
    RxParser::ConditionBreakClosedCastExpressionContext *ctx) {
    return BuildCast::build(this, ctx);
}
any MyParserVisitor::visitStatementClosedCastExpression(
    RxParser::StatementClosedCastExpressionContext *ctx) {
    return BuildCast::build(this, ctx);
}
any MyParserVisitor::visitClosedCastType(RxParser::ClosedCastTypeContext *ctx) {
    if (ctx->LPAREN()) {
        if (!ctx->typeRef())
            return ASTtool::pack(new ASTTUnit(Span::getRuleSpan(ctx)));
        return ctx->typeRef()->accept(this);
    } else if (ctx->arrayType()) {
        return ctx->arrayType()->accept(this);
    } else if (ctx->AMP() || ctx->ANDAND()) {
        ASTType *inner =
            ASTtool::unpack<ASTType>(ctx->closedCastType()->accept(this));
        bool mut = ctx->MUT();
        Span p, ip;
        ip = p = Span::getRuleSpan(ctx);
        ip.begin++;
        ASTTRef *res = new ASTTRef(p);
        if (ctx->AMP()) {
            res->if_mut = mut;
            res->inner = inner;
        } else {
            ASTTRef *tmp = new ASTTRef(ip);
            tmp->if_mut = mut;
            tmp->inner = inner;
            res->inner = tmp;
            res->if_mut = 0;
        }
        return ASTtool::pack(res);
    } else if (ctx->pathIdentSegment()) {
        ASTTPath *res = new ASTTPath(Span::getRuleSpan(ctx));
        for (auto &i : ctx->typePathSegment()) {
            res->path.push_back(ASTtool::unpack<ASTPathSeg>(i->accept(this)));
        }
        ASTPathSeg *tmp =
            new ASTPathSeg(Span::getRuleSpan(ctx->pathIdentSegment()));
        tmp->id = any_cast<string>(ctx->pathIdentSegment()->accept(this));
        tmp->args =
            any_cast<vector<ASTType *>>(ctx->genericArgs()->accept(this));
        if (ctx->genericArgs())
            tmp->pos.end = Span::getRuleSpan(ctx->genericArgs()).end;
        res->path.push_back(tmp);
        return ASTtool::pack(res);
    }
    return unreachable();
}