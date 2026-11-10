#include "SelfEraseAndTypeArgsCheck.hpp"
#include "Crate.hpp"
#include "Impl.hpp"
#include "Path.hpp"
#include "Struct.hpp"
void SelfEraseAndTypeArgsCheck::reset() { fa.clear(); }
int SelfEraseAndTypeArgsCheck::visitCrate(ASTCrate *node) {
    root = node;
    return node->visitChildren(this);
}
int SelfEraseAndTypeArgsCheck::visitStruct(ASTStruct *node) {
    fa = node->name;
    int res = node->visitChildren(this);
    fa.clear();
    return res;
}
int SelfEraseAndTypeArgsCheck::visitPathSeg(ASTPathSeg *node) {
    if (node->id == "Self") {
        if (fa.empty())
            return 1;
        if (!node->args.empty())
            return 1;
        node->id = fa;
    } else if ((node->id == "Vec" || node->id == "Box") &&
               root->_structs.find(node->id) == root->_structs.end()) {
        if (node->args.size() != 1)
            return 1;
    } else {
        if (!node->args.empty())
            return 1;
    }
    return 0;
}