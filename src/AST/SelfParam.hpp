#pragma once
#include "AST.hpp"
class ASTSelfParam : public ASTnode {
  public:
    ASTSelfParam(Span p);
    bool if_and;
    bool if_mut;
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *) override;
};
