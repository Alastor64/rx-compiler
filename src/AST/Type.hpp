#pragma once
#include "AST.hpp"
class ASTType : public ASTnode {
  public:
    virtual ~ASTType();
    ASTType(Span p);
};
