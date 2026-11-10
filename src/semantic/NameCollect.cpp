#include "NameCollect.hpp"
#include "Crate.hpp"
#include "Impl.hpp"
#include "Struct.hpp"
typename NameCollect::MP NameCollect::tmp;
int NameCollect::visitCrate(ASTCrate *node) {
    bool res = 0;
    tmp.clear();
    string x;
    if (collect(tmp, node->structs, node->_structs))
        return 1;
    tmp.clear();
    if (collect(tmp, node->funcs, node->_funcs))
        return 1;
    if (collect(tmp, node->consts, node->_consts))
        return 1;
    tmp.clear();
    root = node;
    for (auto i : node->_structs) {
        if (i.second->accept(this))
            return 1;
    }
    while (!node->impls.empty()) {
        auto i = node->impls.back();
        if (i->accept(this))
            return 1;
        delete i;
        node->impls.pop_back();
    }
    return 0;
}
int NameCollect::visitStruct(ASTStruct *node) {
    tmp.clear();
    if (collect(tmp, node->fields, node->_fields))
        return 1;
    tmp.clear();
    return 0;
}
int NameCollect::visitImpl(ASTImpl *node) {
    if (root->_structs.find(node->id) == root->_structs.end())
        return 1;
    ASTStruct *t = root->_structs[node->id];
    if (collectImpl(node->funcs, t->_methods, t->_consts))
        return 1;
    if (collectImpl(node->consts, t->_consts, t->_methods))
        return 1;
    return 0;
}