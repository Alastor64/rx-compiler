#include "Expr.hpp"
#include "AST.hpp"
ASTELiteral::ASTELiteral(Span p) : ASTExpr(p) {
    if_int = if_true = if_unit = if_false = 0;
}