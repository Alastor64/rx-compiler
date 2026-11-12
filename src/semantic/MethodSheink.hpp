#pragma once
#include "ASTvisitor.hpp"
class MethodShrink : public ASTvisitor {
  public:
    virtual int visitOMethod(ASTOMethod *) override;
};