#include "Path.hpp"
#include "AST.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
#include "RxParserVisitor.h"
#include "Type.hpp"
#include "myErr.hpp"
#include <any>
#include <vector>

ASTPathSeg::~ASTPathSeg() {
    for (auto &i : args) {
        delete i;
        i = nullptr;
    }
}
any MyParserVisitor::visitTypePath(RxParser::TypePathContext *ctx) {
    ASTTPath *res = new ASTTPath(Span::getRuleSpan(ctx));
    for (auto &i : ctx->typePathSegment()) {
        res->path.push_back(ASTtool::unpack<ASTPathSeg>(i->accept(this)));
    }
    return ASTtool::pack(res);
}
any MyParserVisitor::visitTypePathSegment(
    RxParser::TypePathSegmentContext *ctx) {
    ASTPathSeg *res = new ASTPathSeg(Span::getRuleSpan(ctx));
    res->id = any_cast<string>(ctx->pathIdentSegment()->accept(this));
    res->args = std::move(
        any_cast<vector<ASTType *>>(ctx->genericArgs()->accept(this)));
    return ASTtool::pack(res);
}
any MyParserVisitor::visitPathIdentSegment(
    RxParser::PathIdentSegmentContext *ctx) {
    string res;
    if (ctx->SELF_TYPE())
        res = "Self";
    else if (ctx->SELF_VALUE())
        res = "self";
    else
        res = ctx->identifier()->IDENTIFIER()->getText();
    return res;
}
any MyParserVisitor::visitGenericArgs(RxParser::GenericArgsContext *ctx) {
    vector<ASTType *> res;
    for (auto &i : ctx->genericArg()) {
        res.push_back(ASTtool::unpack<ASTType>(i->accept(this)));
    }
    return std::move(res);
}
any MyParserVisitor::visitGenericArg(RxParser::GenericArgContext *ctx) {
    return ctx->typeRef()->accept(this);
}
any MyParserVisitor::visitGenericClose(RxParser::GenericCloseContext *ctx) {
    throw MyErr("visitGenericClose should not be used!");
}