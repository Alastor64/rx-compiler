#include "MyDef.hpp"
#include "MyParserVisitor.hpp"
#include "RxParser.h"
#include <utility>
any MyParserVisitor::visitIdentifier(RxParser::IdentifierContext *ctx) {
    return any(ctx->getText());
}
any MyParserVisitor::visitIdentifierBinding(
    RxParser::IdentifierBindingContext *ctx) {
    std::string tmp = any_cast<std::string>(ctx->identifier()->accept(this));
    return std::make_pair(std::move(tmp), bool(ctx->MUT()));
}