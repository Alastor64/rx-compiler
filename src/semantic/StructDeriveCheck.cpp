#include "StructDeriveCheck.hpp"
#include "Crate.hpp"
#include "Struct.hpp"
bool StructDeriveCheck(ASTStruct *ast) { return ast->derive.err(); }
bool StructDeriveCheck(ASTCrate *ast) {
    for (auto i : ast->structs) {
        if (StructDeriveCheck(i))
            return 1;
    }
    return 0;
}