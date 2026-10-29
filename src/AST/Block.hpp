#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include "Type.hpp"
#include <vector>
class ASTLet : public ASTnode {
  public:
    ASTLet(Span);
    virtual ~ASTLet();
    string id;
    ASTType *type;
    bool if_mut;
    ASTExpr *expr;
};
class ASTStatement : public ASTnode {
  public:
    enum Kind {
        EXPR,
        LET,
    };
    ASTStatement(Span);
    virtual ~ASTStatement();
    bool if_semi;
    Kind kind;
    ASTExpr *expr;
    ASTLet *let;
};
class ASTBlock : public ASTExpr {
  public:
    ASTBlock(Span);
    virtual ~ASTBlock();
    vector<ASTStatement *> statement;
    ASTExpr *tail;
};