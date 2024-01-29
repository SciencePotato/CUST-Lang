#include <iostream>
#include <typeinfo>

enum NodeType {
    program,
    numericLiteral,
    identifier,
    binaryExpr
};

static const char *enumString[] = {"Program", "NumericLiteral", "Identifier", "BinaryExperssion"};

class Stmt {
public:
    NodeType kind;
    float value;
    std::string symbol;
    void print() {
        std::cout <<  "{" + std::to_string(value) + " : " + symbol + " : " + enumString[kind] + "}\n";
    }
};

class Expr: public Stmt {};

class Program: public Stmt {
public:
    NodeType kind = program;
    std::vector<Stmt> body;
    Program() = default;
    void print() {
    }
};

class IdentifierExpr: public Expr {
public:
    NodeType kind = identifier;
    std::string symbol;
    IdentifierExpr() = default;
    IdentifierExpr(std::string symb) {
        this -> symbol = symb;
    }

    void print() {
        std::cout <<  "{" + symbol + " : " + enumString[kind] + "}\n";
    }

};

// Support other type of values in the future
class NumericLiteral: public Expr {
public:
    NodeType kind = numericLiteral;
    float value;
    NumericLiteral() = default;
    NumericLiteral(float val) {
        this -> value = val;
    }

    void print() {
        std::cout <<  "{" + std::to_string(value) + " : " + enumString[kind] + "}\n";
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