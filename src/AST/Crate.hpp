#pragma once
#include "AST.hpp"
#include "MyDef.hpp"
#include "RxParser.h"
#include <vector>
class ASTCrate : public ASTnode {
  public:
    using ASTnode::ASTnode;
    std::vector<ASTItem *> items;
    virtual ~ASTCrate();
};