#pragma once
#include "AST.hpp"
#include "Expr.hpp"
class ASTBlock : public ASTExpr {
  public:
    using ASTExpr::ASTExpr;
    virtual ~ASTBlock();
};
class ASTLet : public ASTnode {};
class ASTStatement : public ASTnode {};