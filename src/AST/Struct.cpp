#include "Struct.hpp"
#include "AST.hpp"
#include "ASTvisitor.hpp"
#include "ChildrenTool.hpp"
#include "Expr.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
#include "Type.hpp"
#include <any>
#include <vector>
int ASTStruct::accept(ASTvisitor *visitor) {
    return visitor->visitStruct(this);
}
int ASTSField::accept(ASTvisitor *visitor) {
    return visitor->visitSField(this);
}

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
    for (auto &i : _fields) {
        delete i.second;
        i.second = nullptr;
    }
    for (auto &i : _methods) {
        delete i.second;
        i.second = nullptr;
    }
    for (auto &i : _consts) {
        delete i.second;
        i.second = nullptr;
    }
    for (auto &i : fields) {
        delete i;
        i = nullptr;
    }
}
ASTSField::ASTSField(Span _pos, string _name, ASTType *_type) : ASTnode(_pos) {
    name = _name;
    type = _type;
}
ASTSField::~ASTSField() {
    delete type;
    type = nullptr;
}
any MyParserVisitor::visitStructDefinition(
    RxParser::StructDefinitionContext *ctx) {
    ASTStruct *res = new ASTStruct(Span::getRuleSpan(ctx));
    res->name = ctx->identifier()->getText();
    for (auto i : ctx->outerAttribute()) {
        res->derive.merge(any_cast<ASTStruct::Derive>(i->accept(this)));
    }
    for (auto i : ctx->structField()) {
        res->fields.push_back(ASTtool::unpack<ASTSField>(i->accept(this)));
    }
    return ASTtool::pack(res);
}
any MyParserVisitor::visitStructField(RxParser::StructFieldContext *ctx) {
    return ASTtool::pack(
        new ASTSField(Span::getRuleSpan(ctx), ctx->identifier()->getText(),
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

int ASTStruct::visitChildren(ASTvisitor *visitor) {
    int res = 0;
    res |= ChildrenTool::visitList(fields, visitor);
    res |= ChildrenTool::visitMap(_fields, visitor);
    res |= ChildrenTool::visitMap(_methods, visitor);
    res |= ChildrenTool::visitMap(_consts, visitor);
    return res;
}
int ASTSField::visitChildren(ASTvisitor *visitor) {
    return ChildrenTool::visitChild(type, visitor);
}
