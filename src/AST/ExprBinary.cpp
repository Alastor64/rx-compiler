#include "ExprBinary.hpp"
#include "MyClasses.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
const string ExprBinary::ERROP = "ERR";
any MyParserVisitor::visitMultiplicativeExpression(
    RxParser::MultiplicativeExpressionContext *ctx) {
    return ExprBinary::build(this, ctx->multiplicativeOperator(),
                             ctx->castExpression());
}
any MyParserVisitor::visitAdditiveExpression(
    RxParser::AdditiveExpressionContext *ctx) {
    return ExprBinary::build(this, ctx->additiveOperator(),
                             ctx->multiplicativeExpression());
}

any MyParserVisitor::visitLogicalOrExpression(
    RxParser::LogicalOrExpressionContext *ctx) {
    return ExprBinary::build(this, "||", ctx->logicalAndExpression());
}

any MyParserVisitor::visitLogicalAndExpression(
    RxParser::LogicalAndExpressionContext *ctx) {
    return ExprBinary::build(this, "&&", ctx->comparisonExpression());
}

any MyParserVisitor::visitComparisonExpression(
    RxParser::ComparisonExpressionContext *ctx) {
    return ExprBinary::build(this, ExprBinary::getCmpop(ctx),
                             makePtrVec(ctx->closedBitOrExpression()),
                             ctx->bitOrExpression());
}

any MyParserVisitor::visitBitOrExpression(
    RxParser::BitOrExpressionContext *ctx) {
    return ExprBinary::build(this, "|", ctx->bitXorExpression());
}

any MyParserVisitor::visitClosedBitOrExpression(
    RxParser::ClosedBitOrExpressionContext *ctx) {
    return ExprBinary::build(this, "|", ctx->bitXorExpression(),
                             makePtrVec(ctx->closedBitXorExpression()));
}

any MyParserVisitor::visitBitXorExpression(
    RxParser::BitXorExpressionContext *ctx) {
    return ExprBinary::build(this, "^", ctx->bitAndExpression());
}

any MyParserVisitor::visitClosedBitXorExpression(
    RxParser::ClosedBitXorExpressionContext *ctx) {
    return ExprBinary::build(this, "^", ctx->bitAndExpression(),
                             makePtrVec(ctx->closedBitAndExpression()));
}

any MyParserVisitor::visitBitAndExpression(
    RxParser::BitAndExpressionContext *ctx) {
    return ExprBinary::build(this, "&", ctx->shiftExpression());
}
any MyParserVisitor::visitClosedBitAndExpression(
    RxParser::ClosedBitAndExpressionContext *ctx) {
    return ExprBinary::build(this, "&", ctx->shiftExpression(),
                             makePtrVec(ctx->closedShiftExpression()));
}

any MyParserVisitor::visitClosedAdditiveExpression(
    RxParser::ClosedAdditiveExpressionContext *ctx) {
    return ExprBinary::build(this, ctx->additiveOperator(),
                             ctx->multiplicativeExpression(),
                             makePtrVec(ctx->closedMultiplicativeExpression()));
}

any MyParserVisitor::visitClosedMultiplicativeExpression(
    RxParser::ClosedMultiplicativeExpressionContext *ctx) {
    return ExprBinary::build(this, ctx->multiplicativeOperator(),
                             ctx->castExpression(),
                             makePtrVec(ctx->closedCastExpression()));
}

any MyParserVisitor::visitConditionLogicalOrExpression(
    RxParser::ConditionLogicalOrExpressionContext *ctx) {
    return ExprBinary::build(this, "||", ctx->conditionLogicalAndExpression());
}

any MyParserVisitor::visitConditionLogicalAndExpression(
    RxParser::ConditionLogicalAndExpressionContext *ctx) {
    return ExprBinary::build(this, "&&", ctx->conditionComparisonExpression());
}

any MyParserVisitor::visitConditionComparisonExpression(
    RxParser::ConditionComparisonExpressionContext *ctx) {
    return ExprBinary::build(this, ExprBinary::getCmpop(ctx),
                             makePtrVec(ctx->conditionClosedBitOrExpression()),
                             ctx->conditionBitOrExpression());
}

any MyParserVisitor::visitConditionBitOrExpression(
    RxParser::ConditionBitOrExpressionContext *ctx) {
    return ExprBinary::build(this, "|", ctx->conditionBitXorExpression());
}

