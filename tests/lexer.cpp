#include <cassert>
#include <vector>
#include "../lexer.cpp"

int main() {
    auto compact = Tokenize("let a=10+20*(b-3)");
    std::vector<TokenType> expected = {
        Let, Identifier, Equals, Numbers, BinaryOperator, Numbers,
        BinaryOperator, OpenParen, Identifier, BinaryOperator, Numbers, CloseParen, Eof
    };
    assert(compact.first.size() == expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        assert(compact.first[i].token == expected[i]);
    }
    assert(compact.first[3].value == "10");
    assert(compact.first[5].value == "20");
    assert(compact.second.empty());

    auto illegal = Tokenize("a@1#");
    assert(illegal.second.size() == 2);
    assert(illegal.second[0].err == EillegalCharError);
    assert(illegal.second[0].detail == "Illegal Character: @");
    assert(illegal.second[1].detail == "Illegal Character: #");

    auto whitespace = Tokenize(" \t\r\n");
    assert(whitespace.first.size() == 1);
    assert(whitespace.first[0].token == Eof);
    assert(whitespace.second.empty());

    for (const auto& source : {"", "123", "abc123"}) {
        auto result = Tokenize(source);
        assert(result.first.back().token == Eof);
        assert(result.second.empty());
    }
}
