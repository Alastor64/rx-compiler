#pragma once
#include "AST.hpp"
#include "MyClasses.hpp"

class ASTExpr : public ASTnode {
  public:
    using ASTnode::ASTnode;
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *) override;
};

class ASTEUnit : public ASTExpr {
  public:
    using ASTExpr::ASTExpr;
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *) override;
};
class ASTEPath : public ASTExpr {
  public:
    vector<ASTPathSeg *> path;
    using ASTExpr::ASTExpr;
    virtual ~ASTEPath();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};

class ASTEIf : public ASTExpr {
  public:
    ASTEIf(Span);
    virtual ~ASTEIf();
    ASTExpr *condition;
    ASTBlock *truestat;
    ASTExpr *falsestat;
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// while loop(if condition=nullptr)
class ASTEWhile : public ASTExpr {
  public:
    enum Kind {
        WHILE,
        LOOP,
    };
    ASTEWhile(Span);
    virtual ~ASTEWhile();
    Kind kind;
    ASTExpr *condition;
    ASTBlock *block;
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
class ASTEStruct : public ASTExpr {
  public:
    class Field {
      public:
        Span pos;
        string id;
        ASTExpr *value;
        Field(Span, const string &, ASTExpr *);
        void del();
    };
    ASTEPath *path;
    vector<Field> member;
    ASTEStruct(Span);
    virtual ~ASTEStruct();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// int true false (unit)
class ASTELiteral : public ASTExpr {
  public:
    string int_text;
    bool if_int;
    bool if_true;
    bool if_false;
    ASTELiteral(Span p);
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *) override;
};

// [,,,]
class ASTEArray : public ASTExpr {
  public:
    vector<ASTExpr *> elem;
    using ASTExpr::ASTExpr;
    virtual ~ASTEArray();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// [;]
class ASTERepeat : public ASTExpr {
  public:
    ASTExpr *elem;
    ASTExpr *len;
    ASTERepeat(Span p);
    virtual ~ASTERepeat();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// return continue break
class ASTEBranch : public ASTExpr {
  public:
    enum Kind {
        CONTINUE,
        BREAK,
        RETURN,
    };
    Kind kind;
    ASTExpr *value;
    ASTEBranch(Span);
    virtual ~ASTEBranch();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};

class ASTEOperator : public ASTExpr {
  public:
    using ASTExpr::ASTExpr;
    string op;
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *) override;
};

// + - * / && || & | ^ % < > <= >= == !=
class ASTOBinary : public ASTEOperator {
  public:
    ASTExpr *left;
    ASTExpr *right;
    ASTOBinary(Span);
    virtual ~ASTOBinary();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// - ! * & &mut &&mut(2 nodes) &&(2 nodes)
class ASTOUnary : public ASTEOperator {
  public:
    bool if_mut;
    ASTExpr *inner;
    ASTOUnary(Span);
    virtual ~ASTOUnary();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// ()
class ASTOCall : public ASTEOperator {
  public:
    ASTExpr *func;
    vector<ASTExpr *> args;
    ASTOCall(Span);
    virtual ~ASTOCall();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// []
class ASTOIndex : public ASTEOperator {
  public:
    ASTExpr *array;
    ASTExpr *index;
    ASTOIndex(Span);
    virtual ~ASTOIndex();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// .
class ASTOField : public ASTEOperator {
  public:
    ASTExpr *owner;
    string id;
    ASTOField(Span);
    virtual ~ASTOField();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// .()
class ASTOMethod : public ASTEOperator {
  public:
    ASTExpr *owner;
    ASTPathSeg *func;
    vector<ASTExpr *> args;
    ASTOMethod(Span);
    virtual ~ASTOMethod();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// = += *= /= %= -= ^= |= &= <<= >>=
class ASTOAssign : public ASTEOperator {
  public:
    ASTExpr *place;
    ASTExpr *value;
    ASTOAssign(Span);
    virtual ~ASTOAssign();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// as
class ASTOCast : public ASTEOperator {
  public:
    ASTExpr *value;
    ASTType *type;
    ASTOCast(Span);
    virtual ~ASTOCast();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// << >>
class ASTOShift : public ASTEOperator {
  public:
    ASTExpr *base;
    ASTExpr *expo;
    ASTOShift(Span);
    virtual ~ASTOShift();
    virtual any accept(ASTvisitor *visitor) override;
    virtual any visitChildren(ASTvisitor *visitor) override;
};
// (expr) no new node
