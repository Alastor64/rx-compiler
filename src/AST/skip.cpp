
#include "AST.hpp"
#include "MyParserVisitor.hpp"
std::any
MyParserVisitor::visitUseDeclaration(RxParser::UseDeclarationContext *ctx) {
    return ASTtool::pack(nullptr);
}

std::any MyParserVisitor::visitUseTree(RxParser::UseTreeContext *ctx) {
    return ASTtool::pack(nullptr);
}

std::any MyParserVisitor::visitUsePath(RxParser::UsePathContext *ctx) {
    return ASTtool::pack(nullptr);
}

std::any
MyParserVisitor::visitUsePathSegment(RxParser::UsePathSegmentContext *ctx) {
    return ASTtool::pack(nullptr);
}
