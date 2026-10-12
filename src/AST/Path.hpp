#pragma once
#include "AST.hpp"
#include "MyClasses.hpp"
class ASTPathSeg : public ASTnode {
  public:
    string id;
    vector<ASTType *> args;
    using ASTnode::ASTnode;
    virtual ~ASTPathSeg();
};