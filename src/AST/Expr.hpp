#pragma once
#include "AST.hpp"
#include "MyClasses.hpp"
#include <vector>
class ASTExpr : public ASTnode {
  public:
    using ASTnode::ASTnode;
};

class ASTEUnit : public ASTExpr {
  public:
    using ASTExpr::ASTExpr;
};
class ASTEPath : public ASTExpr {
  public:
    vector<ASTPathSeg *> path;
    using ASTExpr::ASTExpr;
    virtual ~ASTEPath();
};

class ASTEIf : public ASTExpr {};
// while loop(if condition=nullptr)
class ASTEWhile : public ASTExpr {
  public:
    ASTExpr *condition;
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
};
// int true false (unit)
class ASTELiteral : public ASTExpr {
  public:
    string int_text;
    bool if_int;
    bool if_true;
    bool if_false;
    ASTELiteral(Span p);
};

// [,,,]
class ASTEArray : public ASTExpr {
  public:
    vector<ASTExpr *> elem;
    using ASTExpr::ASTExpr;
    virtual ~ASTEArray();
};
// [;]
class ASTERepeat : public ASTExpr {
  public:
    ASTExpr *elem;
    ASTExpr *len;
    ASTERepeat(Span p);
    virtual ~ASTERepeat();
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
};

class ASTEOperator : public ASTExpr {
  public:
    using ASTExpr::ASTExpr;
    string op;
};

// + - * / && || & | ^ % < > <= >= == !=
class ASTOBinary : public ASTEOperator {
  public:
    ASTExpr *left;
    ASTExpr *right;
    ASTOBinary(Span);
    virtual ~ASTOBinary();
};
// - ! * & &mut &&mut(2 nodes) &&(2 nodes)
class ASTOUnary : public ASTEOperator {
  public:
    bool if_mut;
    ASTExpr *inner;
    ASTOUnary(Span);
    virtual ~ASTOUnary();
};
// ()
class ASTOCall : public ASTEOperator {
  public:
    ASTExpr *func;
    vector<ASTExpr *> args;
    ASTOCall(Span);
    virtual ~ASTOCall();
};
// []
class ASTOIndex : public ASTEOperator {
  public:
    ASTExpr *array;
    ASTExpr *index;
    ASTOIndex(Span);
    virtual ~ASTOIndex();
};
// .
class ASTOField : public ASTEOperator {
  public:
    ASTExpr *owner;
    string id;
    ASTOField(Span);
    virtual ~ASTOField();
};
// .()
class ASTOMethod : public ASTEOperator {
  public:
    ASTExpr *owner;
    ASTPathSeg *func;
    vector<ASTExpr *> args;
    ASTOMethod(Span);
    virtual ~ASTOMethod();
};
// = += *= /= %= -= ^= |= &= <<= >>=
class ASTOAssign : public ASTEOperator {
  public:
    ASTExpr *place;
    ASTExpr *value;
    ASTOAssign(Span);
    virtual ~ASTOAssign();
};
// as
class ASTOCast : public ASTEOperator {
  public:
    ASTExpr *value;
    ASTType *type;
    ASTOCast(Span);
    virtual ~ASTOCast();
};
// << >>
class ASTOShift : public ASTEOperator {
  public:
    ASTExpr *base;
    ASTExpr *expo;
    ASTOShift(Span);
    virtual ~ASTOShift();
};
// (expr) no new node