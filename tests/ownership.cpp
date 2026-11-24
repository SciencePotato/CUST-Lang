#include <cassert>
#include <cstdlib>
#include <new>
#include <vector>
#include <memory>
#include "../parser.cpp"

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

int main() {
    const long before = liveAllocations;
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
    std::cout << "Repeated actual parser calls release all temporary allocations.\n";
}
