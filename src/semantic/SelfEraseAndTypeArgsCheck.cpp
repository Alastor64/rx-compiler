#include "SelfEraseAndTypeArgsCheck.hpp"
#include "ChildrenTool.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
#include "FuncDef.hpp"
#include "Impl.hpp"
#include "Path.hpp"
#include "Struct.hpp"
#include <cstddef>
void SelfEraseAndTypeArgsCheck::reset() {
    fa.clear();
    pathTail = 0;
}
int SelfEraseAndTypeArgsCheck::visitCrate(ASTCrate *node) {
    root = node;
    return node->visitChildren(this);
}
int SelfEraseAndTypeArgsCheck::visitStruct(ASTStruct *node) {
    fa = node->name;
    int res = node->visitChildren(this);
    fa.clear();
    return res;
}
int SelfEraseAndTypeArgsCheck::visitPathSeg(ASTPathSeg *node) {
    if (node->id == "Self") {
        if (fa.empty())
            return 1;
        node->id = fa;
    }
    if (!pathTail && (node->id == "Vec" || node->id == "Box") &&
        root->_structs.find(node->id) == root->_structs.end()) {
        if (node->args.size() != 1)
            return 1;
    } else {
        if (!node->args.empty()) {
            return 1;
        }
    }
    return node->visitChildren(this);
}
int SelfEraseAndTypeArgsCheck::visitTPath(ASTTPath *node) {
    pathTail = 0;
    int res = node->visitChildren(this);
    return res;
}
int SelfEraseAndTypeArgsCheck::visitEPath(ASTEPath *node) {
    pathTail = 0;
    for (size_t i = 0; i < node->path.size(); i++) {
        auto t = node->path.at(i);
        if (i + 1 >= node->path.size())
            pathTail = 1;
        int res = t->accept(this);
        if (res)
            return 1;
    }
    return 0;
}
int SelfEraseAndTypeArgsCheck::visitOMethod(ASTOMethod *node) {
    pathTail = 1;
    return node->func->accept(this) |
           ChildrenTool::visitList(node->args, this) |
           ChildrenTool::visitChild(node->owner, this);
}