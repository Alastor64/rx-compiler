#include "Type.hpp"
#include "AST.hpp"
#include "MyParserVisitor.hpp"
#include "myErr.hpp"
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
    if (ctx->children.front()->getText().length() > 1) {
        ASTTRef *tmp = new ASTTRef(Span::getRuleSpan(ctx));
        tmp->inner = res;
        res = tmp;
    }
    return ASTtool::pack(res);
}