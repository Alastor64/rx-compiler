#include "Path.hpp"
#include "AST.hpp"
#include "ASTvisitor.hpp"
#include "ChildrenTool.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
#include "Type.hpp"
#include "myErr.hpp"
#include <tree/ParseTree.h>
#include <tree/ParseTreeType.h>
any ASTPathSeg::accept(ASTvisitor *visitor) {
    return visitor->visitPathSeg(this);
}

ASTPathSeg::~ASTPathSeg() {
    for (auto &i : args) {
        delete i;
        i = nullptr;
    }
}
any MyParserVisitor::visitTypePath(RxParser::TypePathContext *ctx) {
    return BuildPath<RxParser::TypePathContext>::build(ctx, this);
}
any MyParserVisitor::visitTypePathSegment(
    RxParser::TypePathSegmentContext *ctx) {
    return BuildPathSeg<RxParser::TypePathSegmentContext>::build(ctx, this);
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
    return res;
}
any MyParserVisitor::visitGenericArg(RxParser::GenericArgContext *ctx) {
    if (!ctx->typeRef())
        return ASTtool::pack((ASTType *)nullptr);
    return ctx->typeRef()->accept(this);
}
any MyParserVisitor::visitGenericClose(RxParser::GenericCloseContext *ctx) {
    throw MyErr("visitGenericClose should not be used!");
}

any MyParserVisitor::visitPathExprSegment(
    RxParser::PathExprSegmentContext *ctx) {
    return BuildPathSeg<RxParser::PathExprSegmentContext>::build(ctx, this);
}

any MyParserVisitor::visitPathInExpression(
    RxParser::PathInExpressionContext *ctx) {
    return BuildPath<RxParser::PathInExpressionContext>::build(ctx, this);
}

ASTTPath::~ASTTPath() {
    for (auto &i : path) {
        delete i;
        i = nullptr;
    }
}
ASTEPath::~ASTEPath() {
    for (auto &i : path) {
        delete i;
        i = nullptr;
    }
}

any ASTEPath::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitList(path, visitor);
    return {};
}

any ASTPathSeg::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitList(args, visitor);
    return {};
}

any ASTTPath::visitChildren(ASTvisitor *visitor) {
    ChildrenTool::visitList(path, visitor);
    return {};
}
