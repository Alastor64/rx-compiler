#include "Expr.hpp"
#include "AST.hpp"
#include "MyDef.hpp"
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
ASTOBinary::ASTOBinary(Span p) : ASTEOperator(p) { left = right = nullptr; }
ASTOBinary::~ASTOBinary() {
    delete left;
    delete right;
    left = right = nullptr;
}
ASTOShift::ASTOShift(Span p) : ASTEOperator(p) { base = expo = nullptr; }
ASTOShift::~ASTOShift() {
    delete base;
    delete expo;
    base = expo = nullptr;
}
ASTOAssign::ASTOAssign(Span p) : ASTEOperator(p) { place = value = nullptr; }
ASTOAssign::~ASTOAssign() {
    delete place;
    delete value;
    place = value = nullptr;
}