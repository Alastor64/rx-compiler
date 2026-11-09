#include "ASTvisitor.hpp"
#include "AST.hpp"
any ASTvisitor::visitChildren(ASTnode *ast) { return ast->visitChildren(this); }