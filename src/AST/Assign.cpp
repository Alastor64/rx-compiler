#include "Assign.hpp"
#include "MyParserVisitor.hpp"
any MyParserVisitor::visitAssignmentExpression(
    RxParser::AssignmentExpressionContext *ctx) {
    return BuildAssign::build(this, ctx);
}
any MyParserVisitor::visitConditionAssignmentExpression(
    RxParser::ConditionAssignmentExpressionContext *ctx) {
    return BuildAssign::build(this, ctx);
}
any MyParserVisitor::visitConditionBreakAssignmentExpression(
    RxParser::ConditionBreakAssignmentExpressionContext *ctx) {
    return BuildAssign::build(this, ctx);
}
any MyParserVisitor::visitStatementAssignmentExpression(
    RxParser::StatementAssignmentExpressionContext *ctx) {
    return BuildAssign::build(this, ctx);
}