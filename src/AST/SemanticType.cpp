#include "SemanticType.hpp"
#include "Crate.hpp"
SemanticType::Layer::Layer(string s) {
    len = 0;
    type = ID;
    id = s;
    if (id.empty())
        type = UNIT;
}
SemanticType::Layer::Layer(string s, ASTCrate *root) {
    len = 0;
    if (root->_structs.find(s) != root->_structs.end()) {
        type = ID;
        id = s;
        if (id.empty())
            type = UNIT;
    } else {
        if (s == "Vec") {
            type = VEC;
            id = "";
        } else if (s == "Box") {
            type = BOX;
            id = "";
        } else {
            type = ID;
            id = s;
            if (id.empty())
                type = UNIT;
        }
    }
}
SemanticType::Layer::Layer() {
    len = 0;
    type = UNDEF;
}