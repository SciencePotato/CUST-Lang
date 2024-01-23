#include <iostream>
#include <fstream>
#include <string>
#include "lexer.cpp"

using namespace std;

int main() {
    ifstream inputFile ("testFiles/basicTest.txt");

    // Reading File Source
    string src, line;
    while (getline(inputFile, line)) {
        src += line + "\n";
    }

    // Tokenize and Print information
    pair<vector<Token>, vector<Error>> res = Tokenize(src);
    for (Token t: res.first) {
        t.print();
    }

    std::cout << src;
    return 0;
};