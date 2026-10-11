#pragma once
#include "AST.hpp"
class ASTType : public ASTnode {
  public:
    using ASTnode::ASTnode;
};
class ASTTRef : public ASTType {
  public:
    bool if_mut;
    ASTType *inner;
    ASTTRef(Span p);
    virtual ~ASTTRef();
};
class ASTTArray : public ASTType {
  public:
    using ASTType::ASTType;
    virtual ~ASTTArray();
};
class ASTTUnit : public ASTType {
  public:
    using ASTType::ASTType;
};
class ASTTPath : public ASTType {};