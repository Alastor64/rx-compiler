#pragma once
#include "AST.hpp"
#include "MyDef.hpp"
#include "RxParser.h"
#include <vector>
class ASTCrate : public ASTnode {
  public:
    ASTCrate(Span p);
    std::vector<ASTItem *> items;
    virtual ~ASTCrate();
};