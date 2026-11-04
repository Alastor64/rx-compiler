#pragma once
#include "AST.hpp"
#include "Constant.hpp"
#include "FuncDef.hpp"
#include "Type.hpp"
#include <vector>
struct ASTImpl : public ASTnode {
  public:
    ASTType *type;
    vector<ASTConstant *> consts;
    vector<ASTFuncDef *> funcs;
    ASTImpl(Span);
    virtual ~ASTImpl();
};