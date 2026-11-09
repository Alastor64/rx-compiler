#pragma once
#include "ASTvisitor.hpp"
#include "Crate.hpp"
#include "Struct.hpp"
#include <vector>
class SelfErase : public ASTvisitor {
  public:
    vector<string> fa;
    void reset();
    virtual any visitStruct(ASTStruct *ast) override;
    virtual any visitImpl(ASTImpl *ast) override;
};