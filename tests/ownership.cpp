#include <cassert>
#include <cstdlib>
#include <new>
#include <vector>
#include <memory>
#include <type_traits>
#include <utility>
#include "../parser.cpp"

static_assert(std::has_virtual_destructor_v<Stmt>);
static_assert(std::is_copy_constructible_v<Stmt> && std::is_copy_assignable_v<Stmt>
    && std::is_move_constructible_v<Stmt> && std::is_move_assignable_v<Stmt>);
static_assert(std::is_copy_constructible_v<Program> && std::is_copy_assignable_v<Program>
    && std::is_move_constructible_v<Program> && std::is_move_assignable_v<Program>);

static long liveAllocations = 0;

void* operator new(std::size_t size) {
    if (void* allocation = std::malloc(size == 0 ? 1 : size)) {
        ++liveAllocations;
        return allocation;
    }
    throw std::bad_alloc();
}

void operator delete(void* allocation) noexcept {
    if (allocation) --liveAllocations;
    std::free(allocation);
}

void operator delete(void* allocation, std::size_t) noexcept {
    ::operator delete(allocation);
}

static Stmt statementValue() {
    Stmt statement;
    statement.kind = identifier;
    statement.value = 42;
    statement.symbol = std::string(96, 's');
    return statement;
}

static void checkStatementCopiesAndMoves() {
    Stmt original = statementValue();
    Stmt copied(original);
    copied.symbol[0] = 'c';
    assert(original.symbol[0] == 's');
    Stmt moved(std::move(copied));
    copied.symbol.clear();
    assert(moved.symbol[0] == 'c' && moved.value == 42 && moved.kind == identifier);
    Stmt assigned = statementValue();
    assigned = original;
    assigned.symbol[0] = 'a';
    assert(original.symbol[0] == 's');
    Stmt moveAssigned = statementValue();
    moveAssigned = std::move(moved);
    moved.symbol.clear();
    assert(moveAssigned.symbol[0] == 'c' && moveAssigned.value == 42);
}

static Program programValue() {
    Program program = Parser().produceAST("41 42");
    program.value = 0;
    program.symbol = std::string(96, 'p');
    program.body[0] = statementValue();
    return program;
}

static void checkProgramCopiesAndMoves() {
    Program original = programValue();
    Program copied(original);
    assert(copied.body.data() != original.body.data());
    copied.body[0].symbol[0] = 'c';
    copied.symbol[0] = 'c';
    assert(original.body[0].symbol[0] == 's' && original.symbol[0] == 'p');
    Program moved(std::move(copied));
    copied.body.clear();
    copied.symbol.clear();
    assert(moved.body.size() == 2 && moved.body[0].symbol[0] == 'c');
    assert(moved.body[1].value == 42 && moved.symbol[0] == 'c');
    assert(moved.kind == ::program && moved.value == 0);
    Program assigned = programValue();
    assigned = original;
    assigned.body[0].symbol[0] = 'a';
    assert(original.body[0].symbol[0] == 's');
    Program moveAssigned = programValue();
    moveAssigned = std::move(moved);
    moved.body.clear();
    moved.symbol.clear();
    assert(moveAssigned.body.size() == 2 && moveAssigned.body[0].symbol[0] == 'c');
    assert(moveAssigned.body[1].value == 42 && moveAssigned.symbol[0] == 'c');
    assert(moveAssigned.kind == ::program && moveAssigned.value == 0);
}

int main() {
    const long before = liveAllocations;
    checkStatementCopiesAndMoves();
    checkProgramCopiesAndMoves();
    for (int i = 0; i < 10; ++i) {
        auto program = Parser().produceAST("one 42 two");
        assert(program.body.size() == 3);
        assert(program.body[0].symbol == "one");
        assert(program.body[1].value == 42);
        assert(program.body[2].symbol == "two");
    }
    try {
        Parser().produceAST("one 999999999999999999999999999999999999999999999999999999");
        assert(false);
    } catch (const std::out_of_range&) {
    }
    assert(liveAllocations == before);
    std::cout << "AST copy/move operations and actual parser returns preserve values and release allocations.\n";
}
