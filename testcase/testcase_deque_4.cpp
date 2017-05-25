#include "deque.hpp"
#include <deque>
#include "tracer.hpp"

#include <cstdio>
using std::printf;

void testcase_deque_4()
{
    printf("\n\nRunning testcase 4:");
    {
        printf("Bahaviour of std::deque:\n");
        std::deque<Trace> t;
        t.push_back(Trace());
        t.push_back(Trace());
        t.push_back(Trace());
        t.push_back(Trace());
        t.push_back(Trace());
    }

    {
        printf("Behaviour of saber::deque:\n");
        saber::deque<Trace> t;
        t.push_back(Trace());
        t.push_back(Trace());
        t.push_back(Trace());
        t.push_back(Trace());
        t.push_back(Trace());
    }
}
