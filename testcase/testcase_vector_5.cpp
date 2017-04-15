#include <cstdio>
#include "vector.hpp"
#include <algorithm>

void testcase_vector_5()
{
    std::printf("Running testcase5\n\n");

    saber::vector<int> vec {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};

    std::sort(vec.begin(), vec.end());

    for (auto it = vec.begin();
         it != vec.end();
         ++it)
    {
        std::printf("%d ", *it);
    }
    std::putchar('\n');

    for (auto it = vec.rbegin();
         it != vec.rend();
         ++it)
    {
        std::printf("%d ", *it);
    }
    std::putchar('\n');

    std::printf("\n\n");
}
