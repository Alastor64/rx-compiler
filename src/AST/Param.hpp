#pragma once
#include "AST.hpp"
#include "Type.hpp"
class ASTParam : public ASTnode {
  public:
    ASTParam(Span p);
    ASTType *type;
    string name;
    bool if_mut;
    virtual ~ASTParam();
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *visitor) override;
};
