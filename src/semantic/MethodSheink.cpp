#include "MethodSheink.hpp"
#include "Expr.hpp"
#include "Path.hpp"
int MethodShrink::visitOMethod(ASTOMethod *node) {
    if (node->func->args.empty()) {
        node->id = node->func->id;
        delete node->func;
        node->func = nullptr;
        return node->visitChildren(this);
    } else
        return 1;
}