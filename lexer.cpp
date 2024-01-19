#include <iostream>
#include <map>

using namespace std;

// Static variables 
static map<string, TokenType> typeMap {{"let", Let}};

enum TokenType {
    Number,
    Identifier,
    Equals,
    Let,
    OpenParen, 
    CloseParen,
    BinaryOpterator
};

// Classes      
class Token {
    public: 
        string value;
        TokenType token;
        // Constructors
        Token(char character, TokenType tokenType) { 
            this -> value = character;
            this -> token = tokenType;
        };

        Token(string character, TokenType tokenType) { 
            this -> value = character;
            this -> token = tokenType;
        };

        Token() = default;
};

bool isSkippable(string str) {
    return str == " " || str == "\n" || str == "\t";
}

vector<Token> Tokenize(string source) {
    vector<Token> tokens;
    // Tokenize source code to token
    for (int idx = 0; idx < source.size(); idx ++) {
        if (source[idx] == '(') tokens.push_back(Token(source[idx], OpenParen));
        else if (source[idx] == ')') tokens.push_back(Token(source[idx], CloseParen));
        else if (source[idx] == '*' || source[idx] == '/' || source[idx] == '+' || source[idx] == '-') tokens.push_back(Token(source[idx], BinaryOpterator));
        else if (source[idx] == '=') tokens.push_back(Token(source[idx], Equals));
        else {
            // multi character tokens
            string val = "";
            if (isdigit(source[idx])) {
                while (idx < source.size() && isdigit(source[idx])) {
                    val += source[idx++];
                }
                tokens.push_back(Token(val, Number));
            } else if (isalpha(source[idx])) {
                while (idx < source.size() && isalnum(source[idx])) {
                    val += source[idx++];
                }
                // Check if keyword was reserved
                if (typeMap.count(val)) {
                    tokens.push_back(Token(val, typeMap[val]));
                } else {
                    tokens.push_back(Token(val, Identifier));
                }
            } else if (isSkippable(val)) {
                // don't really have to do anything here
                continue;
            } else {
                cout << "Error";
                exit(0);
            }
        }
    }

    return tokens;
};