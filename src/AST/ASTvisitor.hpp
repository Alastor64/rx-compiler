#pragma once
#include "MyClasses.hpp"
#include "MyDef.hpp"
class ASTvisitor {
  public:
    virtual any visitnode(ASTnode *) {}
};