any MyParserVisitor::visitConditionClosedBitOrExpression(
    RxParser::ConditionClosedBitOrExpressionContext *ctx) {
    return ExprBinary::build(
        this, "|", ctx->conditionBitXorExpression(),
        makePtrVec(ctx->conditionClosedBitXorExpression()));
}

any MyParserVisitor::visitConditionBitXorExpression(
    RxParser::ConditionBitXorExpressionContext *ctx) {
    return ExprBinary::build(this, "^", ctx->conditionBitAndExpression());
}

any MyParserVisitor::visitConditionClosedBitXorExpression(
    RxParser::ConditionClosedBitXorExpressionContext *ctx) {
    return ExprBinary::build(
        this, "^", ctx->conditionBitAndExpression(),
        makePtrVec(ctx->conditionClosedBitAndExpression()));
}

any MyParserVisitor::visitConditionBitAndExpression(
    RxParser::ConditionBitAndExpressionContext *ctx) {
    return ExprBinary::build(this, "&", ctx->conditionShiftExpression());
}

any MyParserVisitor::visitConditionClosedBitAndExpression(
    RxParser::ConditionClosedBitAndExpressionContext *ctx) {
    return ExprBinary::build(this, "&", ctx->conditionShiftExpression(),
                             makePtrVec(ctx->conditionClosedShiftExpression()));
}

any MyParserVisitor::visitConditionAdditiveExpression(
    RxParser::ConditionAdditiveExpressionContext *ctx) {
    return ExprBinary::build(this, ctx->additiveOperator(),
                             ctx->conditionMultiplicativeExpression());
}

any MyParserVisitor::visitConditionClosedAdditiveExpression(
    RxParser::ConditionClosedAdditiveExpressionContext *ctx) {
    return ExprBinary::build(
        this, ctx->additiveOperator(), ctx->conditionMultiplicativeExpression(),
        makePtrVec(ctx->conditionClosedMultiplicativeExpression()));
}

any MyParserVisitor::visitConditionMultiplicativeExpression(
    RxParser::ConditionMultiplicativeExpressionContext *ctx) {
    return ExprBinary::build(this, ctx->multiplicativeOperator(),
                             ctx->conditionCastExpression());
}

any MyParserVisitor::visitConditionClosedMultiplicativeExpression(
    RxParser::ConditionClosedMultiplicativeExpressionContext *ctx) {
    return ExprBinary::build(this, ctx->multiplicativeOperator(),
                             ctx->conditionCastExpression(),
                             makePtrVec(ctx->conditionClosedCastExpression()));
}

any MyParserVisitor::visitConditionBreakLogicalOrExpression(
    RxParser::ConditionBreakLogicalOrExpressionContext *ctx) {
    return ExprBinary::build(
        this, "||", makePtrVec(ctx->conditionBreakLogicalAndExpression()),
        ctx->conditionLogicalAndExpression());
}
any MyParserVisitor::visitConditionBreakLogicalAndExpression(
    RxParser::ConditionBreakLogicalAndExpressionContext *ctx) {
    return ExprBinary::build(
        this, "&&", makePtrVec(ctx->conditionBreakComparisonExpression()),
        ctx->conditionComparisonExpression());
}
any MyParserVisitor::visitConditionBreakComparisonExpression(
    RxParser::ConditionBreakComparisonExpressionContext *ctx) {
    return ExprBinary::build(
        this, ExprBinary::getCmpop(ctx),
        makePtrVec(ctx->conditionBreakBitOrExpression()),
        makePtrVec(ctx->conditionBreakClosedBitOrExpression()),
        makePtrVec(ctx->conditionBitOrExpression()));
}
any MyParserVisitor::visitConditionBreakBitOrExpression(
    RxParser::ConditionBreakBitOrExpressionContext *ctx) {
    return ExprBinary::build(this, "|",
                             makePtrVec(ctx->conditionBreakBitXorExpression()),
                             ctx->conditionBitXorExpression());
}
any MyParserVisitor::visitConditionBreakClosedBitOrExpression(
    RxParser::ConditionBreakClosedBitOrExpressionContext *ctx) {
    return ExprBinary::buildSC(
        this, "|", ctx->conditionBreakClosedBitXorExpression(),
        ctx->conditionBreakBitXorExpression(), ctx->conditionBitXorExpression(),
        ctx->conditionClosedBitXorExpression());
}

