#pragma once
#include "ASTvisitor.hpp"
#include "Crate.hpp"
class TypeCheckAndInfer : public ASTvisitor {
  public:
    ASTCrate *root;
    void reset();
};