#include "MyDef.hpp"
#include "RxLexer.h"
#include "tokenizer.hpp"
#include <ANTLRInputStream.h>
#include <Token.h>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;
int main() {
    ifstream s("a.rx", ios::binary);
    // Tokens t(0);
    // pushTokens(s, t);
    antlr4::ANTLRInputStream input(s);
    RxLexer lexer(&input);
    for (auto &i : lexer.getAllTokens()) {
        cout << i->getType() << ":" << i->getText() << ";" << endl;
    }
    return 0;
}