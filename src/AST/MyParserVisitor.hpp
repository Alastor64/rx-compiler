#pragma once
#include "MyDef.hpp"
#include "RxParserBaseVisitor.h"
class MyParserVisitor : public RxParserBaseVisitor {
    virtual any visitCrate(RxParser::CrateContext *ctx) override;
};