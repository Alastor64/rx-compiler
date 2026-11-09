#include "Expr.hpp"
#include "AST.hpp"
#include "ASTvisitor.hpp"
#include "Block.hpp"
#include "ChildrenTool.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "Path.hpp"
#include "Type.hpp"
any ASTExpr::accept(ASTvisitor *visitor) { return visitor->visitExpr(this); }
any ASTEUnit::accept(ASTvisitor *visitor) { return visitor->visitEUnit(this); }
any ASTEPath::accept(ASTvisitor *visitor) { return visitor->visitEPath(this); }
any ASTEIf::accept(ASTvisitor *visitor) { return visitor->visitEIf(this); }
any ASTEWhile::accept(ASTvisitor *visitor) {
    return visitor->visitEWhile(this);
}
any ASTEStruct::accept(ASTvisitor *visitor) {
    return visitor->visitEStruct(this);
}
any ASTELiteral::accept(ASTvisitor *visitor) {
    return visitor->visitELiteral(this);
}
any ASTEArray::accept(ASTvisitor *visitor) {
    return visitor->visitEArray(this);
}
any ASTERepeat::accept(ASTvisitor *visitor) {
    return visitor->visitERepeat(this);
}
any ASTEBranch::accept(ASTvisitor *visitor) {
    return visitor->visitEBranch(this);
}
any ASTEOperator::accept(ASTvisitor *visitor) {
    return visitor->visitOperator(this);
}
any ASTOBinary::accept(ASTvisitor *visitor) {
    return visitor->visitOBinary(this);
}
any ASTOUnary::accept(ASTvisitor *visitor) {
    return visitor->visitOUnary(this);
}
any ASTOCall::accept(ASTvisitor *visitor) { return visitor->visitOCall(this); }
any ASTOIndex::accept(ASTvisitor *visitor) {
    return visitor->visitOIndex(this);
}
any ASTOField::accept(ASTvisitor *visitor) {
    return visitor->visitOField(this);
}
any ASTOMethod::accept(ASTvisitor *visitor) {
    return visitor->visitOMethod(this);
}
any ASTOAssign::accept(ASTvisitor *visitor) {
    return visitor->visitOAssign(this);
}
any ASTOCast::accept(ASTvisitor *visitor) { return visitor->visitOCast(this); }
any ASTOShift::accept(ASTvisitor *visitor) {
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

any ASTExpr::visitChildren(ASTvisitor *) { return {}; }

any ASTEUnit::visitChildren(ASTvisitor *) { return {}; }

any ASTEIf::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(condition, visitor);
    ChildrenTool::visitChild(truestat, visitor);
    ChildrenTool::visitChild(falsestat, visitor);
    return {};
}

any ASTEWhile::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(condition, visitor);
    ChildrenTool::visitChild(block, visitor);
    return {};
}

any ASTEStruct::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(path, visitor);
    for (const auto &field : member)
        ChildrenTool::visitChild(field.value, visitor);
    return {};
}

any ASTELiteral::visitChildren(ASTvisitor *) { return {}; }

any ASTEArray::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitList(elem, visitor);
    return {};
}

any ASTERepeat::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(elem, visitor);
    ChildrenTool::visitChild(len, visitor);
    return {};
}

any ASTEBranch::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(value, visitor);
    return {};
}

any ASTEOperator::visitChildren(ASTvisitor *) { return {}; }

any ASTOBinary::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(left, visitor);
    ChildrenTool::visitChild(right, visitor);
    return {};
}

any ASTOUnary::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(inner, visitor);
    return {};
}

any ASTOCall::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(func, visitor);
    ChildrenTool::visitList(args, visitor);
    return {};
}

any ASTOIndex::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(array, visitor);
    ChildrenTool::visitChild(index, visitor);
    return {};
}

any ASTOField::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(owner, visitor);
    return {};
}

any ASTOMethod::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(owner, visitor);
    ChildrenTool::visitChild(func, visitor);
    ChildrenTool::visitList(args, visitor);
    return {};
}

any ASTOAssign::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(place, visitor);
    ChildrenTool::visitChild(value, visitor);
    return {};
}

any ASTOCast::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(value, visitor);
    ChildrenTool::visitChild(type, visitor);
    return {};
}

any ASTOShift::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(base, visitor);
    ChildrenTool::visitChild(expo, visitor);
    return {};
}
