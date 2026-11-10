#pragma once
#include "AST.hpp"
#include "Crate.hpp"
#include "ImplShrink.hpp"
#include "NameCollect.hpp"
#include "SelfErase.hpp"
class SemanticChecker {
  public:
    ASTCrate *root;
    ImplShrink IS;
    NameCollect NC;
    SelfErase SE;
    int SemanticCheck(ASTCrate *ast);
};