// tests/test_queue.cpp
// Unit tests for Queue ADT (queue.h / queue.cpp)
// Grading: exit 0 = all pass, exit 1 = any failure

#include "../queue.h"
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
    std::cout << "=== Queue Unit Tests ===\n\n";

    // ── 1. Initialization ─────────────────────────────────────
    Queue q;
    init(&q);
    test("init: isEmpty() == true",  isEmpty(&q));
    test("init: isFull() == false", !isFull(&q));

    // ── 2. Enqueue & front/back ───────────────────────────────
    enqueue(&q, 10);
    test("enqueue(10): !isEmpty()",       !isEmpty(&q));
    test("enqueue(10): front() == 10",     front(&q) == 10);
    test("enqueue(10): back()  == 10",     back(&q)  == 10);

    enqueue(&q, 20);
    test("enqueue(20): front() still 10",  front(&q) == 10);
    test("enqueue(20): back()  == 20",     back(&q)  == 20);

    enqueue(&q, 30);
    test("enqueue(30): front() still 10",  front(&q) == 10);
    test("enqueue(30): back()  == 30",     back(&q)  == 30);

    // ── 3. Dequeue (FIFO ordering) ────────────────────────────
    dequeue(&q);
    test("dequeue(): front() == 20",       front(&q) == 20);
    test("dequeue(): back()  == 30",       back(&q)  == 30);

    dequeue(&q);
    test("dequeue(): front() == 30",       front(&q) == 30);

    dequeue(&q);
    test("dequeue(): isEmpty() == true",   isEmpty(&q));

    // ── 4. FIFO ordering stress ───────────────────────────────
    for (int i = 1; i <= 5; ++i) enqueue(&q, i * 10);
    test("FIFO: front == 10", front(&q) == 10);
    dequeue(&q);
    test("FIFO: front == 20", front(&q) == 20);
    dequeue(&q); dequeue(&q); dequeue(&q); dequeue(&q);
    test("FIFO: empty after 5 dequeues", isEmpty(&q));

    // ── 5. Exception: dequeue from empty ──────────────────────
    test("dequeue empty: throws",
         throws([&]{ dequeue(&q); }));

    // ── 6. Exception: front from empty ────────────────────────
    test("front empty: throws",
         throws([&]{ front(&q); }));

    // ── 7. Exception: back from empty ─────────────────────────
    test("back empty: throws",
         throws([&]{ back(&q); }));

    // ── 8. isFull & enqueue overflow ──────────────────────────
    Queue qf;
    init(&qf);
    for (int i = 0; i < MAX; ++i) enqueue(&qf, i);
    test("after MAX enqueues: isFull() == true", isFull(&qf));
    test("enqueue to full: throws",
         throws([&]{ enqueue(&qf, 999); }));

    // ── 9. Boundary values ────────────────────────────────────
    Queue qb;
    init(&qb);
    enqueue(&qb, -1000); enqueue(&qb, 0); enqueue(&qb, 1000);
    test("boundary: front == -1000", front(&qb) == -1000);
    test("boundary: back  == 1000",  back(&qb)  == 1000);
    dequeue(&qb);
    test("boundary: front == 0 after dequeue", front(&qb) == 0);

    // ── Summary ───────────────────────────────────────────────
    std::cout << "\n=== " << g_passed << " / " << (g_passed + g_failed)
              << " tests passed ===\n";

    return (g_failed == 0) ? 0 : 1;
}
