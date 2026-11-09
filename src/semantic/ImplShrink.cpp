#include "ImplShrink.hpp"
#include "AST.hpp"
#include "Crate.hpp"
#include "Impl.hpp"
#include "Path.hpp"
void ImplShrink::reset() { id = ""; }
int ImplShrink::visitChildren(ASTnode *node) { return 1; }
int ImplShrink::visitCrate(ASTCrate *node) {
    int res = 0;
    for (auto i : node->impls) {
        res |= i->accept(this);
    }
    return res;
}
int ImplShrink::visitImpl(ASTImpl *node) {
    int res = node->type->accept(this);
    if (res)
        return 1;
    if (id.empty())
        return 1;
    node->id = id;
    id = "";
    delete node->type;
    node->type = nullptr;
    return res;
}
int ImplShrink::visitTPath(ASTTPath *node) {
    if (node->path.size() != 1)
        return 1;
    return node->path.front()->accept(this);
}
int ImplShrink::visitPathSeg(ASTPathSeg *node) {
    if (!node->args.empty())
        return 1;
    if (!id.empty())
        return 1;
    id = node->id;
    return 0;
}