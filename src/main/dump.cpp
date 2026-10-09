#include "MyDef.hpp"
#include "RxLexer.h"
#include "RxParser.h"
#include <ANTLRInputStream.h>
#include <CommonTokenStream.h>
#include <Parser.h>
#include <Token.h>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
#include <tree/ParseTree.h>
#include <tree/Trees.h>
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
int main(int argc, char **args) {
    ifstream s(args[1], ios::binary);
    if (!s)
        return 2;
    // Tokens t(0);
    // pushTokens(s, t);
    antlr4::ANTLRInputStream input(s);
    RxLexer lexer(&input);
    antlr4::CommonTokenStream t(&lexer);
    t.fill();
    for (auto &i : t.getTokens()) {
        if (invalid_token(i->getType())) {
            // cout << "lexer reject" << endl;
            return 1;
        }
    }
    // for (auto &i : lexer.getAllTokens()) {
    //     cout << i->getType() << ":" << i->getText() << ";" << endl;
    // }
    RxParser parser(&t);
    antlr4::tree::ParseTree *cst;
    if (argc < 3) {
        cst = parser.crate();
    } else {
        switch (args[2][0]) {
        case 'c':
            cst = parser.crate();
            break;
        case 'e':
            cst = parser.expression();
            break;
        case 't':
            cst = parser.typeRef();
            break;
        case 'i':
            cst = parser.item();
            break;
        case 'l':
            cst = parser.letStatement();
            break;
        default:
            break;
        }
    }
    if (parser.getNumberOfSyntaxErrors() ||
        parser.getCurrentToken()->getType() != antlr4::Token::EOF)
        return 1;
    // cout << antlr4::tree::Trees::toStringTree(cst, &parser) << endl;
    return 0;
}