#pragma once
#include "MyClasses.hpp"
class ChildrenTool {
  public:
    ChildrenTool() = delete;

    // static void visitChild(ASTBlock *node, ASTvisitor *visitor);
    // static void visitChild(ASTPathSeg *node, ASTvisitor *visitor);
    // static void visitChild(ASTType *node, ASTvisitor *visitor);

    static void visitChild(ASTnode *node, ASTvisitor *visitor);

    template <typename T>
    static void visitList(const vector<T *> &nodes, ASTvisitor *visitor) {
        for (auto *node : nodes)
            visitChild(node, visitor);
    }
};