any MyParserVisitor::visitConditionBreakBitXorExpression(
    RxParser::ConditionBreakBitXorExpressionContext *ctx) {
    return ExprBinary::build(this, "^",
                             makePtrVec(ctx->conditionBreakBitAndExpression()),
                             ctx->conditionBitAndExpression());
}

any MyParserVisitor::visitConditionBreakClosedBitXorExpression(
    RxParser::ConditionBreakClosedBitXorExpressionContext *ctx) {
    return ExprBinary::buildSC(
        this, "^", ctx->conditionBreakClosedBitAndExpression(),
        ctx->conditionBreakBitAndExpression(), ctx->conditionBitAndExpression(),
        ctx->conditionClosedBitAndExpression());
}

any MyParserVisitor::visitConditionBreakBitAndExpression(
    RxParser::ConditionBreakBitAndExpressionContext *ctx) {
    return ExprBinary::build(this, "&",
                             makePtrVec(ctx->conditionBreakShiftExpression()),
                             ctx->conditionShiftExpression());
}

any MyParserVisitor::visitConditionBreakClosedBitAndExpression(
    RxParser::ConditionBreakClosedBitAndExpressionContext *ctx) {
    return ExprBinary::buildSC(
        this, "&", ctx->conditionBreakClosedShiftExpression(),
        ctx->conditionBreakShiftExpression(), ctx->conditionShiftExpression(),
        ctx->conditionClosedShiftExpression());
}
any MyParserVisitor::visitConditionBreakAdditiveExpression(
    RxParser::ConditionBreakAdditiveExpressionContext *ctx) {
    return ExprBinary::build(
        this, ctx->additiveOperator(),
        makePtrVec(ctx->conditionBreakMultiplicativeExpression()),
        ctx->conditionMultiplicativeExpression());
}
any MyParserVisitor::visitConditionBreakClosedAdditiveExpression(
    RxParser::ConditionBreakClosedAdditiveExpressionContext *ctx) {
    return ExprBinary::buildSC(
        this, ctx->additiveOperator(),
        ctx->conditionBreakClosedMultiplicativeExpression(),
        ctx->conditionBreakMultiplicativeExpression(),
        ctx->conditionMultiplicativeExpression(),
        ctx->conditionClosedMultiplicativeExpression());
}

any MyParserVisitor::visitConditionBreakMultiplicativeExpression(
    RxParser::ConditionBreakMultiplicativeExpressionContext *ctx) {
    return ExprBinary::build(this, ctx->multiplicativeOperator(),
                             makePtrVec(ctx->conditionBreakCastExpression()),
                             ctx->conditionCastExpression());
}

any MyParserVisitor::visitConditionBreakClosedMultiplicativeExpression(
    RxParser::ConditionBreakClosedMultiplicativeExpressionContext *ctx) {
    return ExprBinary::buildSC(this, ctx->multiplicativeOperator(),
                               ctx->conditionBreakClosedCastExpression(),
                               ctx->conditionBreakCastExpression(),
                               ctx->conditionCastExpression(),
                               ctx->conditionClosedCastExpression());
}

// any MyParserVisitor::visitStatementLogicalOrExpression(
//     RxParser::StatementLogicalOrExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }
// any MyParserVisitor::visitStatementLogicalAndExpression(
//     RxParser::StatementLogicalAndExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

// any MyParserVisitor::visitStatementComparisonExpression(
//     RxParser::StatementComparisonExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

// any MyParserVisitor::visitStatementBitOrExpression(
//     RxParser::StatementBitOrExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

// any MyParserVisitor::visitStatementClosedBitOrExpression(
//     RxParser::StatementClosedBitOrExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

// any MyParserVisitor::visitStatementBitXorExpression(
//     RxParser::StatementBitXorExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

// any MyParserVisitor::visitStatementClosedBitXorExpression(
//     RxParser::StatementClosedBitXorExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

// any MyParserVisitor::visitStatementBitAndExpression(
//     RxParser::StatementBitAndExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

// any MyParserVisitor::visitStatementClosedBitAndExpression(
//     RxParser::StatementClosedBitAndExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

// any MyParserVisitor::visitStatementAdditiveExpression(
//     RxParser::StatementAdditiveExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

// any MyParserVisitor::visitStatementClosedAdditiveExpression(
//     RxParser::StatementClosedAdditiveExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

// any MyParserVisitor::visitStatementMultiplicativeExpression(
//     RxParser::StatementMultiplicativeExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

