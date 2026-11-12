#include "ConstValueShrink.hpp"
#include "ChildrenTool.hpp"
#include "Constant.hpp"
#include "Crate.hpp"
#include "Path.hpp"
#include "SemanticTool.hpp"
#include "Type.hpp"
typename ConstValueShrink::MP tmp;
void ConstValueShrink::reset() { tmp.clear(); }
int ConstValueShrink::visitCrate(ASTCrate *node) {
    root = node;
    for (auto _ : node->_consts) {
        auto i = _.second;
        if (SemanticTool::basicTypeTran(i->type, i->semanticType))
            return 1;
    }
    for (auto _ : node->_structs) {
        for (auto __ : _.second->_consts) {
            auto i = __.second;
            if (SemanticTool::basicTypeTran(i->type, i->semanticType))
                return 1;
        }
    }
    for (auto _ : node->_consts) {
        auto i = _.second;
        if (i->accept(this))
            return 1;
    }
    for (auto _ : node->_structs) {
        for (auto __ : _.second->_consts) {
            auto i = __.second;
            if (i->accept(this))
                return 1;
        }
    }
    return ChildrenTool::visitMap(node->_funcs, this);
}
int ConstValueShrink::visitConstant(ASTConstant *node) {
    if (!node->semanticType.layers.empty())
        return 0; // necessary?
    if (tmp.find(node) != tmp.end())
        return 1;
    tmp[node] = 1;
    if (auto value = dynamic_cast<ASTTPath *>(node->value)) {
        ASTConstant *target = nullptr;
        const auto &path = value->path;
        if (path.size() == 1) {
            auto fd = root->_consts.find(path.front()->id);
            if (fd == root->_consts.end())
                return 1;
            target = fd->second;
        } else if (path.size() == 2) {
            auto fd = root->_structs.find(path.front()->id);
            if (fd == root->_structs.end())
                return 1;
            auto owner = fd->second;
            auto fd2 = owner->_consts.find(path.at(1)->id);
            if (fd2 == root->_consts.end())
                return 1;
            target = fd2->second;
        }
        if (target->semanticType.layers.empty())
            if (target->accept(this))
                return 1;
    }
    tmp.erase(node);
}