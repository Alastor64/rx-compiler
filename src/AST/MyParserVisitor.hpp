#pragma once
#include "MyDef.hpp"
#include "RxParser.h"
#include "RxParserBaseVisitor.h"
#include <any>
class MyParserVisitor : public RxParserBaseVisitor {
  public:
    virtual any visitCrate(RxParser::CrateContext *ctx) override;
    virtual any visitItem(RxParser::ItemContext *ctx) override;
    virtual std::any
    visitUseDeclaration(RxParser::UseDeclarationContext *ctx) override;
    virtual std::any visitUseTree(RxParser::UseTreeContext *ctx) override;
    virtual std::any visitUsePath(RxParser::UsePathContext *ctx) override;
    virtual std::any
    visitUsePathSegment(RxParser::UsePathSegmentContext *ctx) override;
    virtual std::any
    visitFunctionDefinition(RxParser::FunctionDefinitionContext *ctx) override;

    virtual std::any
    visitIdentifierBinding(RxParser::IdentifierBindingContext *ctx) override;
    virtual std::any visitIdentifier(RxParser::IdentifierContext *ctx) override;
    virtual std::any
    visitFunctionParameters(RxParser::FunctionParametersContext *ctx) override;

    virtual std::any visitTypeRef(RxParser::TypeRefContext *ctx) override;
    virtual std::any
    visitReferenceType(RxParser::ReferenceTypeContext *ctx) override;

    virtual std::any visitArrayType(RxParser::ArrayTypeContext *ctx) override;
    virtual std::any visitTypePath(RxParser::TypePathContext *ctx) override;

    virtual std::any
    visitTypePathSegment(RxParser::TypePathSegmentContext *ctx) override;
    virtual std::any
    visitPathIdentSegment(RxParser::PathIdentSegmentContext *ctx) override;

    virtual std::any
    visitGenericArgs(RxParser::GenericArgsContext *ctx) override;

    virtual std::any visitGenericArg(RxParser::GenericArgContext *ctx) override;

    virtual std::any
    visitGenericClose(RxParser::GenericCloseContext *ctx) override;

    virtual std::any visitSelfParam(RxParser::SelfParamContext *ctx) override;

    virtual std::any
    visitFunctionParam(RxParser::FunctionParamContext *ctx) override;
    virtual any visitChildren(antlr4::tree::ParseTree *node) override;

    virtual std::any
    visitLiteralExpression(RxParser::LiteralExpressionContext *ctx) override;
};