#pragma once
#include "MyDef.hpp"
#include "myErr.hpp"
#include <ParserRuleContext.h>
#include <Token.h>
#include <cstddef>
#include <type_traits>
struct Span {
  public:
    size_t begin, end;
    Span();
    Span(size_t b, size_t e);
    static Span getRuleSpan(antlr4::ParserRuleContext *ctx);
    static Span getTokenSpan(antlr4::Token *tk);
};
class ASTnode {
  public:
    virtual ~ASTnode();
    Span pos;
    ASTnode &operator=(ASTnode) = delete;
    ASTnode(ASTnode &) = delete;
    ASTnode(Span p);
};
class ASTItem : public ASTnode {
    using ASTnode::ASTnode;

  public:
    virtual ~ASTItem();
};
class ASTtool {
  public:
    ASTtool() = delete;
    static any pack(ASTnode *);
    template <typename T,
              std::enable_if_t<std::is_base_of_v<ASTnode, T>, int> = 0>
    static T *unpack(any x) {
        ASTnode **v = any_cast<ASTnode *>(&x);
        if (!v)
            throw MyErr("wrong ASTvisitor return value");
        if (!*v)
            return nullptr;
        T *tmp = dynamic_cast<T *>(*v);
        if (!tmp)
            throw MyErr("AST dynamic_cast failed");
        return tmp;
    }
};
