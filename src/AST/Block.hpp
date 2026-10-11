#pragma once
#include "AST.hpp"
class ASTExpr : public ASTnode {
  public:
    using ASTnode::ASTnode;
};
class ASTBlock : public ASTExpr {
  public:
    using ASTExpr::ASTExpr;
    virtual ~ASTBlock();
};