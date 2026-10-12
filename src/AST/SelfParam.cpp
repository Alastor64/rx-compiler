#include "SelfParam.hpp"
#include "AST.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
ASTSelfParam::ASTSelfParam(Span p) : ASTnode(p) { if_and = if_mut = 0; }
any MyParserVisitor::visitSelfParam(RxParser::SelfParamContext *ctx) {
    ASTSelfParam *res = new ASTSelfParam(Span::getRuleSpan(ctx));
    if (ctx->MUT())
        res->if_mut = 1;
    if (ctx->AMP())
        res->if_and = 1;
    return ASTtool::pack(res);
}