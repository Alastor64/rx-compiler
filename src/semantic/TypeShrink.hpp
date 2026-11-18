#pragma once
#include "ASTvisitor.hpp"
#include "Crate.hpp"
#include "SemanticType.hpp"
#include "Type.hpp"
class TypeShrink : public ASTvisitor {
  public:
    ASTCrate *root;
    SemanticType result;
    void reset();
    int visitCrate(ASTCrate *) override;
    int shrink(ASTType *&, SemanticType &);
    int visitTPath(ASTTPath *) override;
    int visitTArray(ASTTArray *) override;
    int visitTUnit(ASTTUnit *) override;
    int visitTRef(ASTTRef *) override;
    int visitParam(ASTParam *) override;
    int visitFuncDef(ASTFuncDef *) override;
    int visitLet(ASTLet *) override;
    int visitSField(ASTSField *) override;
    int visitOCast(ASTOCast *) override;
};