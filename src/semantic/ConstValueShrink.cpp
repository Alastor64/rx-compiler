#include "ConstValueShrink.hpp"
#include "ChildrenTool.hpp"
#include "Constant.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
#include "Path.hpp"
#include "SemanticTool.hpp"
#include "SemanticType.hpp"
#include "Type.hpp"
#include "myErr.hpp"
typename ConstValueShrink::MP ConstValueShrink::vis;
void ConstValueShrink::reset() {
    vis.clear();
    results.clear();
}
int ConstValueShrink::visitCrate(ASTCrate *node) {
    root = node;
    for (auto _ : node->_consts) {
        auto i = _.second;
        if (SemanticTool::basicTypeTran(i->type, i->semanticType, root))
            return 1;
    }
    for (auto _ : node->_structs) {
        for (auto __ : _.second->_consts) {
            auto i = __.second;
            if (SemanticTool::basicTypeTran(i->type, i->semanticType, root))
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
    return 0;
}
int ConstValueShrink::visitConstant(ASTConstant *node) {
    if (!node->value)
        return 0;
    if (vis.find(node) != vis.end())
        return 1;
    vis[node] = 1;
    if (auto value = dynamic_cast<ASTEPath *>(node->value)) {
        ASTConstant *target;
        if (SemanticTool::constPathAnalysis(root, value, target))
            return 1;
        if (target->semanticType != node->semanticType)
            return 1;
        if (target->accept(this))
            return 1;
        node->_value = target->_value;
    } else if (auto value = dynamic_cast<ASTOUnary *>(node->value)) {
        if (value->op != "-")
            return 1;
        if (value->accept(this))
            return 1;
        SemanticType &my = node->semanticType,
                     &actual = node->value->semanticType;
        if (my.outter().unsign())
            return 1;
        if (!SemanticTool::basicTypeConvertable(actual, my)) {
            return 1;
        }
        if (results.empty())
            return 1;
        ConstexprValue res = results.back();
        results.pop_back();
        if (res.overflow)
            return 1;
        if (my.outter().unsign()) {
            return 1;
        }
        // if (res.value > (1u << 31)) {
        //     return 1;
        // }
        // if (res.value == (1u << 31)) {
        //     if (res.minus)
        //         return 1;
        // }
        node->_value = res.value;
    } else if (auto value = dynamic_cast<ASTELiteral *>(node->value)) {
        if (value->accept(this))
            return 1;
        SemanticType &actual = value->semanticType, &my = node->semanticType;
        if (!SemanticTool::basicTypeConvertable(actual, my))
            return 1;
        if (results.empty())
            throw MyErr("empty result");
        ConstexprValue res = results.back();
        results.pop_back();
        if (my.outter().ifint()) {
            if (res.overflow)
                return 1;
            if (!my.outter().unsign()) {
                if (res.value >= (1u << 31))
                    return 1;
            }
        }
        node->_value = res.value;
    } else
        return 1;
    delete node->value;
    node->value = nullptr;
    vis.erase(node);
    return 0;
}
int ConstValueShrink::visitELiteral(ASTELiteral *node) {
    ConstexprValue tmp;
    if (node->type == ASTELiteral::BOOL) {
        node->semanticType.setBool();
        tmp.value = bool(node->if_true);
        results.push_back(tmp);
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
        if (SemanticTool::calIntValue(text, tmp.value, tmp.overflow))
            return 1;
        results.push_back(tmp);
        return 0;
    }
    return 1;
}
int ConstValueShrink::visitOUnary(ASTOUnary *node) {
    ConstexprValue tmp;
    if (node->op != "-")
        return 1;
    if (!node->inner)
        return 1;
    if (auto value = dynamic_cast<ASTEPath *>(node->inner)) {
        ASTConstant *target;
        if (SemanticTool::constPathAnalysis(root, value, target))
            return 1;
        if (target->accept(this))
            return 1;
        node->semanticType = target->semanticType;
        const auto &t = node->semanticType.outter();
        if (t.unsign())
            return 1;
        if (!t.ifint())
            return 1;
        tmp.value = -target->_value;
        if (tmp.value == (1u << 31)) {
            return 1;
        }
    } else if (auto value = dynamic_cast<ASTELiteral *>(node->inner)) {
        if (value->accept(this))
            return 1;
        if (results.empty())
            throw MyErr("empty result");
        tmp = results.back();
        results.pop_back();
        const auto &t = value->semanticType.outter();
        if (!t.ifint())
            return 1;
        if (t.unsign())
            return 1;
        if (tmp.value > (1u << 31))
            return 1;
        node->semanticType = value->semanticType;
        tmp.value = -tmp.value;
    } else
        return 1;
    tmp.minus = 1;
    results.push_back(tmp);
    delete node->inner;
    node->inner = nullptr;
    return 0;
}