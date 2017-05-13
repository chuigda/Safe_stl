#include <list>
#include "list.hpp"

void testcase_list_5(void)
{
    std::printf("Running testcase 5:\n");
    {
        printf("Behaviour of std::list :\n");
        std::list<int> l {1, 2, 2, 2, 3, 3, 4, 5, 5, 6, 7};
        l.unique();

        for (auto& x : l)
        {
            printf("%d ", x);
        }
        putchar('\n');
    }

    {
        printf("Behaviour of saber::list :\n");
        saber::list<int> l {1, 2, 2, 2, 3, 3, 4, 5, 5, 6, 7};
        l.unique();

        for (auto& x : l)
        {
            printf("%d ", x);
        }
        putchar('\n');
    }

    printf("\n\n");
}
