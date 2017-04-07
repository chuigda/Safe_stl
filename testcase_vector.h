#ifndef TESTCASE_VECTOR_H
#define TESTCASE_VECTOR_H

#include <cstdio>

class Trace
{
public:
    Trace() { std::printf("Trace() at %p\n", this); }
    Trace(const Trace&) { std::printf("Trace(const Trace&) at %p\n", this); }
    ~Trace() {std::printf("~Trace() at %p\n", this);}
};

extern void testcase1();
extern void testcase2();
extern void testcase3();
extern void testcase4();
extern void testcase5();

#endif // TESTCASE_VECTOR_H
