#pragma once
#include <ParserRuleContext.h>
#include <Token.h>
struct Span {
  public:
    int begin, end;
    static Span getRuleSpan(antlr4::ParserRuleContext *ctx) {
        antlr4::Token *s = ctx->getStart();
        antlr4::Token *e = ctx->getStop();
        if (s == nullptr)
            return Span{};
        int begin = s->getStartIndex();
        int end;
        if (e && s->getStartIndex() <= e->getStopIndex())
            end = e->getStopIndex() + 1;
        else
            end = begin;
        return Span{begin, end};
    }
    static Span getTokenSpan(antlr4::Token *tk) {
        return Span{int(tk->getStartIndex()), int(tk->getStopIndex()) + 1};
    }
};
class ASTnode {
  public:
    virtual ~ASTnode();

  protected:
    ASTnode();
};
class ASTnodeItem : public ASTnode {
  protected:
    ASTnodeItem();

  public:
    virtual ~ASTnodeItem();
};