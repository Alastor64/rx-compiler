#pragma once
#include "MyDef.hpp"
class SemanticTool {
  public:
    SemanticTool() = delete;
    static string I32, U32, ISIZE, USIZE, BOOL;
    static int if_basic(string s);
};