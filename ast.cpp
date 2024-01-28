#include <iostream>

using namespace std;

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
};

class Expr: public Stmt {};

class Program: public Stmt {
public:
    NodeType kind = program;
    vector<Stmt> body; 
};

class Identifier: public Expr {
public:
    NodeType kind = identifier;
    string symbol;
};

class NumericLiteral: public Expr {
public:
    NodeType kind = numericLiteral;
    int value;
};

class BinaryExpr: public Expr {
public:
    NodeType kind = binaryExpr;
    Expr left;
    Expr right;
    string oper;
};