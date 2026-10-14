#include "Path.hpp"
#include "AST.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
#include "Type.hpp"
#include "myErr.hpp"

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
    if (ctx->genericArgs())
        res->args =
            any_cast<vector<ASTType *>>(ctx->genericArgs()->accept(this));
    return ASTtool::pack(res);
}
any MyParserVisitor::visitPathIdentSegment(
    RxParser::PathIdentSegmentContext *ctx) {
    return ctx->getText();
}
any MyParserVisitor::visitGenericArgs(RxParser::GenericArgsContext *ctx) {
    vector<ASTType *> res;
    for (auto &i : ctx->genericArg()) {
        ASTType *tmp = ASTtool::unpack<ASTType>(i->accept(this));
        if (tmp)
            res.push_back(tmp);
    }
    return std::move(res);
}
any MyParserVisitor::visitGenericArg(RxParser::GenericArgContext *ctx) {
    if (!ctx->typeRef())
        return ASTtool::pack((ASTType *)nullptr);
    return ctx->typeRef()->accept(this);
}
any MyParserVisitor::visitGenericClose(RxParser::GenericCloseContext *ctx) {
    throw MyErr("visitGenericClose should not be used!");
}
ASTTPath::~ASTTPath() {
    for (auto &i : path) {
        delete i;
        i = nullptr;
    }
}