#include <iostream>
#include <map>
#include "ast.cpp"

using namespace std;

enum TokenType {
    Numbers,
    Identifier,
    Equals,
    Let,
    OpenParen, 
    CloseParen,
    BinaryOperator,
    Eof,
};

enum ErrorType {
    EillegalCharError,
    EinvalidSyntaxError
};

static const char* enumTokenString[] = {"Numbers", "Identifier", "Equals", "Let", "OpenParen", "CloseParen", "BinaryOperator", "EOF"};
static const char* enumErrorString[] = {"IllegalCharError", "InvalidSyntaxError"};
// Static variables
static map<string, TokenType> typeMap {{"let", Let}};

// Classes | Add specific classes for Error    
struct Error {
    public:
        string detail;
        ErrorType err;
        void print() {
            cout << "{" + detail + " : " + enumErrorString[err] + "}\n";
        }
};

class IllegalCharError: public Error {
    public:
    IllegalCharError(string detail) {
        this -> err = EillegalCharError;
        this -> detail = detail;
    }
};

class InvalidSyntaxError: public Error {
    public:
    InvalidSyntaxError(string detail) {
        this -> err = EinvalidSyntaxError;
        this -> detail = detail;
    }

};

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

        void print() {
            cout << "{" + value + ":" + enumTokenString[token] + "}\n";
        }
};

bool isSkippable(string str) {
    return str == "" || str == " " || str == "\n" || str == "\t";
}

pair<vector<Token>, vector<Error>> Tokenize(string source) {
    vector<Token> tokens;
    vector<Error> errors;
    // Tokenize source code to token
    for (int idx = 0; idx < source.size(); idx ++) {
        if (source[idx] == '(') tokens.push_back(Token(source[idx], OpenParen));
        else if (source[idx] == ')') tokens.push_back(Token(source[idx], CloseParen));
        else if (source[idx] == '*' || source[idx] == '/' || source[idx] == '+' || source[idx] == '-') tokens.push_back(Token(source[idx], BinaryOperator));
        else if (source[idx] == '=') tokens.push_back(Token(source[idx], Equals));
        else {
            // multi character tokens
            string val = "";
            if (isdigit(source[idx])) {
                while (idx < source.size() && isdigit(source[idx])) {
                    val += source[idx++];
                }
                tokens.push_back(Token(val, Numbers));
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
                // Error checking invalidate syntaxcre
                string s = "Illegal Character: ";
                s += source[idx];
                errors.push_back(IllegalCharError(s));
            }
        }
    }

    tokens.push_back(Token("End of File", Eof));
    return pair(tokens, errors);
};

void print(vector<Token> toks) {
    cout << "##########################################\n";
    for (Token t: toks) {
        t.print();
    }
    cout << "##########################################\n";
}

void print(vector<Error> errs) {
    cout << "##########################################\n";
    for (Error er: errs) {
        er.print();
    }
    cout << "##########################################\n";
}