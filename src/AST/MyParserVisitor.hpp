#pragma once
#include "MyDef.hpp"
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
};