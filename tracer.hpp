#ifndef TRACER_HPP
#define TRACER_HPP

#include <cstdio>

class Trace
{
public:
    Trace() { std::printf("Trace() at %p\n", this); }
    Trace(const Trace&) { std::printf("Trace(const Trace&) at %p\n", this); }
    ~Trace() { std::printf("~Trace() at %p\n", this); }
};

class NoCopy
{
public:
    NoCopy() = default;
    ~NoCopy() = default;
private:
    NoCopy(const NoCopy&);
};

#endif
