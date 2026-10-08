#include "MyDef.hpp"
#include "RxLexer.h"
#include "tokenizer.hpp"
#include <ANTLRInputStream.h>
#include <Token.h>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;
bool invalid_token(int t) {
    switch (t) {
    case RxLexer::INVALID_CHARACTER_LITERAL:
    case RxLexer::INVALID_LIFETIME:
    case RxLexer::INVALID_NUMBER:
    case RxLexer::UNTERMINATED_BLOCK_COMMENT:
    case RxLexer::ERROR_CHAR:
        return 1;
    default:
        return 0;
    }
}
int main() {
    ifstream s("a.rx", ios::binary);
    // Tokens t(0);
    // pushTokens(s, t);
    antlr4::ANTLRInputStream input(s);
    RxLexer lexer(&input);
    for (auto &i : lexer.getAllTokens()) {
        if (invalid_token(i->getType())) {
            cout << "lexer reject" << endl;
            return 0;
        }
    }
    for (auto &i : lexer.getAllTokens()) {
        cout << i->getType() << ":" << i->getText() << ";" << endl;
    }
    return 0;
}