#include <iostream>
#include <typeinfo>

enum NodeType {
    program,
    numericLiteral,
    identifier,
    binaryExpr
};

static const char *enumString[] = {"Program", "NumericLiteral", "Identifier", "BinaryExperssion"};

struct  Stmt {
public:
    NodeType kind;
    float value;
    std::string symbol;
};

class Expr: public Stmt {};

class Program: public Stmt {
public:
    std::vector<Stmt> body;
    Program() {
        this -> kind = program;
    }

    void print() {
        std::cout <<  "{" + std::to_string(body.size()) + " : "+ enumString[kind] + "}\n";
        for (Stmt cur: body) {
            std::cout <<  "{" + std::to_string(cur.value) + ":" + cur.symbol + ":" + enumString[cur.kind] + "}\n";
        }
    }
};

class IdentifierExpr: public Expr {
public:
    IdentifierExpr() = default;
    IdentifierExpr(std::string symb) {
        this -> kind = identifier;
        this -> symbol = symb;
    }

    void print() {
    }

};

// Support other type of values in the future
class NumericLiteral: public Expr {
public:
    NumericLiteral() = default;
    NumericLiteral(float val) {
        this -> kind = numericLiteral;
        this -> value = val;
    }
};

class BinaryExpr: public Expr {
public:
    NodeType kind = binaryExpr;
    Expr left;
    Expr right;
    std::string oper;
    BinaryExpr() = default;
};