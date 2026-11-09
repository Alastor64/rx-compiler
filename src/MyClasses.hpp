#pragma once
#include "MyDef.hpp"
#include <utility>
class ASTnode;
class ASTType;
class ASTPathSeg;
class ASTLet;
class ASTStatement;
class ASTBlock;
class ASTCrate;
class ASTFuncDef;
class ASTStruct;
class ASTConstant;
class ASTImpl;
class ASTParam;
class ASTSelfParam;
class ASTPathSeg;
class ASTLet;
class ASTStatement;
class ASTBlock;

class ASTType;
class ASTTRef;
class ASTTArray;
class ASTTUnit;
class ASTTPath;

class ASTExpr;
class ASTEUnit;
class ASTEPath;
class ASTEIf;
class ASTEWhile;
class ASTEStruct;
class ASTELiteral;
class ASTEArray;
class ASTERepeat;
class ASTEBranch;
class ASTEOperator;
class ASTOBinary;
class ASTOUnary;
class ASTOCall;
class ASTOIndex;
class ASTOField;
class ASTOMethod;
class ASTOAssign;
class ASTOCast;
class ASTOShift;

template <typename T> class PtrVec {
  public:
    PtrVec() = delete;
    template <typename U, typename V, typename W>
    static vector<T *> tran(const vector<U *> &x, const vector<V *> &y,
                            const vector<W *> z) {
        vector<T *> tmp;
        for (auto i : x)
            tmp.push_back(dynamic_cast<T *>(i));
        for (auto i : y)
            tmp.push_back(dynamic_cast<T *>(i));
        for (auto i : z)
            tmp.push_back(dynamic_cast<T *>(i));
        return std::move(tmp);
    }
};
template <typename T> vector<T *> makePtrVec(T *x) {
    if (x)
        return vector<T *>(1, x);
    else
        return vector<T *>(0);
}
