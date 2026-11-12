#pragma once
#include "MyDef.hpp"
#include "SemanticType.hpp"
#include "Type.hpp"
#include "myErr.hpp"
class SemanticTool {
  public:
    SemanticTool() = delete;
    static string I32, U32, ISIZE, USIZE, BOOL;
    static int if_basic(string s);
    static int basicTypeTran(ASTType *node, SemanticType &);
};