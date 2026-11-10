#pragma once
#include "AST.hpp"
#include "MyClasses.hpp"
#include "MyDef.hpp"
#include "Struct.hpp"

class ASTvisitor {
  public:
    virtual int visit(ASTnode *);
    virtual int visitChildren(ASTnode *);
    virtual ~ASTvisitor() = default;
    virtual int visitNode(ASTnode *);

    virtual int visitCrate(ASTCrate *);
    virtual int visitFuncDef(ASTFuncDef *);
    virtual int visitStruct(ASTStruct *);
    virtual int visitSField(ASTSField *);
    virtual int visitConstant(ASTConstant *);
    virtual int visitImpl(ASTImpl *);
    virtual int visitParam(ASTParam *);
    virtual int visitSelfParam(ASTSelfParam *);
    virtual int visitPathSeg(ASTPathSeg *);
    virtual int visitLet(ASTLet *);
    virtual int visitStatement(ASTStatement *);
    virtual int visitBlock(ASTBlock *);

    virtual int visitType(ASTType *);
    virtual int visitTRef(ASTTRef *);
    virtual int visitTArray(ASTTArray *);
    virtual int visitTUnit(ASTTUnit *);
    virtual int visitTPath(ASTTPath *);

    virtual int visitExpr(ASTExpr *);
    virtual int visitEUnit(ASTEUnit *);
    virtual int visitEPath(ASTEPath *);
    virtual int visitEIf(ASTEIf *);
    virtual int visitEWhile(ASTEWhile *);
    virtual int visitEStruct(ASTEStruct *);
    virtual int visitELiteral(ASTELiteral *);
    virtual int visitEArray(ASTEArray *);
    virtual int visitERepeat(ASTERepeat *);
    virtual int visitEBranch(ASTEBranch *);
    virtual int visitOperator(ASTEOperator *);
    virtual int visitOBinary(ASTOBinary *);
    virtual int visitOUnary(ASTOUnary *);
    virtual int visitOCall(ASTOCall *);
    virtual int visitOIndex(ASTOIndex *);
    virtual int visitOField(ASTOField *);
    virtual int visitOMethod(ASTOMethod *);
    virtual int visitOAssign(ASTOAssign *);
    virtual int visitOCast(ASTOCast *);
    virtual int visitOShift(ASTOShift *);
};
