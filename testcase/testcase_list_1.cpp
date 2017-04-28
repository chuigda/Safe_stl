#include "list.hpp"
#include <list>
#include <cstdio>

using std::printf;
using std::putchar;

void testcase_list_1()
{
    printf("Running testcase 1:\n");
    printf("Behaviour of std::list:\n");
    {
        std::list<int> l {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
        auto operation_place = l.cbegin();
        operation_place++;
        operation_place++;
        l.insert(operation_place, {2,3,4});
        auto operation_place_2 = operation_place;
        operation_place++;
        operation_place++;

        l.erase(operation_place_2, operation_place);
        for (auto it = l.begin(); it != l.end(); ++it)
        {
            printf("%d ", *it);
        }
        putchar('\n');
    }

    printf("Behaviour of saber::list:\n");
    {
        saber::list<int> l {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
        auto operation_place = l.begin();
        operation_place++;
        operation_place++;
        l.insert(operation_place, {2,3,4});
        auto operation_place_2 = operation_place;
        operation_place++;
        operation_place++;

        l.erase(operation_place_2, operation_place);
        for (auto it = l.begin(); it != l.end(); ++it)
        {
            printf("%d ", *it);
        }
        putchar('\n');
    }
    printf("\n\n");
}
