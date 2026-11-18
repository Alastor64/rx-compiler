#include "SemanticChecker.hpp"
#include "AST.hpp"
#include "Crate.hpp"
#include "ImplShrink.hpp"
#include "StructDeriveCheck.hpp"
int SemanticChecker::SemanticCheck(ASTCrate *ast) {
    root = ast;
    IS.reset();
    SEATAC.reset();
    CVS.reset();
    return StructDeriveCheck(ast) || IS.visit(ast) || NC.visit(ast) ||
           MS.visit(ast) || SEATAC.visit(ast) || LS.visit(ast) ||
           CVS.visit(ast);
}