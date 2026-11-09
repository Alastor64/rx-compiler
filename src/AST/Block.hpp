#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include "Type.hpp"

class ASTLet : public ASTnode {
  public:
    ASTLet(Span);
    virtual ~ASTLet();
    string id;
    ASTType *type;
    bool if_mut;
    ASTExpr *expr;
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *visitor) override;
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
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *visitor) override;
};
class ASTBlock : public ASTExpr {
  public:
    ASTBlock(Span);
    virtual ~ASTBlock();
    vector<ASTStatement *> statement;
    ASTExpr *tail;
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *visitor) override;
};
