#include "Unary.hpp"
#include "MyParserVisitor.hpp"
any MyParserVisitor::visitUnaryExpression(
    RxParser::UnaryExpressionContext *ctx) {
    return BuildUnary::build(this, ctx);
}
any MyParserVisitor::visitConditionUnaryExpression(
    RxParser::ConditionUnaryExpressionContext *ctx) {
    return BuildUnary::build(this, ctx);
}
any MyParserVisitor::visitConditionBreakUnaryExpression(
    RxParser::ConditionBreakUnaryExpressionContext *ctx) {
    return BuildUnary::build(this, ctx);
}
any MyParserVisitor::visitStatementUnaryExpression(
    RxParser::StatementUnaryExpressionContext *ctx) {
    return BuildUnary::build(this, ctx);
}