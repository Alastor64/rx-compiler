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

any ASTvisitor::visitChildren(ASTnode *ast) { return ast->visitChildren(this); }
any ASTvisitor::visitNode(ASTnode *node) { return visitChildren(node); }

any ASTvisitor::visitCrate(ASTCrate *node) { return visitChildren(node); }
any ASTvisitor::visitFuncDef(ASTFuncDef *node) { return visitChildren(node); }
any ASTvisitor::visitStruct(ASTStruct *node) { return visitChildren(node); }
any ASTvisitor::visitConstant(ASTConstant *node) { return visitChildren(node); }
any ASTvisitor::visitImpl(ASTImpl *node) { return visitChildren(node); }
any ASTvisitor::visitParam(ASTParam *node) { return visitChildren(node); }
any ASTvisitor::visitSelfParam(ASTSelfParam *node) {
    return visitChildren(node);
}
any ASTvisitor::visitPathSeg(ASTPathSeg *node) { return visitChildren(node); }
any ASTvisitor::visitLet(ASTLet *node) { return visitChildren(node); }
any ASTvisitor::visitStatement(ASTStatement *node) {
    return visitChildren(node);
}
any ASTvisitor::visitBlock(ASTBlock *node) { return visitChildren(node); }

any ASTvisitor::visitType(ASTType *node) { return visitChildren(node); }
any ASTvisitor::visitTRef(ASTTRef *node) { return visitChildren(node); }
any ASTvisitor::visitTArray(ASTTArray *node) { return visitChildren(node); }
any ASTvisitor::visitTUnit(ASTTUnit *node) { return visitChildren(node); }
any ASTvisitor::visitTPath(ASTTPath *node) { return visitChildren(node); }

any ASTvisitor::visitExpr(ASTExpr *node) { return visitChildren(node); }
any ASTvisitor::visitEUnit(ASTEUnit *node) { return visitChildren(node); }
any ASTvisitor::visitEPath(ASTEPath *node) { return visitChildren(node); }
any ASTvisitor::visitEIf(ASTEIf *node) { return visitChildren(node); }
any ASTvisitor::visitEWhile(ASTEWhile *node) { return visitChildren(node); }
any ASTvisitor::visitEStruct(ASTEStruct *node) { return visitChildren(node); }
any ASTvisitor::visitELiteral(ASTELiteral *node) { return visitChildren(node); }
any ASTvisitor::visitEArray(ASTEArray *node) { return visitChildren(node); }
any ASTvisitor::visitERepeat(ASTERepeat *node) { return visitChildren(node); }
any ASTvisitor::visitEBranch(ASTEBranch *node) { return visitChildren(node); }
any ASTvisitor::visitOperator(ASTEOperator *node) {
    return visitChildren(node);
}
any ASTvisitor::visitOBinary(ASTOBinary *node) { return visitChildren(node); }
any ASTvisitor::visitOUnary(ASTOUnary *node) { return visitChildren(node); }
any ASTvisitor::visitOCall(ASTOCall *node) { return visitChildren(node); }
any ASTvisitor::visitOIndex(ASTOIndex *node) { return visitChildren(node); }
any ASTvisitor::visitOField(ASTOField *node) { return visitChildren(node); }
any ASTvisitor::visitOMethod(ASTOMethod *node) { return visitChildren(node); }
any ASTvisitor::visitOAssign(ASTOAssign *node) { return visitChildren(node); }
any ASTvisitor::visitOCast(ASTOCast *node) { return visitChildren(node); }
any ASTvisitor::visitOShift(ASTOShift *node) { return visitChildren(node); }

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
