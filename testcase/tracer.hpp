#ifndef TRACER_HPP
#define TRACER_HPP

#include <cstdio>

class Trace
{
public:
    Trace()
    {
        std::printf("Trace() at %p\n", this);
        m_dynamic = new int[4];
        size = 4;
    }

    Trace(const Trace&)
    {
        std::printf("Trace(const Trace&) at %p\n", this);
        m_dynamic = new int[4];
        size = 4;
    }

    ~Trace()
    {
        std::printf("~Trace() at %p\n", this);
        delete[] m_dynamic;
    }

private:
    int *m_dynamic;
    size_t size;
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
