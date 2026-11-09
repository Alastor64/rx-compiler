#pragma once
#include "MyClasses.hpp"
#include "MyDef.hpp"

class ASTvisitor {
  public:
    virtual ~ASTvisitor() = default;
    virtual any visitNode(ASTnode *) { return {}; }

    virtual any visitCrate(ASTCrate *) { return {}; }
    virtual any visitFuncDef(ASTFuncDef *) { return {}; }
    virtual any visitStruct(ASTStruct *) { return {}; }
    virtual any visitConstant(ASTConstant *) { return {}; }
    virtual any visitImpl(ASTImpl *) { return {}; }
    virtual any visitParam(ASTParam *) { return {}; }
    virtual any visitSelfParam(ASTSelfParam *) { return {}; }
    virtual any visitPathSeg(ASTPathSeg *) { return {}; }
    virtual any visitLet(ASTLet *) { return {}; }
    virtual any visitStatement(ASTStatement *) { return {}; }
    virtual any visitBlock(ASTBlock *) { return {}; }

    virtual any visitType(ASTType *) { return {}; }
    virtual any visitTRef(ASTTRef *) { return {}; }
    virtual any visitTArray(ASTTArray *) { return {}; }
    virtual any visitTUnit(ASTTUnit *) { return {}; }
    virtual any visitTPath(ASTTPath *) { return {}; }

    virtual any visitExpr(ASTExpr *) { return {}; }
    virtual any visitEUnit(ASTEUnit *) { return {}; }
    virtual any visitEPath(ASTEPath *) { return {}; }
    virtual any visitEIf(ASTEIf *) { return {}; }
    virtual any visitEWhile(ASTEWhile *) { return {}; }
    virtual any visitEStruct(ASTEStruct *) { return {}; }
    virtual any visitELiteral(ASTELiteral *) { return {}; }
    virtual any visitEArray(ASTEArray *) { return {}; }
    virtual any visitERepeat(ASTERepeat *) { return {}; }
    virtual any visitEBranch(ASTEBranch *) { return {}; }
    virtual any visitOperator(ASTEOperator *) { return {}; }
    virtual any visitOBinary(ASTOBinary *) { return {}; }
    virtual any visitOUnary(ASTOUnary *) { return {}; }
    virtual any visitOCall(ASTOCall *) { return {}; }
    virtual any visitOIndex(ASTOIndex *) { return {}; }
    virtual any visitOField(ASTOField *) { return {}; }
    virtual any visitOMethod(ASTOMethod *) { return {}; }
    virtual any visitOAssign(ASTOAssign *) { return {}; }
    virtual any visitOCast(ASTOCast *) { return {}; }
    virtual any visitOShift(ASTOShift *) { return {}; }
};
