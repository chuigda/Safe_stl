#include "list.hpp"
#include <list>
#include <cstdio>
using std::printf;
using std::putchar;

void testcase_list_3()
{
    printf("Running testcase 3:\n");
    printf("Behaviour of std::list\n");
    {
        std::list<int> l {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
        l.remove(4);
        for (auto& x : l)
        {
            printf("%d ", x);
        }
        putchar('\n');
        l.remove_if([](const int& _number) -> bool {return _number > 7;});
        for (auto& x : l)
        {
            printf("%d ", x);
        }
        putchar('\n');
    }

    printf("Behaviour of saber::list\n");
    {
        saber::list<int> l {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
        l.remove(4);
        for (auto& x : l)
        {
            printf("%d ", x);
        }
        putchar('\n');
        l.remove_if([](const int& _number) -> bool {return _number > 7;});
        for (auto& x : l)
        {
            printf("%d ", x);
        }
        putchar('\n');
    }

    printf("\n\n");
}
