#pragma once
#include "Crate.hpp"
#include "ImplShrink.hpp"
#include "NameCollect.hpp"
#include "SelfEraseAndTypeArgsCheck.hpp"
class SemanticChecker {
  public:
    ASTCrate *root;
    ImplShrink IS;
    NameCollect NC;
    SelfEraseAndTypeArgsCheck SEATAC;
    int SemanticCheck(ASTCrate *ast);
};