#include "Block.hpp"
#include "AST.hpp"
#include "Expr.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
#include "Type.hpp"
#include <any>
#include <string>
#include <utility>
ASTLet::ASTLet(Span p) : ASTnode(p) {
    if_mut = 0;
    type = nullptr;
    expr = nullptr;
}
ASTLet::~ASTLet() {
    delete type;
    delete expr;
    type = nullptr;
    expr = nullptr;
}
ASTStatement::ASTStatement(Span p) : ASTnode(p) {
    let = nullptr;
    expr = nullptr;
    if_semi = 0;
}
ASTStatement::~ASTStatement() {
    delete let;
    delete expr;
    let = nullptr;
    expr = nullptr;
}
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
        auto tmp = ASTtool::unpack<ASTStatement>(i->accept(this));
        if (tmp)
            res->statement.push_back(tmp);
    }
    if (ctx->statementExpression())
        res->tail =
            ASTtool::unpack<ASTExpr>(ctx->statementExpression()->accept(this));
    return ASTtool::pack(res);
}
any MyParserVisitor::visitStatement(RxParser::StatementContext *ctx) {
    ASTStatement *res = new ASTStatement(Span::getRuleSpan(ctx));
    res->if_semi = ctx->SEMI();
    if (ctx->letStatement()) {
        res->kind = ASTStatement::LET;
        res->let = ASTtool::unpack<ASTLet>(ctx->letStatement()->accept(this));
    } else if (ctx->statementExpression()) {
        res->kind = ASTStatement::EXPR;
        res->expr =
            ASTtool::unpack<ASTExpr>(ctx->statementExpression()->accept(this));
    } else if (ctx->expressionWithBlock()) {
        res->kind = ASTStatement::EXPR;
        res->expr =
            ASTtool::unpack<ASTExpr>(ctx->expressionWithBlock()->accept(this));
    } else if (ctx->SEMI()) {
        delete res;
        return ASTtool::pack(nullptr);
    } else
        unreachable();
    return ASTtool::pack(res);
}
any MyParserVisitor::visitLetStatement(RxParser::LetStatementContext *ctx) {
    ASTLet *res = new ASTLet(Span::getRuleSpan(ctx));
    auto tmp = any_cast<std::pair<string, bool>>(
        ctx->identifierBinding()->accept(this));
    res->if_mut = tmp.second;
    res->id = tmp.first;
    if (ctx->COLON()) {
        res->type = ASTtool::unpack<ASTType>(ctx->typeRef()->accept(this));
    }
    res->expr = ASTtool::unpack<ASTExpr>(ctx->expression()->accept(this));
    return ASTtool::pack(res);
}