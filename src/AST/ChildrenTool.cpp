#include "ChildrenTool.hpp"
#include "AST.hpp"
void ChildrenTool::visitChild(ASTnode *node, ASTvisitor *visitor) {
    if (node)
        node->accept(visitor);
}