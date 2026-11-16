#pragma once
#include "Constant.hpp"
#include "Crate.hpp"
#include "Expr.hpp"
#include "MyDef.hpp"
#include "SemanticType.hpp"
#include "Type.hpp"
#include "myErr.hpp"
class SemanticTool {
  public:
    SemanticTool() = delete;
    static string I32, U32, ISIZE, USIZE, BOOL;
    static int if_basic(string s);
    // if success,delete the node
    static int basicTypeTran(ASTType *&node, SemanticType &, ASTCrate *root);
    // only handle EPath represent constant
    // need SelfErase
    static int constPathAnalysis(ASTCrate *root, ASTEPath *node,
                                 ASTConstant *&);
    // note: not compete yet!!!
    static int basicTypeConvertable(const SemanticType &actual,
                                    const SemanticType &target);
    // ret if overflow uint,note overflow won't disturb the calculate,the ans
    // will be anded 2^32-1
    static int calIntValue(const string &s, unsigned int &res, int &overflow);
    static int ifDigital(char c);
};