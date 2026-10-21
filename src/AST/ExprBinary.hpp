#pragma once
#include "AST.hpp"
#include "Expr.hpp"
#include "MyClasses.hpp"
#include "MyDef.hpp"
#include "RuleText.hpp"
#include "myErr.hpp"
#include <Parser.h>
#include <ParserRuleContext.h>
#include <tree/ParseTreeVisitor.h>
class ExprBinary {
  private:
    static any work(antlr4::tree::ParseTreeVisitor *visitor,
                    const vector<string> &op,
                    const vector<antlr4::ParserRuleContext *> children) {
        if (children.size() != op.size() + 1)
            throw MyErr("invalid binary expr!");
        if (op.empty())
            return children.front()->accept(visitor);
        ASTExpr *res =
            ASTtool::unpack<ASTExpr>(children.front()->accept(visitor));
        if (!res)
            throw MyErr("empty binary left son");
        Span p = Span::getRuleSpan(children.front());
        for (int i = 0; i < op.size(); i++) {
            p.end = Span::getRuleSpan(children.at(i + 1)).end;
            ASTOBinary *tmp = new ASTOBinary(p);
            tmp->op = op.at(i);
            tmp->left = res;
            tmp->right =
                ASTtool::unpack<ASTExpr>(children.at(i + 1)->accept(visitor));
            res = tmp;
            if (!tmp->right)
                throw MyErr("empty binary right son");
        }
        return ASTtool::pack(res);
    }

  public:
    ExprBinary() = delete;
    template <typename T, typename U, typename Y, typename Z>
    static any build(antlr4::tree::ParseTreeVisitor *visitor,
                     const vector<T *> &op, const vector<U *> &pre,
                     const vector<Y *> &mid, const vector<Z *> &suc) {
        return work(visitor, RuleText::get(op),
                    PtrVec<antlr4::ParserRuleContext>::tran(pre, mid, suc));
    }
    template <typename T, typename U, typename Y, typename Z>
    static any build(antlr4::tree::ParseTreeVisitor *visitor, const string &op,
                     const vector<U *> &pre, const vector<Y *> &mid,
                     const vector<Z *> &suc) {
        return work(
            visitor,
            vector<string>(pre.size() + mid.size() + suc.size() - 1, op),
            PtrVec<antlr4::ParserRuleContext>::tran(pre, mid, suc));
    }
};