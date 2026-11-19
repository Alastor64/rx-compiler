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
        for (auto *node : nodes)
            if (auto ret = visitChild(node, visitor))
                return ret;
        return 0;
    }

    template <typename T>
    static int visitMap(const map<string, T *> &nodes, ASTvisitor *visitor) {
        for (const auto &[_, node] : nodes)
            if (auto ret = visitChild(node, visitor))
                return ret;
        return 0;
    }
};
