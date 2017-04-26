#include "list.hpp"
#include <list>

void testcase_list_2()
{
    {
        std::list<int> l {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};

        for (auto it = l.rbegin(); it != l.crend(); ++it)
        {
            std::printf("%d ", *it);
        }
        std::putchar('\n');
    }

    {
        saber::list<int> l {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};

        for (auto it = l.rbegin(); it != l.crend(); ++it)
        {
            std::printf("%d ", *it);
        }
        std::putchar('\n');
    }
}
