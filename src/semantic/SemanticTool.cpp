#include "SemanticTool.hpp"
string SemanticTool::BOOL = "bool", SemanticTool::I32 = "i32",
       SemanticTool::ISIZE = "isize", SemanticTool::U32 = "u32",
       SemanticTool::USIZE = "usize";
int SemanticTool::if_basic(string s) {
    return s == BOOL || s == I32 || s == U32 || s == ISIZE || s == USIZE;
}
