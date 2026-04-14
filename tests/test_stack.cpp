// tests/test_stack.cpp
// Unit tests for Stack ADT (stack.h / stack.cpp)
// Grading: exit 0 = all pass, exit 1 = any failure

#include "../stack.h"
#include <iostream>
#include <string>

static int g_passed = 0, g_failed = 0;

void test(const std::string& name, bool condition) {
    if (condition) {
        std::cout << "[PASS] " << name << "\n";
        ++g_passed;
    } else {
        std::cout << "[FAIL] " << name << "\n";
        ++g_failed;
    }
}

template<typename Fn>
bool throws(Fn fn) {
    try { fn(); return false; }
    catch (...) { return true; }
}

int main() {
    std::cout << "=== Stack Unit Tests ===\n\n";

    // ── 1. Initialization ─────────────────────────────────────
    Stack s;
    init(&s);
    test("init: isEmpty() == true",  isEmpty(&s));
    test("init: isFull() == false", !isFull(&s));

    // ── 2. Push & Peek ────────────────────────────────────────
    push(&s, 10);
    test("push(10): !isEmpty()",    !isEmpty(&s));
    test("push(10): peek() == 10",   peek(&s) == 10);

    push(&s, 20);
    test("push(20): peek() == 20",   peek(&s) == 20);

    push(&s, 30);
    test("push(30): peek() == 30",   peek(&s) == 30);

    // ── 3. Pop ────────────────────────────────────────────────
    pop(&s);
    test("pop():  peek() == 20",     peek(&s) == 20);

    pop(&s);
    test("pop():  peek() == 10",     peek(&s) == 10);

    pop(&s);
    test("pop():  isEmpty() == true", isEmpty(&s));

    // ── 4. LIFO ordering ─────────────────────────────────────
    push(&s, 1); push(&s, 2); push(&s, 3);
    test("LIFO: peek == 3",  peek(&s) == 3); pop(&s);
    test("LIFO: peek == 2",  peek(&s) == 2); pop(&s);
    test("LIFO: peek == 1",  peek(&s) == 1); pop(&s);

    // ── 5. Exception: pop from empty ──────────────────────────
    test("pop empty: throws",
         throws([&]{ pop(&s); }));

    // ── 6. Exception: peek from empty ─────────────────────────
    test("peek empty: throws",
         throws([&]{ peek(&s); }));

    // ── 7. isFull & push overflow ─────────────────────────────
    Stack sf;
    init(&sf);
    for (int i = 0; i < MAX; ++i) push(&sf, i);
    test("after MAX pushes: isFull() == true", isFull(&sf));
    test("push to full: throws",
         throws([&]{ push(&sf, 999); }));

    // ── 8. Boundary values ────────────────────────────────────
    Stack sb;
    init(&sb);
    push(&sb, -1000); push(&sb, 0); push(&sb, 1000);
    test("boundary: peek == 1000", peek(&sb) == 1000); pop(&sb);
    test("boundary: peek == 0",    peek(&sb) == 0);    pop(&sb);
    test("boundary: peek == -1000",peek(&sb) == -1000);

    // ── Summary ───────────────────────────────────────────────
    std::cout << "\n=== " << g_passed << " / " << (g_passed + g_failed)
              << " tests passed ===\n";

    return (g_failed == 0) ? 0 : 1;
}
