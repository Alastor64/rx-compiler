#pragma once
#include "ASTvisitor.hpp"
#include "Crate.hpp"
#include "Path.hpp"
#include "Struct.hpp"
#include <vector>
class SelfEraseAndTypeArgsCheck : public ASTvisitor {
  public:
    string fa;
    ASTCrate *root;
    void reset();
    virtual int visitCrate(ASTCrate *node) override;
    virtual int visitStruct(ASTStruct *node) override;
    virtual int visitPathSeg(ASTPathSeg *node) override;
};
