#pragma once
#include "AST.hpp"
#include "Constant.hpp"
#include "FuncDef.hpp"
#include "Type.hpp"
struct ASTImpl : public ASTnode {
  public:
    ASTType *type;
    string id;
    vector<ASTConstant *> consts;
    vector<ASTFuncDef *> funcs;
    ASTImpl(Span);
    virtual ~ASTImpl();
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *visitor) override;
};
