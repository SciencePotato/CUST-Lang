#include <iostream>
#include "lexer.cpp"

class Parser {
public:
    Program produceAST(string src) {
        this -> result = Tokenize(src);
        this -> tokens = result.first;
        this -> errors = result.second;
        Program *program = new Program();

        // Parsing Until end of file
        while (notEof()) {
            Stmt *current = this -> parseStmt();
            if (current != nullptr) {
                program -> body.push_back(*current);
            }
        }

        return *program;
    }

private:
    std::pair<std::vector<Token>, std::vector<Error>> result = {};
    std::vector<Token> tokens = {};
    std::vector<Error> errors = {};

    Token eat() {
        Token prev = *at();
        tokens.erase(tokens.begin());
        return prev;
    }

    bool notEof() {
        Token* res = at();
        if (res == nullptr) return true;
        return (*(this -> at())).token != Eof;
    }

    Token* at() {
        if (tokens.empty()) return nullptr;
        return &(tokens[0]);
    }

    Stmt* parseStmt() {
        // Parsing Statements
        return this -> parseExpr();
    }

    Expr* parseExpr() {
        return this -> parsePrimaryExpr();
    }


    Expr* parsePrimaryExpr() {
        Token token = eat();
        TokenType tk = token.token;
        switch(tk) {
            case Identifier:
                return new IdentifierExpr(token.value);
            case Numbers:
                return new NumericLiteral(std::stof(token.value));
            default:
                token.print();
                break;
        };
        return nullptr;
    }

};