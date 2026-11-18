#include "LiteralShrink.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
#include "SemanticTool.hpp"
#include "myErr.hpp"
int LiteralShrink::visitCrate(ASTCrate *node) {
    root = node;
    return node->visitChildren(this);
}
int LiteralShrink::visitELiteral(ASTELiteral *node) {
    if (node->type == ASTELiteral::BOOL) {
        node->semanticType.setBool();
        node->value = bool(node->if_true);
        return 0;
    }
    if (node->type == ASTELiteral::INT) {
        const auto &S = node->int_text;
        node->semanticType.setInt();
        string text = S;
        // i32 u32
        string suc = "";
        if (S.size() >= 3) {
            suc = S.substr(S.length() - 3, 3);
        }
        if (SemanticType::Layer::getIntType(suc) !=
            SemanticType::Layer::ERRMARK) {
            node->semanticType.setType(suc, root);
            text = S.substr(0, S.length() - 3);
        }

        // isize usize
        suc = "";
        if (S.size() >= 5) {
            suc = S.substr(S.length() - 5, 5);
        }
        if (SemanticType::Layer::getIntType(suc) !=
            SemanticType::Layer::ERRMARK) {
            node->semanticType.setType(suc, root);
            text = S.substr(0, S.length() - 5);
        }
        int overflow = 0;
        if (SemanticTool::calIntValue(text, node->value, overflow))
            return 1;
        if (overflow)
            throw MyErr("Literal Overflow");
        return 0;
    }
    return 1;
}