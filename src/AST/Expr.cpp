#include "Expr.hpp"
#include "AST.hpp"
#include "Block.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "Path.hpp"
#include "Type.hpp"
ASTELiteral::ASTELiteral(Span p) : ASTExpr(p) {
    if_int = if_true = if_false = 0;
}
ASTEArray::~ASTEArray() {
    for (auto &i : elem) {
        delete i;
        i = nullptr;
    }
}
ASTERepeat::ASTERepeat(Span p) : ASTExpr(p) { elem = len = nullptr; }
ASTERepeat::~ASTERepeat() {
    delete elem;
    delete len;
    len = elem = nullptr;
}
ASTOBinary::ASTOBinary(Span p) : ASTEOperator(p) { left = right = nullptr; }
ASTOBinary::~ASTOBinary() {
    delete left;
    delete right;
    left = right = nullptr;
}
ASTOShift::ASTOShift(Span p) : ASTEOperator(p) { base = expo = nullptr; }
ASTOShift::~ASTOShift() {
    delete base;
    delete expo;
    base = expo = nullptr;
}
ASTOAssign::ASTOAssign(Span p) : ASTEOperator(p) { place = value = nullptr; }
ASTOAssign::~ASTOAssign() {
    delete place;
    delete value;
    place = value = nullptr;
}
ASTOCast::ASTOCast(Span p) : ASTEOperator(p) {
    value = nullptr;
    type = nullptr;
}
ASTOCast::~ASTOCast() {
    delete value;
    delete type;
    value = nullptr;
    type = nullptr;
}
ASTOUnary::ASTOUnary(Span p) : ASTEOperator(p) {
    inner = nullptr;
    if_mut = 0;
}
ASTOUnary::~ASTOUnary() {
    delete inner;
    inner = nullptr;
}
ASTOIndex::ASTOIndex(Span p) : ASTEOperator(p) { array = index = nullptr; }
ASTOIndex::~ASTOIndex() {
    delete array;
    delete index;
    array = index = nullptr;
}
ASTOField::ASTOField(Span p) : ASTEOperator(p) { owner = nullptr; }
ASTOField::~ASTOField() {
    delete owner;
    owner = nullptr;
}
ASTOCall::ASTOCall(Span p) : ASTEOperator(p) { func = nullptr; }
ASTOCall::~ASTOCall() {
    delete func;
    func = nullptr;
    for (auto &i : args) {
        delete i;
        i = nullptr;
    }
}
ASTOMethod::ASTOMethod(Span p) : ASTEOperator(p) {
    owner = nullptr;
    func = nullptr;
}
ASTOMethod::~ASTOMethod() {
    delete owner;
    delete func;
    owner = nullptr;
    func = nullptr;
    for (auto &i : args) {
        delete i;
        i = nullptr;
    }
}
ASTEBranch::ASTEBranch(Span p) : ASTExpr(p) { value = nullptr; }
ASTEBranch::~ASTEBranch() {
    delete value;
    value = nullptr;
}
ASTEStruct::ASTEStruct(Span p) : ASTExpr(p) { path = nullptr; }
ASTEStruct::~ASTEStruct() {
    delete path;
    path = nullptr;
    for (auto &i : member) {
        i.del();
    }
}
ASTEStruct::Field::Field(Span p, const string &i, ASTExpr *v) {
    pos = p;
    id = i;
    value = v;
}
void ASTEStruct::Field::del() {
    delete value;
    value = nullptr;
}
ASTEIf::ASTEIf(Span p) : ASTExpr(p) {
    condition = falsestat = nullptr;
    truestat = nullptr;
}
ASTEIf::~ASTEIf() {
    delete condition;
    delete truestat;
    delete falsestat;
    condition = falsestat = nullptr;
}
ASTEWhile::ASTEWhile(Span p) : ASTExpr(p) {
    condition = nullptr;
    block = nullptr;
}
ASTEWhile::~ASTEWhile() {
    delete condition;
    delete block;
    condition = nullptr;
    block = nullptr;
}

any MyParserVisitor::visitExpression(RxParser::ExpressionContext *ctx) {
    return ctx->assignmentExpression()->accept(this);
}

any MyParserVisitor::visitConditionExpression(
    RxParser::ConditionExpressionContext *ctx) {
    return ctx->conditionAssignmentExpression()->accept(this);
}

any MyParserVisitor::visitConditionBreakExpression(
    RxParser::ConditionBreakExpressionContext *ctx) {
    return ctx->conditionBreakAssignmentExpression()->accept(this);
}

any MyParserVisitor::visitStatementExpression(
    RxParser::StatementExpressionContext *ctx) {
    return ctx->statementAssignmentExpression()->accept(this);
}

any MyParserVisitor::visitConstValue(RxParser::ConstValueContext *ctx) {
    if (ctx->constValue())
        return ctx->constValue()->accept(this);
    else if (ctx->pathInExpression())
        return ctx->pathInExpression()->accept(this);
    else if (ctx->INTEGER_LITERAL() || ctx->TRUE() || ctx->FALSE()) {
        ASTELiteral *res = new ASTELiteral(Span::getRuleSpan(ctx));
        if (ctx->INTEGER_LITERAL()) {
            res->if_int = 1;
            res->int_text = ctx->INTEGER_LITERAL()->getText();
        } else if (ctx->TRUE()) {
            res->if_true = 1;
        } else if (ctx->FALSE()) {
            res->if_false = 1;
        }
        return ASTtool::pack(res);
    } else if (ctx->MINUS()) {
        ASTOUnary *res = new ASTOUnary(Span::getRuleSpan(ctx));
        res->op = "-";
        res->inner = ASTtool::unpack<ASTExpr>(ctx->magnitude()->accept(this));
        return ASTtool::pack(res);
    }
    unreachable();
    return nullptr;
}
any MyParserVisitor::visitMagnitude(RxParser::MagnitudeContext *ctx) {
    if (ctx->magnitude())
        return ctx->magnitude()->accept(this);
    else if (ctx->pathInExpression())
        return ctx->pathInExpression()->accept(this);
    else if (ctx->INTEGER_LITERAL()) {
        ASTELiteral *res = new ASTELiteral(Span::getRuleSpan(ctx));
        res->if_int = 1;
        res->int_text = ctx->INTEGER_LITERAL()->getText();
        return ASTtool::pack(res);
    }
    unreachable();
    return nullptr;
}