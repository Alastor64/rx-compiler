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
int SemanticType::Layer::generate(string s, ASTCrate *root, Layer &res) {
    res = Layer();
    if (root->_structs.find(s) != root->_structs.end()) {
        res.type = STRUCT;
        res._struct = root->_structs.find(s)->second;
    } else {
        if (s == "bool") {
            res.type = BOOL;
        } else if (s == "Vec") {
            res.type = VEC;
        } else if (s == "Box") {
            res.type = BOX;
        } else if (s == "") {
            res.type = UNIT;
        } else if (getIntType(s) != ERRMARK) {
            res.type = getIntType(s);
        } else
            return 1;
    }
    return 0;
}
SemanticType::Layer::Layer(string s, ASTCrate *root) {
    if (generate(s, root, *this))
        throw MyErr("unknown layer");
}
void SemanticType::clear() { layers.clear(); }
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
SemanticType::Layer &SemanticType::outter() { return layers.back(); }
const SemanticType::Layer &SemanticType::outter() const {
    return layers.back();
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
void SemanticType::setType(int t) {
    layers.clear();
    layers.push_back(Layer(t));
}
void SemanticType::setInt() {
    layers.clear();
    layers.push_back(Layer(SemanticType::Layer::INT));
}
void SemanticType::setType(string s, ASTCrate *root) {
    layers.clear();
    layers.push_back(Layer(s, root));
}