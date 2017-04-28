#include "list.hpp"
#include <list>
#include <cstdio>
using std::printf;
using std::putchar;

void testcase_list_2()
{
    printf("Running testcase 2:\n");
    printf("Behaviour of std::list:\n");
    {
        std::list<int> l {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};

        for (auto it = l.rbegin(); it != l.crend(); ++it)
        {
            printf("%d ", *it);
        }
        putchar('\n');
    }

    printf("Behaviour of saber::list:\n");
    {
        saber::list<int> l {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};

        for (auto it = l.rbegin(); it != l.crend(); ++it)
        {
            printf("%d ", *it);
        }
        putchar('\n');
    }
    printf("\n\n");
}
