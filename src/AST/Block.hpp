#pragma once
#include "AST.hpp"
class ASTExpr : public ASTnode {
  public:
    ASTExpr(Span p);
    virtual ~ASTExpr();
};
class ASTBlock : public ASTExpr {
  public:
    ASTBlock(Span p);
    virtual ~ASTBlock();
};