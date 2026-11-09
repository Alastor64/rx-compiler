#pragma once
#include "AST.hpp"
#include "Constant.hpp"
#include "FuncDef.hpp"
#include "Type.hpp"
class ASTStruct : public ASTnode {
  public:
    class Field {
      public:
        Span pos;
        string name;
        ASTType *type;
        Field(Span, string, ASTType *);
        void del();
    };
    class Derive { // we drop the pos of derive
      public:
        int sta;
        // 01234
        // if_err, if_copy, if_clone, if_partial_eq, if_eq;
        Derive();
        Derive(int);
        void merge(const Derive &);
        bool err() const;
        bool copy() const;
        bool clone() const;
        bool eq() const;
        bool partial_eq() const;
    };
    Derive derive;
    string name;
    vector<Field> fields;
    map<string, Field> _fields;
    map<string, ASTFuncDef *> _methods;
    map<string, ASTConstant *> _consts;
    ASTStruct(Span);
    virtual ~ASTStruct();
    virtual int accept(ASTvisitor *visitor) override;
    virtual int visitChildren(ASTvisitor *visitor) override;
};