// any MyParserVisitor::visitStatementClosedMultiplicativeExpression(
//     RxParser::StatementClosedMultiplicativeExpressionContext *ctx) {
//     return ExprBinary::build(this, , , , );
// }

any MyParserVisitor::visitStatementLogicalOrExpression(
    RxParser::StatementLogicalOrExpressionContext *ctx) {
    return ExprBinary::build(this, "||",
                             makePtrVec(ctx->statementLogicalAndExpression()),
                             ctx->logicalAndExpression());
}
any MyParserVisitor::visitStatementLogicalAndExpression(
    RxParser::StatementLogicalAndExpressionContext *ctx) {
    return ExprBinary::build(this, "&&",
                             makePtrVec(ctx->statementComparisonExpression()),
                             ctx->comparisonExpression());
}
any MyParserVisitor::visitStatementComparisonExpression(
    RxParser::StatementComparisonExpressionContext *ctx) {
    return ExprBinary::build(this, ExprBinary::getCmpop(ctx),
                             makePtrVec(ctx->statementBitOrExpression()),
                             makePtrVec(ctx->statementClosedBitOrExpression()),
                             makePtrVec(ctx->bitOrExpression()));
}
any MyParserVisitor::visitStatementBitOrExpression(
    RxParser::StatementBitOrExpressionContext *ctx) {
    return ExprBinary::build(this, "|",
                             makePtrVec(ctx->statementBitXorExpression()),
                             ctx->bitXorExpression());
}
any MyParserVisitor::visitStatementClosedBitOrExpression(
    RxParser::StatementClosedBitOrExpressionContext *ctx) {
    return ExprBinary::buildSC(
        this, "|", ctx->statementClosedBitXorExpression(),
        ctx->statementBitXorExpression(), ctx->bitXorExpression(),
        ctx->closedBitXorExpression());
}

any MyParserVisitor::visitStatementBitXorExpression(
    RxParser::StatementBitXorExpressionContext *ctx) {
    return ExprBinary::build(this, "^",
                             makePtrVec(ctx->statementBitAndExpression()),
                             ctx->bitAndExpression());
}

any MyParserVisitor::visitStatementClosedBitXorExpression(
    RxParser::StatementClosedBitXorExpressionContext *ctx) {
    return ExprBinary::buildSC(
        this, "^", ctx->statementClosedBitAndExpression(),
        ctx->statementBitAndExpression(), ctx->bitAndExpression(),
        ctx->closedBitAndExpression());
}

any MyParserVisitor::visitStatementBitAndExpression(
    RxParser::StatementBitAndExpressionContext *ctx) {
    return ExprBinary::build(this, "&",
                             makePtrVec(ctx->statementShiftExpression()),
                             ctx->shiftExpression());
}

any MyParserVisitor::visitStatementClosedBitAndExpression(
    RxParser::StatementClosedBitAndExpressionContext *ctx) {
    return ExprBinary::buildSC(this, "&", ctx->statementClosedShiftExpression(),
                               ctx->statementShiftExpression(),
                               ctx->shiftExpression(),
                               ctx->closedShiftExpression());
}
any MyParserVisitor::visitStatementAdditiveExpression(
    RxParser::StatementAdditiveExpressionContext *ctx) {
    return ExprBinary::build(
        this, ctx->additiveOperator(),
        makePtrVec(ctx->statementMultiplicativeExpression()),
        ctx->multiplicativeExpression());
}
any MyParserVisitor::visitStatementClosedAdditiveExpression(
    RxParser::StatementClosedAdditiveExpressionContext *ctx) {
    return ExprBinary::buildSC(this, ctx->additiveOperator(),
                               ctx->statementClosedMultiplicativeExpression(),
                               ctx->statementMultiplicativeExpression(),
                               ctx->multiplicativeExpression(),
                               ctx->closedMultiplicativeExpression());
}

any MyParserVisitor::visitStatementMultiplicativeExpression(
    RxParser::StatementMultiplicativeExpressionContext *ctx) {
    return ExprBinary::build(this, ctx->multiplicativeOperator(),
                             makePtrVec(ctx->statementCastExpression()),
                             ctx->castExpression());
}

any MyParserVisitor::visitStatementClosedMultiplicativeExpression(
    RxParser::StatementClosedMultiplicativeExpressionContext *ctx) {
    return ExprBinary::buildSC(
        this, ctx->multiplicativeOperator(),
        ctx->statementClosedCastExpression(), ctx->statementCastExpression(),
        ctx->castExpression(), ctx->closedCastExpression());
}