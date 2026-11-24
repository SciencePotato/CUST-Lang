#include <iostream>
#include <fstream>
#include <string>
#include "parser.cpp"

using namespace std;

int main() {
    ifstream inputFile ("testFiles/basicTest.txt");
    if (!inputFile) {
        cerr << "Unable to open testFiles/basicTest.txt\n";
        return 1;
    }

    // Reading File Source
    string src, line;
    while (getline(inputFile, line)) {
        src += line + "\n";
    }
    if (inputFile.bad()) {
        cerr << "Unable to read testFiles/basicTest.txt\n";
        return 1;
    }

    // Tokenize and Print information
    // pair<vector<Token>, vector<Error>> res = Tokenize(src);
    // for (Token t: res.first) {
    //     t.print();
    // }
    Program program = Parser().produceAST(src);
    program.print();

    // std::cout << src;
    return 0;
};