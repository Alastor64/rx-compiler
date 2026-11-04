#include "Struct.hpp"
#include "AST.hpp"
#include "Expr.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
#include "Type.hpp"
#include <any>
#include <vector>
ASTStruct::Derive::Derive() { sta = 0; }
ASTStruct::Derive::Derive(int _sta) { sta = _sta; }
bool ASTStruct::Derive::err() const { return sta & 1; }
bool ASTStruct::Derive::copy() const { return sta >> 1 & 1; }
bool ASTStruct::Derive::clone() const { return sta >> 2 & 1; }
bool ASTStruct::Derive::partial_eq() const { return sta >> 3 & 1; }
bool ASTStruct::Derive::eq() const { return sta >> 4 & 1; }
void ASTStruct::Derive::merge(const Derive &x) {
    if (sta & x.sta) {
        sta |= 1;
    }
    sta |= x.sta;
}
ASTStruct::ASTStruct(Span p) : ASTnode(p) {}
ASTStruct::~ASTStruct() {
    for (auto i : fields) {
        i.del();
    }
}
ASTStruct::Field::Field(Span _pos, string _name, ASTType *_type) {
    pos = _pos;
    name = _name;
    type = _type;
}
void ASTStruct::Field::del() { delete type; }
any MyParserVisitor::visitStructDefinition(
    RxParser::StructDefinitionContext *ctx) {
    ASTStruct *res = new ASTStruct(Span::getRuleSpan(ctx));
    res->name = ctx->identifier()->getText();
    for (auto i : ctx->outerAttribute()) {
        res->derive.merge(any_cast<ASTStruct::Derive>(i->accept(this)));
    }
    for (auto i : ctx->structField()) {
        res->fields.push_back(any_cast<ASTStruct::Field>(i->accept(this)));
    }
    return ASTtool::pack(res);
}
any MyParserVisitor::visitStructField(RxParser::StructFieldContext *ctx) {
    return any(ASTStruct::Field(
        Span::getRuleSpan(ctx), ctx->identifier()->getText(),
        ASTtool::unpack<ASTType>(ctx->typeRef()->accept(this))));
}
any MyParserVisitor::visitOuterAttribute(RxParser::OuterAttributeContext *ctx) {
    ASTStruct::Derive res(0);
    for (auto i : ctx->deriveName()) {
        res.merge(any_cast<ASTStruct::Derive>(i->accept(this)));
    }
    return any(res);
}
any MyParserVisitor::visitDeriveName(RxParser::DeriveNameContext *ctx) {
    int sta = 0;
    if (ctx->COPY())
        sta |= 1 << 1;
    if (ctx->CLONE())
        sta |= 1 << 2;
    if (ctx->PARTIAL_EQ())
        sta |= 1 << 3;
    if (ctx->EQ())
        sta |= 1 << 4;
    return any(ASTStruct::Derive(sta));
}