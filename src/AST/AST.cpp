#include "AST.hpp"
#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "myErr.hpp"
#include <tree/ParseTree.h>
Span::Span() { begin = end = 0; }
Span::Span(size_t b, size_t e) : begin(b), end(e) {}
Span Span::getRuleSpan(antlr4::ParserRuleContext *ctx) {
    antlr4::Token *s = ctx->getStart();
    antlr4::Token *e = ctx->getStop();
    if (!s)
        return Span();
    size_t begin = s->getStartIndex();
    size_t end;
    if (e && s->getStartIndex() <= e->getStopIndex())
        end = e->getStopIndex() + 1;
    else
        end = begin;
    return Span(begin, end);
}
Span Span::getTokenSpan(antlr4::Token *tk) {
    if (!tk)
        return Span();
    return Span(tk->getStartIndex(), tk->getStopIndex() + 1);
}
ASTnode::~ASTnode() {};
ASTnode::ASTnode(Span p) : pos(p) {};
ASTItem::~ASTItem() {};

any ASTtool::pack(ASTnode *p) { return any(p); }
any MyParserVisitor::visitItem(RxParser::ItemContext *ctx) {
    if (ctx->children.empty())
        return ASTtool::pack(nullptr);
    return ctx->children[0]->accept(this);
}
any MyParserVisitor::visitChildren(antlr4::tree::ParseTree *ctx) {
    throw MyErr("unrealized visitor");
}
void MyParserVisitor::unreachable() { throw MyErr("unreachable"); }