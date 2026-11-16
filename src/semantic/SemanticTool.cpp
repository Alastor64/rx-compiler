#include "SemanticTool.hpp"
#include "Constant.hpp"
#include "Crate.hpp"
#include "Path.hpp"
#include "SemanticType.hpp"
#include "Struct.hpp"
string SemanticTool::BOOL = "bool", SemanticTool::I32 = "i32",
       SemanticTool::ISIZE = "isize", SemanticTool::U32 = "u32",
       SemanticTool::USIZE = "usize";
int SemanticTool::if_basic(string s) {
    return s == BOOL || s == I32 || s == U32 || s == ISIZE || s == USIZE;
}
int SemanticTool::basicTypeTran(ASTType *&node, SemanticType &res,
                                ASTCrate *root) {
    if (auto tmp = dynamic_cast<ASTTPath *>(node)) {
        if (tmp->path.size() != 1)
            return 1;
        if (!if_basic(tmp->path.front()->id))
            return 1;
        res.setType(tmp->path.front()->id, root);
        delete node;
        node = nullptr;
        return 0;
    } else
        return 1;
}
int SemanticTool::constPathAnalysis(ASTCrate *root, ASTEPath *node,
                                    ASTConstant *&res) {
    string tmp;
    ASTStruct *owner;
    switch (node->path.size()) {
    case 1:
        tmp = node->path.at(0)->id;
        if (root->_consts.find(tmp) == root->_consts.end())
            return 1;
        res = root->_consts[tmp];
        break;
    case 2:
        tmp = node->path.at(0)->id;
        if (root->_structs.find(tmp) == root->_structs.end())
            return 1;
        owner = root->_structs[tmp];
        tmp = node->path.at(1)->id;
        if (owner->_consts.find(tmp) == owner->_consts.end())
            return 1;
        res = owner->_consts[tmp];
        break;
    default:
        return 1;
    }
    return 0;
}
int SemanticTool::basicTypeConvertable(const SemanticType &_actual,
                                       const SemanticType &_target) {
    if (_actual.layers.size() != 1 || _target.layers.size() != 1)
        return 1;
    const SemanticType::Layer &actual = _actual.layers.front();
    const SemanticType::Layer &target = _target.layers.front();
    if (actual == target)
        return 1;
    if (actual.type != SemanticType::Layer::INT || !target.ifint())
        return 0;
    if (actual.len != target.len)
        return 0;
    return 1;
}
int SemanticTool::ifDigital(char c) { return c >= '0' && c <= '9'; }
int SemanticTool::calIntValue(const string &s, unsigned int &res,
                              int &overflow) {
    unsigned long long tmp = 0, base = 10;
    overflow = 0;
    int start = 0;
    if (s.length() >= 2 && s[1] != '_') {
        if (s[0] == '0' && !ifDigital(s[1])) {
            if (s[1] == 'x') {
                base = 16;
            } else if (s[1] == 'o') {
                base = 8;
            } else if (s[1] == 'b') {
                base = 2;
            } else
                return 1;
            start = 2;
        }
    }
    for (int _ = start; _ < s.length(); _++) {
        auto i = s[_];
        if (i == '_')
            continue;
        unsigned long long a;
        if (!ifDigital(i)) {
            if (i >= 'a' && i <= 'f') {
                a = i - 'a' + 10;
            } else if (i >= 'A' && i <= 'F') {
                a = i - 'A' + 10;
            } else
                return 1;
        } else
            a = i - '0';
        if (a >= base)
            return 1;
        tmp *= base;
        tmp += a;
        if (tmp >= (1llu << 32)) {
            overflow = 1;
        }
        tmp &= (1llu << 32) - 1;
    }
    res = tmp;
    return 0;
}