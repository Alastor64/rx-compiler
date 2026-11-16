#include "SemanticType.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
#include "myErr.hpp"
SemanticType::Layer::Layer() {
    len = 0;
    type = UNDEF;
    _struct = nullptr;
}
SemanticType::Layer::Layer(int _type) : Layer() { type = _type; }
SemanticType::Layer::Layer(string s, ASTCrate *root) : Layer() {
    if (root->_structs.find(s) != root->_structs.end()) {
        type = STRUCT;
        _struct = root->_structs.find(s)->second;
    } else {
        if (s == "bool") {
            type = BOOL;
        } else if (s == "Vec") {
            type = VEC;
        } else if (s == "Box") {
            type = BOX;
        } else if (s == "") {
            type = UNIT;
        } else if (getIntType(s) != ERRMARK) {
            type = getIntType(s);
        } else
            throw MyErr("unknown layer");
    }
}
bool SemanticType::operator==(const SemanticType &x) const {
    return layers == x.layers;
}
bool SemanticType::operator!=(const SemanticType &x) const {
    return !((*this) == x);
}
bool SemanticType::Layer::operator==(const Layer &x) const {
    if (type != x.type)
        return 0;
    if (muts != x.muts)
        return 0;
    if (len != x.len)
        return 0;
    if (type == STRUCT && _struct != x._struct)
        return 0;
    return 1;
}
bool SemanticType::Layer::operator!=(const Layer &x) const {
    return !((*this) == x);
}
SemanticType::Layer &SemanticType::outter() { return layers.front(); }
const SemanticType::Layer &SemanticType::outter() const {
    return layers.front();
}
int SemanticType::Layer::unsign() const { return type == U32 || type == USIZE; }
int SemanticType::Layer::ifint() const {
    return type == INT || type == U32 || type == USIZE || type == I32 ||
           type == ISIZE;
}
void SemanticType::setBool() {
    layers.clear();
    layers.push_back(Layer(SemanticType::Layer::BOOL));
}
void SemanticType::setInt() {
    layers.clear();
    layers.push_back(Layer(SemanticType::Layer::INT));
}
void SemanticType::setType(string s, ASTCrate *root) {
    layers.clear();
    layers.push_back(Layer(s, root));
}