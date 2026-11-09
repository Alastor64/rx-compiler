#include "Impl.hpp"
#include "AST.hpp"
#include "ASTvisitor.hpp"
#include "ChildrenTool.hpp"
#include "Constant.hpp"
#include "FuncDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
#include "Type.hpp"
int ASTImpl::accept(ASTvisitor *visitor) { return visitor->visitImpl(this); }

ASTImpl::ASTImpl(Span p) : ASTnode(p) { type = nullptr; }
ASTImpl::~ASTImpl() {
    delete type;
    for (auto &i : funcs) {
        delete i;
        i = nullptr;
    }
    for (auto &i : consts) {
        delete i;
        i = nullptr;
    }
}
any MyParserVisitor::visitInherentImpl(RxParser::InherentImplContext *ctx) {
    ASTImpl *res = new ASTImpl(Span::getRuleSpan(ctx));
    res->type = ASTtool::unpack<ASTType>(ctx->typeRef()->accept(this));
    for (auto i : ctx->associatedItem()) {
        ASTnode *tmp = ASTtool::unpack<ASTnode>(i->accept(this));
        if (auto val = dynamic_cast<ASTFuncDef *>(tmp)) {
            res->funcs.push_back(val);
        }
        if (auto val = dynamic_cast<ASTConstant *>(tmp)) {
            res->consts.push_back(val);
        }
    }
    return ASTtool::pack(res);
}
any MyParserVisitor::visitAssociatedItem(RxParser::AssociatedItemContext *ctx) {
    if (ctx->constantItem())
        return ctx->constantItem()->accept(this);
    if (ctx->functionDefinition())
        return ctx->functionDefinition()->accept(this);
    return ASTtool::pack(nullptr);
}

int ASTImpl::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitChild(type, visitor);
    res |= ChildrenTool::visitList(consts, visitor);
    res |= ChildrenTool::visitList(funcs, visitor);
    return res;
}
