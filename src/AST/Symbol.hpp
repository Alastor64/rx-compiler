#pragma once
#include "Block.hpp"
#include "Constant.hpp"
#include "FuncDef.hpp"
#include "Param.hpp"
#include "Struct.hpp"
// class Symbol {
//   public:
//     enum class Type {
//         UNDEF,
//         CONST,
//         DEFFUNC,
//         INNERFUNC,
//         VAR,
//         PARAM,
//         IO,
//     };
//     enum class IOFunc {
//         GET_I32,
//         PRINT_I32,
//         PRINTLN_I32,
//     };
//     enum class OwnerType {
//         UNDEF,
//         VEC,
//         BOX,
//         SELFDEF,
//     };
//     enum class InnerFunc {
//         UNDEF,
//         NEW,
//         LEN,
//         CLONE,
//         PUSH,
//     };
//     Type type;
//     OwnerType ownerType;
//     InnerFunc innerFunc;
//     ASTStruct *owner;
//     ASTConstant *constant;
//     ASTFuncDef *deffunc;
//     ASTLet *let;
//     ASTParam *param;
//     Symbol();
// };