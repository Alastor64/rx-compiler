#include "Expr.hpp"
#include "AST.hpp"
#include "ASTvisitor.hpp"
#include "Block.hpp"
#include "ChildrenTool.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "Path.hpp"
#include "Type.hpp"
int ASTExpr::accept(ASTvisitor *visitor) { return visitor->visitExpr(this); }
int ASTEUnit::accept(ASTvisitor *visitor) { return visitor->visitEUnit(this); }
int ASTEPath::accept(ASTvisitor *visitor) { return visitor->visitEPath(this); }
int ASTEIf::accept(ASTvisitor *visitor) { return visitor->visitEIf(this); }
int ASTEWhile::accept(ASTvisitor *visitor) {
    return visitor->visitEWhile(this);
}
int ASTEStruct::accept(ASTvisitor *visitor) {
    return visitor->visitEStruct(this);
}
int ASTELiteral::accept(ASTvisitor *visitor) {
    return visitor->visitELiteral(this);
}
int ASTEArray::accept(ASTvisitor *visitor) {
    return visitor->visitEArray(this);
}
int ASTERepeat::accept(ASTvisitor *visitor) {
    return visitor->visitERepeat(this);
}
int ASTEBranch::accept(ASTvisitor *visitor) {
    return visitor->visitEBranch(this);
}
int ASTEOperator::accept(ASTvisitor *visitor) {
    return visitor->visitOperator(this);
}
int ASTOBinary::accept(ASTvisitor *visitor) {
    return visitor->visitOBinary(this);
}
int ASTOUnary::accept(ASTvisitor *visitor) {
    return visitor->visitOUnary(this);
}
int ASTOCall::accept(ASTvisitor *visitor) { return visitor->visitOCall(this); }
int ASTOIndex::accept(ASTvisitor *visitor) {
    return visitor->visitOIndex(this);
}
int ASTOField::accept(ASTvisitor *visitor) {
    return visitor->visitOField(this);
}
int ASTOMethod::accept(ASTvisitor *visitor) {
    return visitor->visitOMethod(this);
}
int ASTOAssign::accept(ASTvisitor *visitor) {
    return visitor->visitOAssign(this);
}
int ASTOCast::accept(ASTvisitor *visitor) { return visitor->visitOCast(this); }
int ASTOShift::accept(ASTvisitor *visitor) {
    return visitor->visitOShift(this);
}

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

int ASTExpr::visitChildren(ASTvisitor *) { return 0; }

int ASTEUnit::visitChildren(ASTvisitor *) { return 0; }

int ASTEIf::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(condition, visitor);
    res |= ChildrenTool::visitChild(truestat, visitor);
    res |= ChildrenTool::visitChild(falsestat, visitor);
    return res;
}

int ASTEWhile::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(condition, visitor);
    res |= ChildrenTool::visitChild(block, visitor);
    return res;
}

int ASTEStruct::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(path, visitor);
    for (const auto &field : member)
        res |= ChildrenTool::visitChild(field.value, visitor);
    return res;
}

int ASTELiteral::visitChildren(ASTvisitor *) { return 0; }

int ASTEArray::visitChildren(ASTvisitor *visitor) {
    return ChildrenTool::visitList(elem, visitor);
}

int ASTERepeat::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(elem, visitor);
    res |= ChildrenTool::visitChild(len, visitor);
    return res;
}

int ASTEBranch::visitChildren(ASTvisitor *visitor) {
    return ChildrenTool::visitChild(value, visitor);
}

int ASTEOperator::visitChildren(ASTvisitor *) { return 0; }

int ASTOBinary::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(left, visitor);
    res |= ChildrenTool::visitChild(right, visitor);
    return res;
}

int ASTOUnary::visitChildren(ASTvisitor *visitor) {
    return ChildrenTool::visitChild(inner, visitor);
}

int ASTOCall::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(func, visitor);
    res |= ChildrenTool::visitList(args, visitor);
    return res;
}

int ASTOIndex::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(array, visitor);
    res |= ChildrenTool::visitChild(index, visitor);
    return res;
}

int ASTOField::visitChildren(ASTvisitor *visitor) {
    return ChildrenTool::visitChild(owner, visitor);
}

int ASTOMethod::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(owner, visitor);
    res |= ChildrenTool::visitChild(func, visitor);
    res |= ChildrenTool::visitList(args, visitor);
    return res;
}

int ASTOAssign::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(place, visitor);
    res |= ChildrenTool::visitChild(value, visitor);
    return res;
}

int ASTOCast::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(value, visitor);
    res |= ChildrenTool::visitChild(type, visitor);
    return res;
}

int ASTOShift::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(base, visitor);
    res |= ChildrenTool::visitChild(expo, visitor);
    return res;
}
