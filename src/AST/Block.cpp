#include "Block.hpp"
#include "AST.hpp"
ASTExpr::ASTExpr(Span p) : ASTnode(p) {}
ASTExpr::~ASTExpr() {}
ASTBlock::ASTBlock(Span p) : ASTExpr(p) {}
ASTBlock::~ASTBlock() {}