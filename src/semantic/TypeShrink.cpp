#include "TypeShrink.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
#include "FuncDef.hpp"
#include "MyDef.hpp"
#include "Param.hpp"
#include "Path.hpp"
#include "SemanticType.hpp"
#include "Struct.hpp"
#include "Type.hpp"
void TypeShrink::reset() {
    root = nullptr;
    result.clear();
}
int TypeShrink::visitCrate(ASTCrate *node) {
    root = node;
    return node->visitChildren(this);
}
int TypeShrink::shrink(ASTType *&node, SemanticType &res) {
    result.clear();
    if (node->accept(this))
        return 1;
    res.clear();
    swap(res, result);
    delete node;
    node = nullptr;
    return 0;
}
int TypeShrink::visitTUnit(ASTTUnit *node) {
    if (!result.layers.empty())
        throw "Unit not innest";
    result.setType(SemanticType::Layer::UNIT);
    return 0;
}
int TypeShrink::visitTArray(ASTTArray *node) {
    if (node->elem->accept(this))
        return 1;
    result.layers.push_back(SemanticType::Layer(SemanticType::Layer::ARRAY));
    result.outter().len = node->_len;
    return 0;
}
int TypeShrink::visitTRef(ASTTRef *node) {
    if (node->inner->accept(this))
        return 1;
    result.outter().muts.push_back(node->if_mut);
    return 0;
}
int TypeShrink::visitTPath(ASTTPath *node) {
    if (node->path.size() == 1) {
        SemanticType::Layer tmp;
        const auto &seg = node->path.front();
        if (SemanticType::Layer::generate(seg->id, root, tmp))
            return 1;
        if (!seg->args.empty()) {
            if (seg->args.front()->accept(this))
                return 1;
        }
        result.layers.push_back(tmp);
        return 0;
    }
    return 1;
}
int TypeShrink::visitParam(ASTParam *node) {
    if (shrink(node->type, node->semanticType))
        return 1;
    return node->visitChildren(this);
}
int TypeShrink::visitLet(ASTLet *node) {
    if (!node->undef) {
        if (node->type && shrink(node->type, node->semanticType))
            return 1;
    } else {
        node->undef = 0;
        node->semanticType.setType(SemanticType::Layer::UNDEF);
    }
    return node->visitChildren(this);
}
int TypeShrink::visitOCast(ASTOCast *node) {
    if (shrink(node->type, node->semanticType))
        return 1;
    return node->visitChildren(this);
}
int TypeShrink::visitSField(ASTSField *node) {
    if (shrink(node->type, node->semanticType))
        return 1;
    return node->visitChildren(this);
}
int TypeShrink::visitFuncDef(ASTFuncDef *node) {
    if (shrink(node->ret, node->semanticType))
        return 1;
    return node->visitChildren(this);
}