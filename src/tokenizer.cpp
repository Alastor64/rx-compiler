#include "tokenizer.hpp"
#include "MyDef.hpp"
#include "RxLexer.h"
#include <ANTLRInputStream.h>
#include <fstream>
void pushTokens(std::ifstream &input, Tokens &tokens) {
    antlr4::ANTLRInputStream tmp(input);
    RxLexer lexer(&tmp);
    for (auto &i : lexer.getAllTokens()) {
        tokens.push_back(std::move(i));
    }
}