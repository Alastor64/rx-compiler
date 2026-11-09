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
    vector<ASTFuncDef *> funcs;
    vector<ASTStruct *> structs;
    vector<ASTConstant *> consts;
    vector<ASTImpl *> impls;
    virtual ~ASTCrate();
    virtual any accept(ASTvisitor *visitor) override {
        return visitor->visitCrate(this);
    }
};
