#include "ConstValueErase.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
#include "SemanticTool.hpp"
#include "SemanticType.hpp"
#include "Type.hpp"
#include "myErr.hpp"
int ConstValueErase::visitCrate(ASTCrate *node) {
    root = node;
    return node->visitChildren(this);
}
int ConstValueErase::calLen(ASTExpr *&len, unsigned int &_len) {
    if (auto value = dynamic_cast<ASTEPath *>(len)) {
        ASTConstant *target;
        if (SemanticTool::constPathAnalysis(root, value, target))
            return 1;
        if (target->semanticType.outter().type != SemanticType::Layer::USIZE)
            return 1;
        _len = target->_value;
    } else if (auto value = dynamic_cast<ASTELiteral *>(len)) {
        if (value->semanticType.outter() != SemanticType::Layer::USIZE &&
            value->semanticType.outter() != SemanticType::Layer::INT)
            return 1;
        _len = value->value;
    } else
        return 1;
    if (_len == 0)
        throw MyErr("Zero length array!");
    delete len;
    len = nullptr;
    return 0;
}
int ConstValueErase::visitTArray(ASTTArray *node) {
    if (calLen(node->len, node->_len))
        return 1;
    return node->visitChildren(this);
}
int ConstValueErase::visitERepeat(ASTERepeat *node) {
    if (calLen(node->len, node->_len))
        return 1;
    return node->visitChildren(this);
}