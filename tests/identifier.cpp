#include <cassert>
#include <cstring>
#include <new>
#include <sstream>
#include <vector>
#include "../ast.cpp"

int main() {
    alignas(IdentifierExpr) unsigned char storage[sizeof(IdentifierExpr)];
    std::memset(storage, 0x7f, sizeof storage);
    auto* expression = new (storage) IdentifierExpr("answer");
    Program program;
    program.body.push_back(*expression);
    expression->~IdentifierExpr();
    std::ostringstream output;
    auto* previous = std::cout.rdbuf(output.rdbuf());
    program.print();
    std::cout.rdbuf(previous);
    assert(output.str() == "{1 : Program}\n{0.000000:answer:Identifier}\n");
    std::cout << "Identifier AST printing uses initialized numeric storage.\n";
}
