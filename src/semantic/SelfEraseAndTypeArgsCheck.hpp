#pragma once
#include "ASTvisitor.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
#include "Path.hpp"
#include "Struct.hpp"
// remove all Self
// check all path's arg num
class SelfEraseAndTypeArgsCheck : public ASTvisitor {
  public:
    string fa;
    ASTCrate *root;
    int pathTail;
    void reset();
    virtual int visitCrate(ASTCrate *node) override;
    virtual int visitStruct(ASTStruct *node) override;
    virtual int visitPathSeg(ASTPathSeg *node) override;
    virtual int visitEPath(ASTEPath *node) override;
    virtual int visitTPath(ASTTPath *node) override;
    virtual int visitOMethod(ASTOMethod *node) override;
};
