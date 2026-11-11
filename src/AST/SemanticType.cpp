#include "SemanticType.hpp"
#include "Crate.hpp"
SemanticType::Layer::Layer(string s) {
    type = ID;
    id = s;
}
SemanticType::Layer::Layer(string s, ASTCrate *root) {
    if (root->_structs.find(s) != root->_structs.end()) {
        type = ID;
        id = s;
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
        }
    }
}