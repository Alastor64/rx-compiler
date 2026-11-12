#include "IntUppering.hpp"
#include "Expr.hpp"
int IntUppering::visitELiteral(ASTELiteral *node) {
    switch (node->type) {
    case ASTELiteral::BOOL:
        break;
    case ASTELiteral::INT:
        break;
    default:
        return 1;
    }
    return 0;
}