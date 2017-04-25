#include "list.hpp"
#include <list>
#include <cstdio>

void testcase_list_1()
{
    {
        std::list<int> l {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
        l.insert(l.cbegin()++, {2,3,4});
        for (auto it = l.begin(); it != l.end(); ++it)
        {
            std::printf("%d ", *it);
        }
        std::putchar('\n');
    }

    {
        saber::list<int> l {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
        l.insert(l.cbegin()++, {2,3,4});
        for (auto it = l.begin(); it != l.end(); ++it)
        {
            std::printf("%d ", *it);
        }
        std::putchar('\n');
    }
}
