#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include <vector>
class ASTLet : public ASTnode {};
class ASTStatement : public ASTnode {};
class ASTBlock : public ASTExpr {
  public:
    ASTBlock(Span);
    virtual ~ASTBlock();
    vector<ASTStatement *> statement;
    ASTExpr *tail;
};