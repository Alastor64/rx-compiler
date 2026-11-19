#pragma once
#include "ConstValueErase.hpp"
#include "ConstValueShrink.hpp"
#include "Crate.hpp"
#include "ImplShrink.hpp"
#include "LiteralShrink.hpp"
#include "MethodSheink.hpp"
#include "NameCollect.hpp"
#include "SelfEraseAndTypeArgsCheck.hpp"
#include "TypeCheckAndInfer.hpp"
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
    // calculate out all literal
    LiteralShrink LS;

    // calculate all constantItem,get its _value and semanticType,remove its
    // value and type
    ConstValueShrink CVS;

    // calculate all constvalue(seems only arrytype use it)
    ConstValueErase CVE;

    // turn all ASTType into SemanticType
    TypeShrink TS;

    // type check and infer
    TypeCheckAndInfer TCAI;

    // 1:fail 0:pass
    int SemanticCheck(ASTCrate *ast);
};