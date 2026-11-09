#pragma once
#include "AST.hpp"
#include "Constant.hpp"
#include "FuncDef.hpp"
#include "Impl.hpp"
#include "MyDef.hpp"
#include "Struct.hpp"

class ASTCrate : public ASTnode {
  public:
    using ASTnode::ASTnode;
    map<string, ASTFuncDef *> _funcs;
    map<string, ASTStruct *> _structs;
    map<string, ASTConstant *> _consts;
    vector<ASTFuncDef *> funcs;
    vector<ASTStruct *> structs;
    vector<ASTConstant *> consts;
    vector<ASTImpl *> impls;
    virtual ~ASTCrate();
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *visitor) override;
};
