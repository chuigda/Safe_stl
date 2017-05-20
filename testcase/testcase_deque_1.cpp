#include "deque.hpp"
#include <deque>
#include <cstdio>

extern void testcase_deque_1()
{
    {
        std::deque<int> i;
        i.push_back(2);
        i.push_back(1);
        i.push_back(4);
        i.push_back(7);
        i.push_back(6);

        i.emplace(++i.cbegin(), 233);

        for (auto it = i.cbegin(); it != i.cend(); ++it)
        {
            std::printf("%d ", *it);
        }
        std::putchar('\n');
    }

    {
        saber::deque<int> i;

        i.push_back(2);
        i.push_back(1);
        i.push_back(4);
        i.push_back(7);
        i.push_back(6);

        i.emplace(++i.begin(), 233);

        for (auto it = i.cbegin(); it != i.cend(); ++it)
        {
            std::printf("%d ", *it);
        }
        std::putchar('\n');
    }
}
