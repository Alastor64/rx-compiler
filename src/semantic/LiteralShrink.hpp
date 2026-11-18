#pragma once
#include "ASTvisitor.hpp"
#include "Crate.hpp"
class LiteralShrink : public ASTvisitor {
  public:
    ASTCrate *root;
    int visitCrate(ASTCrate *) override;
    int visitELiteral(ASTELiteral *) override;
};