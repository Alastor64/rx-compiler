#include "Expr.hpp"
#include "AST.hpp"
ASTELiteral::ASTELiteral(Span p) : ASTExpr(p) {
    if_int = if_true = if_unit = if_false = 0;
}
ASTEArray::~ASTEArray() {
    for (auto &i : elem) {
        delete i;
        i = nullptr;
    }
}
ASTERepeat::ASTERepeat(Span p) : ASTExpr(p) { elem = len = nullptr; }
ASTERepeat::~ASTERepeat() {
    delete elem;
    delete len;
    len = elem = nullptr;
}