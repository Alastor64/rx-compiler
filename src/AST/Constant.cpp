#include "Constant.hpp"
#include "AST.hpp"
#include "ASTvisitor.hpp"
#include "ChildrenTool.hpp"
#include "Expr.hpp"
#include "MyParserVisitor.hpp"
#include "Type.hpp"
int ASTConstant::accept(ASTvisitor *visitor) {
    return visitor->visitConstant(this);
}

ASTConstant::ASTConstant(Span p) : ASTnode(p) {
    type = nullptr;
    value = nullptr;
}
ASTConstant::~ASTConstant() {
    delete type;
    delete value;
    type = nullptr;
    value = nullptr;
}
any MyParserVisitor::visitConstantItem(RxParser::ConstantItemContext *ctx) {
    ASTConstant *res = new ASTConstant(Span::getRuleSpan(ctx));
    res->name = ctx->identifier()->getText();
    res->type = ASTtool::unpack<ASTType>(ctx->typeRef()->accept(this));
    res->value = ASTtool::unpack<ASTExpr>(ctx->constValue()->accept(this));
    return ASTtool::pack(res);
}

int ASTConstant::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(type, visitor);
    res |= ChildrenTool::visitChild(value, visitor);
    return res;
}
