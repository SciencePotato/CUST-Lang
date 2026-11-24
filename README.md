# CUST-Lang

## Build and check the front end

Run from the repository root so the demo can find `testFiles/basicTest.txt`:

```sh
mkdir -p build
c++ -std=c++17 main.cpp -o build/cust
./build/cust
c++ -std=c++17 tests/lexer.cpp -o build/lexer-test
./build/lexer-test
python3 tests/input.py build/cust
```

The lexer preserves operators adjacent to numbers/identifiers and returns
illegal-character errors in the second member of `Tokenize`'s result pair.
Whitespace, including CRLF, is skipped. An unreadable demo input file produces
a diagnostic and a nonzero exit code, not a successful empty program.
The parser is still a learning-stage implementation, not a complete grammar.

## How does a Language Interpreter work?

What is a programming language? Well, it should just be a program
that executes and does magical stuff. To understand it a bit more
I decide to try to write a language interpreter. This project, I'll write a super basic language.

### Tokens, Errors, Lexer
Tokens are the fundamental building blocks. You can think of Token as a character in a word. Tokens combines together to make Statement / Expression, which I would explain later.

### Parser

### Abstract Syntax Tree

## What's the purpose of making this?

Honestly, I don't think it's just a good learning lessons. It's like learning the composition of a language, how it works together and why it works together. Besides, it's a cool project.

## Credits (Resources)

## TODO

1. Extract Classes to own file
2. Utility Function creation
3. Reorganize and create Header functions
