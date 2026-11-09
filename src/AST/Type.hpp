#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include "MyClasses.hpp"
class ASTType : public ASTnode {
  public:
    using ASTnode::ASTnode;
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *) override;
};
class ASTTRef : public ASTType {
  public:
    bool if_mut;
    ASTType *inner;
    ASTTRef(Span p);
    virtual ~ASTTRef();
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *visitor) override;
};
class ASTTArray : public ASTType {
  public:
    ASTType *elem;
    ASTExpr *len;
    ASTTArray(Span p);
    virtual ~ASTTArray();
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *visitor) override;
};
class ASTTUnit : public ASTType {
  public:
    using ASTType::ASTType;
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *) override;
};
class ASTTPath : public ASTType {
  public:
    using ASTType::ASTType;
    vector<ASTPathSeg *> path;
    virtual ~ASTTPath();
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *visitor) override;
};
