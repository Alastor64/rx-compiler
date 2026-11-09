#pragma once
#include "AST.hpp"
#include "ASTvisitor.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
#include "Impl.hpp"
#include "Path.hpp"
#include "Type.hpp"
// return correctly only when visit crate/item(impl) otherwise return 1
class ImplShrink : public ASTvisitor {
  public:
    string id;
    void reset();
    int visitChildren(ASTnode *) override;
    int visitCrate(ASTCrate *) override;
    int visitImpl(ASTImpl *) override;
    int visitTPath(ASTTPath *) override;
    int visitPathSeg(ASTPathSeg *) override;
};