#pragma once
#include "AST.hpp"
#include "MyClasses.hpp"
class ASTExpr : public ASTnode {
  public:
    using ASTnode::ASTnode;
};
class ASTEIf : public ASTExpr {};
// while loop(if condition=nullptr)
class ASTEWhile : public ASTExpr {};
class ASTEStruct : public ASTExpr {};
// int true false (unit)
class ASTELiteral : public ASTExpr {
  public:
    string int_text;
    bool if_int;
    bool if_true;
    bool if_false;
    bool if_unit; // realize in nonblockexpr
    ASTELiteral(Span p);
};

class ASTEPath : public ASTExpr {
  public:
    vector<ASTPathSeg *> path;
    using ASTExpr::ASTExpr;
    virtual ~ASTEPath();
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
class ASTEBranch : public ASTExpr {};

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
class ASTOUnary : public ASTEOperator {};
// ()
class ASTOCall : public ASTEOperator {};
// []
class ASTOIndex : public ASTEOperator {};
// .
class ASTOField : public ASTEOperator {};
// .()
class ASTOMethod : public ASTEOperator {};
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