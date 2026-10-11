#pragma once
#include "AST.hpp"
#include "Expr.hpp"
class ASTBlock : public ASTExpr {
  public:
    using ASTExpr::ASTExpr;
    virtual ~ASTBlock();
};