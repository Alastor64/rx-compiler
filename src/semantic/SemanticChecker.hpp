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
    // struct derive check(no class)
    ASTCrate *root;
    // turn methods' func(pathseg) into string
    MethodShrink MS;
    // turn impls' type into string
    ImplShrink IS;
    // turn crate's structs and their fields,constants,methods(vector) into map
    NameCollect NC;
    // replace Self(do not handle self) with ture type name,Check all generic
    // args num
    SelfEraseAndTypeArgsCheck SEATAC;
    // calculate all constantItem,get its _value and semanticType,remove its
    // value and type
    ConstValueShrink CVS;

    // calculate all constvalue(seems only arrytype use it)
    // ConstValueErase CE;

    // replace ASTELiteral with SEMImm
    //  ConstErase CE;

    // NamePathErase NPE; replace paths that represent constants
    // or variables with symbol IntUppering IU; ConstValueShrink CVS; TypeShrink
    // TS;
    int SemanticCheck(ASTCrate *ast);
};