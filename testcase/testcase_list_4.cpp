﻿#include <list>
#include "list.hpp"

using std::printf;
using std::putchar;

void testcase_list_4()
{
    {
        std::list<int> l1 {1, 2, 3, 4};
        std::list<int> l2 {9, 8, 7, 6};
        std::list<int> l3 {5, 5, 5, 5};

        l1.splice(l1.cbegin(), l2);
        l1.splice(l1.cend(), l3, ++(l3.cbegin()), --(l3.cend()));

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
        saber::list<int> l1 {1, 2, 3, 4};
        saber::list<int> l2 {9, 8, 7, 6};
        saber::list<int> l3 {5, 5, 5, 5};

        l1.splice(l1.cbegin(), l2);
        l1.splice(l1.cend(), l3, ++(l3.cbegin()), --(l3.cend()));

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
}
