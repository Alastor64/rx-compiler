#include "ASTvisitor.hpp"
#include "AST.hpp"
#include "Block.hpp"
#include "Constant.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
#include "FuncDef.hpp"
#include "Impl.hpp"
#include "Param.hpp"
#include "Path.hpp"
#include "SelfParam.hpp"
#include "Struct.hpp"
#include "Type.hpp"

int ASTvisitor::visit(ASTnode *ast) { return ast->accept(this); }
int ASTvisitor::visitChildren(ASTnode *ast) { return ast->visitChildren(this); }
int ASTvisitor::visitNode(ASTnode *node) { return visitChildren(node); }

int ASTvisitor::visitCrate(ASTCrate *node) { return visitChildren(node); }
int ASTvisitor::visitFuncDef(ASTFuncDef *node) { return visitChildren(node); }
int ASTvisitor::visitSField(ASTSField *node) { return visitChildren(node); }
int ASTvisitor::visitStruct(ASTStruct *node) { return visitChildren(node); }
int ASTvisitor::visitConstant(ASTConstant *node) { return visitChildren(node); }
int ASTvisitor::visitImpl(ASTImpl *node) { return visitChildren(node); }
int ASTvisitor::visitParam(ASTParam *node) { return visitChildren(node); }
int ASTvisitor::visitSelfParam(ASTSelfParam *node) {
    return visitChildren(node);
}
int ASTvisitor::visitPathSeg(ASTPathSeg *node) { return visitChildren(node); }
int ASTvisitor::visitLet(ASTLet *node) { return visitChildren(node); }
int ASTvisitor::visitStatement(ASTStatement *node) {
    return visitChildren(node);
}
int ASTvisitor::visitBlock(ASTBlock *node) { return visitChildren(node); }

int ASTvisitor::visitType(ASTType *node) { return visitChildren(node); }
int ASTvisitor::visitTRef(ASTTRef *node) { return visitChildren(node); }
int ASTvisitor::visitTArray(ASTTArray *node) { return visitChildren(node); }
int ASTvisitor::visitTUnit(ASTTUnit *node) { return visitChildren(node); }
int ASTvisitor::visitTPath(ASTTPath *node) { return visitChildren(node); }

int ASTvisitor::visitExpr(ASTExpr *node) { return visitChildren(node); }
int ASTvisitor::visitEUnit(ASTEUnit *node) { return visitChildren(node); }
int ASTvisitor::visitEPath(ASTEPath *node) { return visitChildren(node); }
int ASTvisitor::visitEIf(ASTEIf *node) { return visitChildren(node); }
int ASTvisitor::visitEWhile(ASTEWhile *node) { return visitChildren(node); }
int ASTvisitor::visitEStruct(ASTEStruct *node) { return visitChildren(node); }
int ASTvisitor::visitELiteral(ASTELiteral *node) { return visitChildren(node); }
int ASTvisitor::visitEArray(ASTEArray *node) { return visitChildren(node); }
int ASTvisitor::visitERepeat(ASTERepeat *node) { return visitChildren(node); }
int ASTvisitor::visitEBranch(ASTEBranch *node) { return visitChildren(node); }
int ASTvisitor::visitOperator(ASTEOperator *node) {
    return visitChildren(node);
}
int ASTvisitor::visitOBinary(ASTOBinary *node) { return visitChildren(node); }
int ASTvisitor::visitOUnary(ASTOUnary *node) { return visitChildren(node); }
int ASTvisitor::visitOCall(ASTOCall *node) { return visitChildren(node); }
int ASTvisitor::visitOIndex(ASTOIndex *node) { return visitChildren(node); }
int ASTvisitor::visitOField(ASTOField *node) { return visitChildren(node); }
int ASTvisitor::visitOMethod(ASTOMethod *node) { return visitChildren(node); }
int ASTvisitor::visitOAssign(ASTOAssign *node) { return visitChildren(node); }
int ASTvisitor::visitOCast(ASTOCast *node) { return visitChildren(node); }
int ASTvisitor::visitOShift(ASTOShift *node) { return visitChildren(node); }

// void ChildrenTool::visitChild(ASTBlock *node, ASTvisitor *visitor) {
//     if (node)
//         node->accept(visitor);
// }
// void ChildrenTool::visitChild(ASTPathSeg *node, ASTvisitor *visitor) {
//     if (node)
//         node->accept(visitor);
// }
// void ChildrenTool::visitChild(ASTType *node, ASTvisitor *visitor) {
//     if (node)
//         node->accept(visitor);
// }
