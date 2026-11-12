#pragma once
#include "ConstValueShrink.hpp"
#include "Crate.hpp"
#include "ImplShrink.hpp"
#include "IntUppering.hpp"
#include "MethodSheink.hpp"
#include "NameCollect.hpp"
#include "SelfEraseAndTypeArgsCheck.hpp"
#include "TypeShrink.hpp"
class SemanticChecker {
  public:
    // struct derive check
    ASTCrate *root;
    MethodShrink MS; // turn methods' func(pathseg) into string
    ImplShrink IS;   // turn impls' type into string
    NameCollect NC;
    // turn crate's structs and their fields,constants,methods(vector) into map
    SelfEraseAndTypeArgsCheck SEATAC;
    // replace Self(do not handle self) with ture type name,Check all generic
    // args num
    // NamePathErase NPE; replace paths that represent constants or
    // variables with symbol IntUppering IU; ConstValueShrink CVS; TypeShrink
    // TS;
    int SemanticCheck(ASTCrate *ast);
};