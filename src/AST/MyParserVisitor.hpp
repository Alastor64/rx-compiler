#pragma once
#include "MyDef.hpp"
#include "RxParser.h"
#include "RxParserBaseVisitor.h"
#include <any>
class MyParserVisitor : public RxParserBaseVisitor {
  public:
    static void unreachable();
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
    ///
    virtual std::any
    visitShiftExpression(RxParser::ShiftExpressionContext *ctx) override;
    virtual std::any visitClosedShiftExpression(
        RxParser::ClosedShiftExpressionContext *ctx) override;
    virtual std::any visitConditionShiftExpression(
        RxParser::ConditionShiftExpressionContext *ctx) override;

    virtual std::any visitConditionClosedShiftExpression(
        RxParser::ConditionClosedShiftExpressionContext *ctx) override;
    virtual std::any visitConditionBreakShiftExpression(
        RxParser::ConditionBreakShiftExpressionContext *ctx) override;

    virtual std::any visitConditionBreakClosedShiftExpression(
        RxParser::ConditionBreakClosedShiftExpressionContext *ctx) override;

    virtual std::any visitStatementShiftExpression(
        RxParser::StatementShiftExpressionContext *ctx) override;

    virtual std::any visitStatementClosedShiftExpression(
        RxParser::StatementClosedShiftExpressionContext *ctx) override;

    virtual std::any visitAssignmentExpression(
        RxParser::AssignmentExpressionContext *ctx) override;
    virtual std::any visitConditionAssignmentExpression(
        RxParser::ConditionAssignmentExpressionContext *ctx) override;
    virtual std::any visitConditionBreakAssignmentExpression(
        RxParser::ConditionBreakAssignmentExpressionContext *ctx) override;
    virtual std::any visitStatementAssignmentExpression(
        RxParser::StatementAssignmentExpressionContext *ctx) override;
    virtual std::any
    visitCastExpression(RxParser::CastExpressionContext *ctx) override;
    virtual std::any visitConditionCastExpression(
        RxParser::ConditionCastExpressionContext *ctx) override;
    virtual std::any visitConditionBreakCastExpression(
        RxParser::ConditionBreakCastExpressionContext *ctx) override;
    virtual std::any visitStatementCastExpression(
        RxParser::StatementCastExpressionContext *ctx) override;
    virtual std::any visitClosedCastExpression(
        RxParser::ClosedCastExpressionContext *ctx) override;
    virtual std::any visitConditionClosedCastExpression(
        RxParser::ConditionClosedCastExpressionContext *ctx) override;
    virtual std::any visitConditionBreakClosedCastExpression(
        RxParser::ConditionBreakClosedCastExpressionContext *ctx) override;
    virtual std::any visitStatementClosedCastExpression(
        RxParser::StatementClosedCastExpressionContext *ctx) override;

    virtual std::any
    visitClosedCastType(RxParser::ClosedCastTypeContext *ctx) override;

    virtual std::any
    visitUnaryExpression(RxParser::UnaryExpressionContext *ctx) override;
    virtual std::any visitConditionUnaryExpression(
        RxParser::ConditionUnaryExpressionContext *ctx) override;
    virtual std::any visitConditionBreakUnaryExpression(
        RxParser::ConditionBreakUnaryExpressionContext *ctx) override;
    virtual std::any visitStatementUnaryExpression(
        RxParser::StatementUnaryExpressionContext *ctx) override;

    virtual std::any
    visitPostfixExpression(RxParser::PostfixExpressionContext *ctx) override;
    virtual std::any visitConditionPostfixExpression(
        RxParser::ConditionPostfixExpressionContext *ctx) override;
    virtual std::any visitConditionBreakPostfixExpression(
        RxParser::ConditionBreakPostfixExpressionContext *ctx) override;
    virtual std::any visitStatementPostfixExpression(
        RxParser::StatementPostfixExpressionContext *ctx) override;

    virtual std::any
    visitNonBlockPrimary(RxParser::NonBlockPrimaryContext *ctx) override;

    virtual std::any
    visitIfExpression(RxParser::IfExpressionContext *ctx) override;

    virtual std::any visitExpressionWithBlock(
        RxParser::ExpressionWithBlockContext *ctx) override;

    virtual std::any
    visitBlockExpression(RxParser::BlockExpressionContext *ctx) override;

    virtual std::any visitStatement(RxParser::StatementContext *ctx) override;

    virtual std::any
    visitLetStatement(RxParser::LetStatementContext *ctx) override;
    virtual std::any visitExpression(RxParser::ExpressionContext *ctx) override;
    virtual std::any visitConditionExpression(
        RxParser::ConditionExpressionContext *ctx) override;
    virtual std::any visitConditionBreakExpression(
        RxParser::ConditionBreakExpressionContext *ctx) override;
    virtual std::any visitStatementExpression(
        RxParser::StatementExpressionContext *ctx) override;

    virtual std::any
    visitPrimaryExpression(RxParser::PrimaryExpressionContext *ctx) override;
    virtual std::any
    visitConditionPrimary(RxParser::ConditionPrimaryContext *ctx) override;
    virtual std::any visitConditionPrimaryWithoutBareBlock(
        RxParser::ConditionPrimaryWithoutBareBlockContext *ctx) override;
    virtual std::any visitConstValue(RxParser::ConstValueContext *ctx) override;
    virtual std::any visitMagnitude(RxParser::MagnitudeContext *ctx) override;
};