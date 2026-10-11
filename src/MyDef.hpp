#pragma once
#include <Token.h>
#include <any>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>
typedef std::vector<std::unique_ptr<antlr4::Token>> Tokens;
using std::any;
using std::any_cast;
using std::size_t;
using std::string;
using std::swap;
using std::vector;