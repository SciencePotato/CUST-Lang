# CUST-Lang

Parser temporaries are owned: returned programs retain copied statement data,
while intermediate expressions are released on success or an exception.
The incomplete grammar is unchanged.

```sh
mkdir -p build
c++ -std=c++17 main.cpp -o build/cust
c++ -std=c++17 tests/ownership.cpp -o build/ownership-test
./build/ownership-test
c++ -std=c++17 -fno-elide-constructors tests/ownership.cpp -o build/ownership-no-elide
./build/ownership-no-elide
```

The focused test accounts for allocations during actual repeated parser calls
and during a numeric-conversion exception. It also checks statement and Program
copy/move construction and assignment, independent copied storage, and safe
destruction after clearing moved-from objects. The second build disables
optional return-value elision, including the named return in `produceAST`.

The retained AST owns `vector<Stmt>` and `string` values, not owning raw
pointers. Only parser-local intermediates use `unique_ptr<Stmt>`, and the
virtual base destructor safely releases their dynamic types. `Stmt` rvalues
may use the copy operations because its virtual destructor suppresses an
implicit move constructor; that fallback still preserves value ownership.
Ownership correctness does not depend on NRVO. These checks are not a sanitizer
or full interpreter test.

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
