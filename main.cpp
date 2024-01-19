#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile ("testFiles/basicTest.txt");
    string line;
    while (getline(inputFile, line)) {
        std::cout << line << '\n';
    }
    std::cout << "Testing";
    return 0;
};