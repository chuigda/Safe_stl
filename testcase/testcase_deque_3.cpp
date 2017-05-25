#include "deque.hpp"
#include <deque>
#include "excalibur.hpp"
#include <cstdio>

using std::printf;

void testcase_deque_3()
{
    printf("\n\nRunning testcase 3:\n");
    {
        std::deque<int> deq {1, 2, 3, 4, 5};
        auto begin = deq.cbegin();
        auto end = deq.cend();

        deq.push_back(11);
        saber::avalon(begin, end);

    }
    {
        saber::deque<int> deq {1, 2, 3, 4, 5};
        auto begin = deq.cbegin();
        auto end = deq.cend();

        deq.push_back(11);
        saber::avalon(begin, end);
    }
}
