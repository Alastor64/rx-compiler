#include "ChildrenTool.hpp"
#include "AST.hpp"
int ChildrenTool::visitChild(ASTnode *node, ASTvisitor *visitor) {
    if (node)
        return node->accept(visitor);
    return 0;
}