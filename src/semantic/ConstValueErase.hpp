#pragma once
#include "ASTvisitor.hpp"
#include "Constant.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
class ConstValueErase : public ASTvisitor {
  public:
    ASTCrate *root;
    int visitCrate(ASTCrate *) override;
    int visitTArray(ASTTArray *) override;
    int visitERepeat(ASTERepeat *) override;
    int calLen(ASTExpr *&, unsigned int &);
};