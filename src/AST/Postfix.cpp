#include "Postfix.hpp"
#include "MyParserVisitor.hpp"
any MyParserVisitor::visitPostfixExpression(
    RxParser::PostfixExpressionContext *ctx) {
    return BuildPostfix::build(this, ctx);
}
any MyParserVisitor::visitConditionPostfixExpression(
    RxParser::ConditionPostfixExpressionContext *ctx) {
    return BuildPostfix::build(this, ctx);
}
any MyParserVisitor::visitConditionBreakPostfixExpression(
    RxParser::ConditionBreakPostfixExpressionContext *ctx) {
    return BuildPostfix::build(this, ctx);
}
any MyParserVisitor::visitStatementPostfixExpression(
    RxParser::StatementPostfixExpressionContext *ctx) {
    return BuildPostfix::build(this, ctx);
}