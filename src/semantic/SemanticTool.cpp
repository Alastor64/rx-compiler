#include "SemanticTool.hpp"
#include "Path.hpp"
#include "SemanticType.hpp"
string SemanticTool::BOOL = "bool", SemanticTool::I32 = "i32",
       SemanticTool::ISIZE = "isize", SemanticTool::U32 = "u32",
       SemanticTool::USIZE = "usize";
int SemanticTool::if_basic(string s) {
    return s == BOOL || s == I32 || s == U32 || s == ISIZE || s == USIZE;
}
int SemanticTool::basicTypeTran(ASTType *node, SemanticType &res) {
    if (auto tmp = dynamic_cast<ASTTPath *>(node)) {
        if (tmp->path.size() != 1)
            return 1;
        if (!if_basic(tmp->path.front()->id))
            return 1;
        res.layers.clear();
        res.layers.push_back(SemanticType::Layer(tmp->path.front()->id));
        return 0;
    } else
        return 1;
}
