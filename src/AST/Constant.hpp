#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include "Type.hpp"
struct ASTConstant : public ASTnode {
  public:
    string name;
    ASTType *type;
    ASTExpr *value;
    ASTConstant(Span);
    virtual ~ASTConstant();
};