#include "Param.hpp"
#include "AST.hpp"
#include "ASTvisitor.hpp"
#include "ChildrenTool.hpp"
#include "MyParserVisitor.hpp"
int ASTParam::accept(ASTvisitor *visitor) { return visitor->visitParam(this); }

ASTParam::ASTParam(Span p) : ASTnode(p) { if_mut = 0; }
ASTParam::~ASTParam() {
    delete type;
    type = nullptr;
}
any MyParserVisitor::visitFunctionParam(RxParser::FunctionParamContext *ctx) {
    auto tmp = any_cast<std::pair<string, bool>>(
        ctx->identifierBinding()->accept(this));
    auto res = new ASTParam(Span::getRuleSpan(ctx));
    res->if_mut = tmp.second;
    res->name = std::move(tmp.first);
    res->type = ASTtool::unpack<ASTType>(ctx->typeRef()->accept(this));
    return ASTtool::pack(res);
}

int ASTParam::visitChildren(ASTvisitor *visitor) {
    return ChildrenTool::visitChild(type, visitor);
}
