# CUST-Lang

Identifier nodes initialize numeric storage because the current AST printer
prints that field for every statement. Check the actual printer without
depending on fresh heap contents:

```sh
mkdir -p build
c++ -std=c++17 tests/identifier.cpp -o build/identifier-test
./build/identifier-test
```

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
