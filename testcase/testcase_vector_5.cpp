#include <cstdio>
#include "vector.hpp"
#include <algorithm>

using std::printf;
using std::putchar;

void testcase_vector_5()
{
    printf("Running testcase5\n\n");

    saber::vector<int> vec {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};

    std::sort(vec.begin(), vec.end());

    for (auto it = vec.begin();
         it != vec.end();
         ++it)
    {
        printf("%d ", *it);
    }
    putchar('\n');

    for (auto it = vec.rbegin();
         it != vec.rend();
         ++it)
    {
        printf("%d ", *it);
    }
    putchar('\n');

    printf("\n\n");
}
