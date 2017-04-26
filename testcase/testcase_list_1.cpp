#include "list.hpp"
#include <list>
#include <cstdio>

void testcase_list_1()
{
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
            std::printf("%d ", *it);
        }
        std::putchar('\n');
    }

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
            std::printf("%d ", *it);
        }
        std::putchar('\n');
    }
}
