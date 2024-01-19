#include <iostream>

using namespace std;

enum TokenType {
    Number,
    Identifier,
    Equals,
    Let,
    OpenParen, 
    CloseParen,
    BinaryOpterator
};

class Token {
    string value;
    TokenType token;
};

vector<Token> Tokenize(string source) {
    vector<Token> tokens;

    // Tokenize source code to token
    for (char c: source) {

    }

    return tokens;
};