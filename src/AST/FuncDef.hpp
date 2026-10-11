#pragma once
#include "AST.hpp"
#include "Block.hpp"
#include "Param.hpp"
#include "SelfParam.hpp"
#include "Type.hpp"
class ASTFuncDef : public ASTItem {
  public:
    std::string name;
    ASTSelfParam *self;
    vector<ASTParam *> params;
    ASTType *ret;
    ASTBlock *block;
    ASTFuncDef(Span p);
    virtual ~ASTFuncDef();
};