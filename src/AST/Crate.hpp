#pragma once
#include "AST.hpp"
#include "FuncDef.hpp"
#include "MyDef.hpp"
#include "RxParser.h"
#include "Struct.hpp"
#include <vector>
class ASTCrate : public ASTnode {
  public:
    using ASTnode::ASTnode;
    vector<ASTFuncDef *> funcs;
    vector<ASTStruct *> structs;
    virtual ~ASTCrate();
};