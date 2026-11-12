#pragma once
#include "ASTvisitor.hpp"
#include "Expr.hpp"
// calculate constexpr value in ELiteral and OUnary
class IntUppering : public ASTvisitor {
  public:
    virtual int visitELiteral(ASTELiteral *) override;
    virtual int visitOUnary(ASTOUnary *) override;
};