#include "Primary.hpp"
#include "AST.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "Type.hpp"
any MyParserVisitor::visitNonBlockPrimary(
    RxParser::NonBlockPrimaryContext *ctx) {
    if (ctx->literalExpression())
        return ctx->literalExpression()->accept(this);
    else if (ctx->LPAREN()) {
        if (ctx->expression())
            return ctx->expression()->accept(this);
        else
            return ASTtool::pack(new ASTEUnit(Span::getRuleSpan(ctx)));
    } else if (ctx->arrayExpression())
        return ctx->arrayExpression()->accept(this);
    else if (ctx->LBRACE()) {
        return ASTtool::pack(BuildPrimary::buildStruct(this, ctx));
    } else if (ctx->BREAK() || ctx->RETURN() || ctx->CONTINUE()) {
        return ASTtool::pack(BuildPrimary::buildBranch(this, ctx));
    } else if (ctx->pathInExpression()) {
        return ctx->pathInExpression()->accept(this);
    }
    unreachable();
}
