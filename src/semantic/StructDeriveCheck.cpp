#include "StructDeriveCheck.hpp"
#include "Crate.hpp"
#include "Struct.hpp"
bool StructMultiDeriveCheck(ASTStruct *ast) { return ast->derive.err(); }
bool StructMultiDeriveCheck(ASTCrate *ast) {
    for (auto i : ast->structs) {
        if (StructMultiDeriveCheck(i))
            return 1;
    }
    return 0;
}