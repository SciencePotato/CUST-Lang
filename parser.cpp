#include <iostream>
#include "ast.cpp"
#include "lexer.cpp"

class Parser {
public:
    Program produceAST(string src) {
        this -> result = Tokenize(src);
        this -> tokens = result.first;
        this -> errors = result.second;
        Program *program = new Program();

        // Parsing Until end of file
        while (notEof) {
            program -> body.push_back(this -> parseStmt());
        }

        return *program;
    }
private:
    std::pair<std::vector<Token>, std::vector<Error>> result = {};
    std::vector<Token> tokens = {};
    std::vector<Error> errors = {};

    bool notEof(Token token) {
        return token.token != Eof;
    }

    Token at(int i) {
        return this -> tokens[i];
    }

    Stmt parseStmt() {
        // Parsing Statements
        return this -> parseExpr();
    }

    Expr parseExpr() {
        return this -> parsePrimaryExpr();
    }


    Expr parsePrimaryExpr() {
        Token token = at(0);
        TokenType tk = token.token;

        switch(tk) {
            case Identifier:
                return IdentifierExpr(token.value);
            default:
                this -> errors.push_back(Error("Wrong Identifier", "ParsePrimaryExpr Failure"));
        };
    }

};