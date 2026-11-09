#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include "MyClasses.hpp"
class ASTType : public ASTnode {
  public:
    using ASTnode::ASTnode;
    virtual any accept(ASTvisitor *visitor) override {
        return visitor->visitType(this);
    }
};
class ASTTRef : public ASTType {
  public:
    bool if_mut;
    ASTType *inner;
    ASTTRef(Span p);
    virtual ~ASTTRef();
    virtual any accept(ASTvisitor *visitor) override {
        return visitor->visitTRef(this);
    }
};
class ASTTArray : public ASTType {
  public:
    ASTType *elem;
    ASTExpr *len;
    ASTTArray(Span p);
    virtual ~ASTTArray();
    virtual any accept(ASTvisitor *visitor) override {
        return visitor->visitTArray(this);
    }
};
class ASTTUnit : public ASTType {
  public:
    using ASTType::ASTType;
    virtual any accept(ASTvisitor *visitor) override {
        return visitor->visitTUnit(this);
    }
};
class ASTTPath : public ASTType {
  public:
    using ASTType::ASTType;
    vector<ASTPathSeg *> path;
    virtual ~ASTTPath();
    virtual any accept(ASTvisitor *visitor) override {
        return visitor->visitTPath(this);
    }
};
