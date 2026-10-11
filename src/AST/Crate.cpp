#include "Crate.hpp"
#include "AST.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
#include <any>
ASTCrate::~ASTCrate() {
    for (auto &i : items) {
        delete i;
        i = nullptr;
    }
}
std::any MyParserVisitor::visitCrate(RxParser::CrateContext *ctx) {
    ASTCrate *res = new ASTCrate(Span::getRuleSpan(ctx)); // 含EOF
    for (auto &i : ctx->item()) {
        ASTItem *v = ASTtool::unpack<ASTItem>(i->accept(this));
        if (v)
            res->items.push_back(v);
    }
    return ASTtool::pack(res);
}