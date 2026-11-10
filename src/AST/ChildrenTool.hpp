#pragma once
#include "MyClasses.hpp"
class ChildrenTool {
  public:
    ChildrenTool() = delete;

    // static void visitChild(ASTBlock *node, ASTvisitor *visitor);
    // static void visitChild(ASTPathSeg *node, ASTvisitor *visitor);
    // static void visitChild(ASTType *node, ASTvisitor *visitor);

    static int visitChild(ASTnode *node, ASTvisitor *visitor);

    template <typename T>
    static int visitList(const vector<T *> &nodes, ASTvisitor *visitor) {
        int res = 0;
        for (auto *node : nodes)
            res |= visitChild(node, visitor);
        return res;
    }

    template <typename T>
    static int visitMap(const map<string, T *> &nodes, ASTvisitor *visitor) {
        int res = 0;
        for (const auto &[_, node] : nodes)
            res |= visitChild(node, visitor);
        return res;
    }
};
