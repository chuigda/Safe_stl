#include <list>
#include "list.hpp"

using std::printf;
using std::putchar;

void testcase_list_4()
{
    printf("Running testcase 3:\n");
    {
        printf("Behaviour of std::list\n");
        std::list<int> l1 {1, 2, 3, 4};
        std::list<int> l2 {9, 8, 7, 6};
        std::list<int> l3 {5, 5, 5, 5};

        l1.splice(l1.cend(), l2);
        l1.splice(l1.cend(), l3, ++(l3.cbegin()), --(l3.cend()));

        std::swap(l1, l2);

        for (auto& x : l1)
        {
            printf("%d ", x);
        }
        putchar('\n');

        for (auto& x : l2)
        {
            printf("%d ", x);
        }
        putchar('\n');

        for (auto& x : l3)
        {
            printf("%d ", x);
        }
        putchar('\n');
    }

    {
        printf("Behaviour pf saber::list\n");
        saber::list<int> l1 {1, 2, 3, 4};
        saber::list<int> l2 {9, 8, 7, 6};
        saber::list<int> l3 {5, 5, 5, 5};
        saber::list<int> l4;

        l1.splice(l1.cend(), l2);
        l1.splice(l1.cend(), l3, ++(l3.cbegin()), --(l3.cend()));

        saber::swap(l1, l2);

        for (auto& x : l1)
        {
            printf("%d ", x);
        }
        putchar('\n');
        for (auto& x : l2)
        {
            printf("%d ", x);
        }
        putchar('\n');

        for (auto& x : l3)
        {
            printf("%d ", x);
        }

        for (auto& x : l4)
        {
            printf("%d ", x);
        }
        putchar('\n');
    }
}
