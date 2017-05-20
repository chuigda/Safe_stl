#include "deque.hpp"
#include <deque>
#include <cstdio>
#include "excalibur.hpp"

using std::printf;

extern void testcase_deque_1()
{
    printf("\n\nRunning testcase 1:\n");
    {
        printf("Behaviour of std::deque:\n");
        std::deque<int> i;
        i.push_back(2);
        i.push_back(1);
        i.push_back(4);
        i.push_back(7);
        i.push_back(6);

        i.emplace(++i.cbegin(), 233);
        saber::avalon(i.begin(), i.end());
    }

    {
        printf("Behaviour of saber::deque:\n");
        saber::deque<int> i;

        i.push_back(2);
        i.push_back(1);
        i.push_back(4);
        i.push_back(7);
        i.push_back(6);

        i.emplace(++i.begin(), 233);
        saber::avalon(i.begin(), i.end());
    }
}
