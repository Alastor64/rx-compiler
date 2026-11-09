#pragma once
#include "AST.hpp"
#include "MyClasses.hpp"
#include "MyDef.hpp"

class ASTvisitor {
  public:
    virtual any visit(ASTnode *);
    virtual any visitChildren(ASTnode *);
    virtual ~ASTvisitor() = default;
    virtual any visitNode(ASTnode *);

    virtual any visitCrate(ASTCrate *);
    virtual any visitFuncDef(ASTFuncDef *);
    virtual any visitStruct(ASTStruct *);
    virtual any visitConstant(ASTConstant *);
    virtual any visitImpl(ASTImpl *);
    virtual any visitParam(ASTParam *);
    virtual any visitSelfParam(ASTSelfParam *);
    virtual any visitPathSeg(ASTPathSeg *);
    virtual any visitLet(ASTLet *);
    virtual any visitStatement(ASTStatement *);
    virtual any visitBlock(ASTBlock *);

    virtual any visitType(ASTType *);
    virtual any visitTRef(ASTTRef *);
    virtual any visitTArray(ASTTArray *);
    virtual any visitTUnit(ASTTUnit *);
    virtual any visitTPath(ASTTPath *);

    virtual any visitExpr(ASTExpr *);
    virtual any visitEUnit(ASTEUnit *);
    virtual any visitEPath(ASTEPath *);
    virtual any visitEIf(ASTEIf *);
    virtual any visitEWhile(ASTEWhile *);
    virtual any visitEStruct(ASTEStruct *);
    virtual any visitELiteral(ASTELiteral *);
    virtual any visitEArray(ASTEArray *);
    virtual any visitERepeat(ASTERepeat *);
    virtual any visitEBranch(ASTEBranch *);
    virtual any visitOperator(ASTEOperator *);
    virtual any visitOBinary(ASTOBinary *);
    virtual any visitOUnary(ASTOUnary *);
    virtual any visitOCall(ASTOCall *);
    virtual any visitOIndex(ASTOIndex *);
    virtual any visitOField(ASTOField *);
    virtual any visitOMethod(ASTOMethod *);
    virtual any visitOAssign(ASTOAssign *);
    virtual any visitOCast(ASTOCast *);
    virtual any visitOShift(ASTOShift *);
};
