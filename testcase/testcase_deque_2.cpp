#include "deque.hpp"
#include <deque>

#include <algorithm>
#include <cstdio>
#include "excalibur.hpp"

void testcase_deque_2()
{
    {
        std::deque<int> d {2, 1, 4, 7, 4, 8, 3};
        std::sort(d.begin(), d.end());
        saber::avalon(d.cbegin(), d.cend());
    }

    {
        saber::deque<int> d {2, 1, 4, 7, 4, 8, 3};
        std::sort(d.begin(), d.end());
        saber::avalon(d.cbegin(), d.cend());
    }
}
