#include "Constant.hpp"
#include "AST.hpp"
#include "ASTvisitor.hpp"
#include "ChildrenTool.hpp"
#include "Expr.hpp"
#include "MyParserVisitor.hpp"
#include "Type.hpp"
any ASTConstant::accept(ASTvisitor *visitor) {
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

any ASTConstant::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(type, visitor);
    ChildrenTool::visitChild(value, visitor);
    return {};
}
