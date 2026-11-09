#include "Type.hpp"
#include "AST.hpp"
#include "ASTvisitor.hpp"
#include "ChildrenTool.hpp"
#include "Expr.hpp"
#include "MyParserVisitor.hpp"
#include "myErr.hpp"
any ASTType::accept(ASTvisitor *visitor) { return visitor->visitType(this); }
any ASTTRef::accept(ASTvisitor *visitor) { return visitor->visitTRef(this); }
any ASTTArray::accept(ASTvisitor *visitor) {
    return visitor->visitTArray(this);
}
any ASTTUnit::accept(ASTvisitor *visitor) { return visitor->visitTUnit(this); }
any ASTTPath::accept(ASTvisitor *visitor) { return visitor->visitTPath(this); }

ASTTRef::ASTTRef(Span p) : ASTType(p) {
    inner = nullptr;
    if_mut = 0;
}
ASTTRef::~ASTTRef() {
    delete inner;
    inner = nullptr;
}

std::any MyParserVisitor::visitTypeRef(RxParser::TypeRefContext *ctx) {
    if (ctx->children.size() == 2 && ctx->LPAREN() && ctx->RPAREN())
        return ASTtool::pack(new ASTTUnit(Span::getRuleSpan(ctx)));
    if (ctx->referenceType())
        return ctx->referenceType()->accept(this);
    if (ctx->typeRef())
        return ctx->typeRef()->accept(this);
    if (ctx->typePath())
        return ctx->typePath()->accept(this);
    if (ctx->arrayType())
        return ctx->arrayType()->accept(this);
    throw MyErr("unknown TypeRef children");
}

std::any
MyParserVisitor::visitReferenceType(RxParser::ReferenceTypeContext *ctx) {
    ASTTRef *res = new ASTTRef(Span::getRuleSpan(ctx));
    if (ctx->MUT())
        res->if_mut = 1;
    if (ctx->children.size() < 2)
        throw MyErr("unkown err in RefenceType");
    res->inner = ASTtool::unpack<ASTType>(ctx->children.back()->accept(this));
    if (ctx->ANDAND()) {
        ASTTRef *tmp = new ASTTRef(Span::getRuleSpan(ctx));
        tmp->inner = res;
        res = tmp;
    }
    return ASTtool::pack(res);
}

ASTTArray::~ASTTArray() {
    delete elem;
    delete len;
    elem = nullptr;
    len = nullptr;
}
ASTTArray::ASTTArray(Span p) : ASTType(p) {
    elem = nullptr;
    len = nullptr;
}
std::any MyParserVisitor::visitArrayType(RxParser::ArrayTypeContext *ctx) {
    ASTTArray *res = new ASTTArray(Span::getRuleSpan(ctx));
    res->elem = ASTtool::unpack<ASTType>(ctx->typeRef()->accept(this));
    res->len = ASTtool::unpack<ASTExpr>(ctx->constValue()->accept(this));
    return ASTtool::pack(res);
}

any ASTType::visitChildren(ASTvisitor *) { return {}; }

any ASTTRef::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(inner, visitor);
    return {};
}

any ASTTArray::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitChild(elem, visitor);
    ChildrenTool::visitChild(len, visitor);
    return {};
}

any ASTTUnit::visitChildren(ASTvisitor *) { return {}; }
