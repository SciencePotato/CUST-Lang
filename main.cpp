#include <iostream>
#include <fstream>
#include <string>
#include "parser.cpp"

using namespace std;

int main() {
    ifstream inputFile ("testFiles/basicTest.txt");

    // Reading File Source
    string src, line;
    while (getline(inputFile, line)) {
        src += line + "\n";
    }

    // Tokenize and Print information
    // pair<vector<Token>, vector<Error>> res = Tokenize(src);
    // for (Token t: res.first) {
    //     t.print();
    // }
    Program program = Parser().produceAST(src);

    // std::cout << src;
    return 0;
};