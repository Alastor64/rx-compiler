#pragma once
#include "AST.hpp"
#include "Type.hpp"
class ASTParam : public ASTnode {
  public:
    using ASTnode::ASTnode;
    ASTType *type;
    string name;
    bool if_mut;
};