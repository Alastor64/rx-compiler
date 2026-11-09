#include "SelfParam.hpp"
#include "ASTvisitor.hpp"
#include "AST.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
any ASTSelfParam::accept(ASTvisitor *visitor) {
    return visitor->visitSelfParam(this);
}

ASTSelfParam::ASTSelfParam(Span p) : ASTnode(p) { if_and = if_mut = 0; }
any MyParserVisitor::visitSelfParam(RxParser::SelfParamContext *ctx) {
    ASTSelfParam *res = new ASTSelfParam(Span::getRuleSpan(ctx));
    if (ctx->MUT())
        res->if_mut = 1;
    if (ctx->AMP())
        res->if_and = 1;
    return ASTtool::pack(res);
}

any ASTSelfParam::visitChildren(ASTvisitor *) { return {}; }
