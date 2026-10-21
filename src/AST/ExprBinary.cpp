#include "ExprBinary.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
any MyParserVisitor::visitMultiplicativeExpression(
    RxParser::MultiplicativeExpressionContext *ctx) {
    return ExprBinary::build(this, ctx->multiplicativeOperator(),
                             ctx->castExpression(), nullvecptr, nullvecptr);
}
any MyParserVisitor::visitAdditiveExpression(
    RxParser::AdditiveExpressionContext *ctx) {
    return ExprBinary::build(this, ctx->additiveOperator(),
                             ctx->multiplicativeExpression(), nullvecptr,
                             nullvecptr);
}