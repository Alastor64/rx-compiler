#pragma once
#include "ASTvisitor.hpp"
#include "Constant.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
#include "Struct.hpp"
// calculate all constant's value and value type
class ConstValueShrink : public ASTvisitor {
  public:
    using MP = map<ASTConstant *, int>;
    static MP tmp;
    ASTCrate *root;
    void reset();
    virtual int visitCrate(ASTCrate *) override;
    virtual int visitConstant(ASTConstant *) override;
    virtual int visitStruct(ASTStruct *) override;
    virtual int visitELiteral(ASTELiteral *) override;
    virtual int visitOUnary(ASTOUnary *) override;
};