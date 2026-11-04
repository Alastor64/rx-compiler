#include "Crate.hpp"
#include "AST.hpp"
#include "FuncDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
#include "Struct.hpp"
#include <any>
any MyParserVisitor::visitItem(RxParser::ItemContext *ctx) {
    if (ctx->functionDefinition())
        return ctx->functionDefinition()->accept(this);
    if (ctx->structDefinition())
        return ctx->structDefinition()->accept(this);
}
ASTCrate::~ASTCrate() {
    for (auto &i : funcs) {
        delete i;
        i = nullptr;
    }
    for (auto &i : structs) {
        delete i;
        i = nullptr;
    }
}
std::any MyParserVisitor::visitCrate(RxParser::CrateContext *ctx) {
    ASTCrate *res = new ASTCrate(Span::getRuleSpan(ctx)); // 含EOF
    for (auto &i : ctx->item()) {
        ASTnode *tmp = ASTtool::unpack<ASTnode>(i->accept(this));
        if (auto val = dynamic_cast<ASTFuncDef *>(tmp)) {
            res->funcs.push_back(val);
        }
        if (auto val = dynamic_cast<ASTStruct *>(tmp)) {
            res->structs.push_back(val);
        }
    }
    return ASTtool::pack(res);
}