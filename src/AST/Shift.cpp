#include "Shift.hpp"
any MyParserVisitor::visitShiftExpression(
    RxParser::ShiftExpressionContext *ctx) {
    return BuildShift::build(this, ctx);
}
any MyParserVisitor::visitClosedShiftExpression(
    RxParser::ClosedShiftExpressionContext *ctx) {
    return BuildShift::build(this, ctx);
}
any MyParserVisitor::visitConditionShiftExpression(
    RxParser::ConditionShiftExpressionContext *ctx) {
    return BuildShift::build(this, ctx);
}
any MyParserVisitor::visitConditionClosedShiftExpression(
    RxParser::ConditionClosedShiftExpressionContext *ctx) {
    return BuildShift::build(this, ctx);
}
any MyParserVisitor::visitConditionBreakShiftExpression(
    RxParser::ConditionBreakShiftExpressionContext *ctx) {
    return BuildShift::build(this, ctx);
}
any MyParserVisitor::visitConditionBreakClosedShiftExpression(
    RxParser::ConditionBreakClosedShiftExpressionContext *ctx) {
    return BuildShift::build(this, ctx);
}
any MyParserVisitor::visitStatementShiftExpression(
    RxParser::StatementShiftExpressionContext *ctx) {
    return BuildShift::build(this, ctx);
}
any MyParserVisitor::visitStatementClosedShiftExpression(
    RxParser::StatementClosedShiftExpressionContext *ctx) {
    return BuildShift::build(this, ctx);
}