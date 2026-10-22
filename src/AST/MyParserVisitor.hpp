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

    virtual std::any
    visitPathInExpression(RxParser::PathInExpressionContext *ctx) override;

    virtual std::any
    visitPathExprSegment(RxParser::PathExprSegmentContext *ctx) override;

    virtual std::any
    visitArrayExpression(RxParser::ArrayExpressionContext *ctx) override;

    virtual std::any visitMultiplicativeExpression(
        RxParser::MultiplicativeExpressionContext *ctx) override;
    virtual std::any
    visitAdditiveExpression(RxParser::AdditiveExpressionContext *ctx) override;

    //

    virtual std::any visitLogicalOrExpression(
        RxParser::LogicalOrExpressionContext *ctx) override;

    virtual std::any visitLogicalAndExpression(
        RxParser::LogicalAndExpressionContext *ctx) override;

    virtual std::any visitComparisonExpression(
        RxParser::ComparisonExpressionContext *ctx) override;

    virtual std::any
    visitBitOrExpression(RxParser::BitOrExpressionContext *ctx) override;

    virtual std::any visitClosedBitOrExpression(
        RxParser::ClosedBitOrExpressionContext *ctx) override;

    virtual std::any
    visitBitXorExpression(RxParser::BitXorExpressionContext *ctx) override;

    virtual std::any visitClosedBitXorExpression(
        RxParser::ClosedBitXorExpressionContext *ctx) override;

    virtual std::any
    visitBitAndExpression(RxParser::BitAndExpressionContext *ctx) override;
    virtual std::any visitClosedBitAndExpression(
        RxParser::ClosedBitAndExpressionContext *ctx) override;

    virtual std::any visitClosedAdditiveExpression(
        RxParser::ClosedAdditiveExpressionContext *ctx) override;

    virtual std::any visitClosedMultiplicativeExpression(
        RxParser::ClosedMultiplicativeExpressionContext *ctx) override;

    virtual std::any visitConditionLogicalOrExpression(
        RxParser::ConditionLogicalOrExpressionContext *ctx) override;

    virtual std::any visitConditionLogicalAndExpression(
        RxParser::ConditionLogicalAndExpressionContext *ctx) override;

    virtual std::any visitConditionComparisonExpression(
        RxParser::ConditionComparisonExpressionContext *ctx) override;

    virtual std::any visitConditionBitOrExpression(
        RxParser::ConditionBitOrExpressionContext *ctx) override;

    virtual std::any visitConditionClosedBitOrExpression(
        RxParser::ConditionClosedBitOrExpressionContext *ctx) override;

    virtual std::any visitConditionBitXorExpression(
        RxParser::ConditionBitXorExpressionContext *ctx) override;

    virtual std::any visitConditionClosedBitXorExpression(
        RxParser::ConditionClosedBitXorExpressionContext *ctx) override;

    virtual std::any visitConditionBitAndExpression(
        RxParser::ConditionBitAndExpressionContext *ctx) override;

    virtual std::any visitConditionClosedBitAndExpression(
        RxParser::ConditionClosedBitAndExpressionContext *ctx) override;

    virtual std::any visitConditionAdditiveExpression(
        RxParser::ConditionAdditiveExpressionContext *ctx) override;

    virtual std::any visitConditionClosedAdditiveExpression(
        RxParser::ConditionClosedAdditiveExpressionContext *ctx) override;

    virtual std::any visitConditionMultiplicativeExpression(
        RxParser::ConditionMultiplicativeExpressionContext *ctx) override;

    virtual std::any visitConditionClosedMultiplicativeExpression(
        RxParser::ConditionClosedMultiplicativeExpressionContext *ctx) override;

    virtual std::any visitConditionBreakLogicalOrExpression(
        RxParser::ConditionBreakLogicalOrExpressionContext *ctx) override;
    virtual std::any visitConditionBreakLogicalAndExpression(
        RxParser::ConditionBreakLogicalAndExpressionContext *ctx) override;
    virtual std::any visitConditionBreakComparisonExpression(
        RxParser::ConditionBreakComparisonExpressionContext *ctx) override;
    virtual std::any visitConditionBreakBitOrExpression(
        RxParser::ConditionBreakBitOrExpressionContext *ctx) override;
    virtual std::any visitConditionBreakClosedBitOrExpression(
        RxParser::ConditionBreakClosedBitOrExpressionContext *ctx) override;

    virtual std::any visitConditionBreakBitXorExpression(
        RxParser::ConditionBreakBitXorExpressionContext *ctx) override;

    virtual std::any visitConditionBreakClosedBitXorExpression(
        RxParser::ConditionBreakClosedBitXorExpressionContext *ctx) override;

    virtual std::any visitConditionBreakBitAndExpression(
        RxParser::ConditionBreakBitAndExpressionContext *ctx) override;

    virtual std::any visitConditionBreakClosedBitAndExpression(
        RxParser::ConditionBreakClosedBitAndExpressionContext *ctx) override;
    virtual std::any visitConditionBreakAdditiveExpression(
        RxParser::ConditionBreakAdditiveExpressionContext *ctx) override;
    virtual std::any visitConditionBreakClosedAdditiveExpression(
        RxParser::ConditionBreakClosedAdditiveExpressionContext *ctx) override;

    virtual std::any visitConditionBreakMultiplicativeExpression(
        RxParser::ConditionBreakMultiplicativeExpressionContext *ctx) override;

    virtual std::any visitConditionBreakClosedMultiplicativeExpression(
        RxParser::ConditionBreakClosedMultiplicativeExpressionContext *ctx)
        override;

    virtual std::any visitStatementLogicalOrExpression(
        RxParser::StatementLogicalOrExpressionContext *ctx) override;
    virtual std::any visitStatementLogicalAndExpression(
        RxParser::StatementLogicalAndExpressionContext *ctx) override;

    virtual std::any visitStatementComparisonExpression(
        RxParser::StatementComparisonExpressionContext *ctx) override;

    virtual std::any visitStatementBitOrExpression(
        RxParser::StatementBitOrExpressionContext *ctx) override;

    virtual std::any visitStatementClosedBitOrExpression(
        RxParser::StatementClosedBitOrExpressionContext *ctx) override;

    virtual std::any visitStatementBitXorExpression(
        RxParser::StatementBitXorExpressionContext *ctx) override;

    virtual std::any visitStatementClosedBitXorExpression(
        RxParser::StatementClosedBitXorExpressionContext *ctx) override;

    virtual std::any visitStatementBitAndExpression(
        RxParser::StatementBitAndExpressionContext *ctx) override;

    virtual std::any visitStatementClosedBitAndExpression(
        RxParser::StatementClosedBitAndExpressionContext *ctx) override;

    virtual std::any visitStatementAdditiveExpression(
        RxParser::StatementAdditiveExpressionContext *ctx) override;

    virtual std::any visitStatementClosedAdditiveExpression(
        RxParser::StatementClosedAdditiveExpressionContext *ctx) override;

    virtual std::any visitStatementMultiplicativeExpression(
        RxParser::StatementMultiplicativeExpressionContext *ctx) override;

    virtual std::any visitStatementClosedMultiplicativeExpression(
        RxParser::StatementClosedMultiplicativeExpressionContext *ctx) override;
};