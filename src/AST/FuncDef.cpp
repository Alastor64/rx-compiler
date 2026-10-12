#include "FuncDef.hpp"
#include "AST.hpp"
#include "Block.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "Param.hpp"
#include "RxParser.h"
#include "SelfParam.hpp"
#include "Type.hpp"
#include <utility>
#include <vector>
ASTFuncDef::ASTFuncDef(Span p) : ASTItem(p) {
    self = nullptr;
    block = nullptr;
    ret = nullptr;
}
ASTFuncDef::~ASTFuncDef() {
    delete self;
    delete block;
    delete ret;
    self = nullptr;
    block = nullptr;
    ret = nullptr;
    for (auto &i : params) {
        delete i;
        i = nullptr;
    }
}
any MyParserVisitor::visitFunctionDefinition(
    RxParser::FunctionDefinitionContext *ctx) {
    ASTFuncDef *res = new ASTFuncDef(Span::getRuleSpan(ctx));
    res->name = any_cast<std::string>(ctx->identifier()->accept(this));
    std::pair<ASTSelfParam *, vector<ASTParam *>> tmp(nullptr, 0);
    if (ctx->functionParameters())
        tmp = any_cast<decltype(tmp)>(ctx->functionParameters()->accept(this));
    res->self = tmp.first;
    swap(res->params, tmp.second);
    if (ctx->typeRef())
        res->ret = ASTtool::unpack<ASTType>(ctx->typeRef()->accept(this));
    else
        res->ret = new ASTTUnit(Span(res->pos.end, res->pos.end));
    res->block =
        ASTtool::unpack<ASTBlock>(ctx->blockExpression()->accept((this)));
    return ASTtool::pack(res);
}
any MyParserVisitor::visitFunctionParameters(
    RxParser::FunctionParametersContext *ctx) {
    std::pair<ASTSelfParam *, vector<ASTParam *>> tmp(nullptr, 0);
    if (ctx->selfParam())
        tmp.first =
            ASTtool::unpack<ASTSelfParam>(ctx->selfParam()->accept((this)));
    for (auto i : ctx->functionParam()) {
        tmp.second.push_back(ASTtool::unpack<ASTParam>(i->accept(this)));
    }
    return std::move(any(tmp));
}