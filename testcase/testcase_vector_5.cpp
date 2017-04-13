#include <cstdio>
#include "vector.hpp"
#include <algorithm>

void testcase5()
{
    std::printf("Running testcase5\n\n");

    saber::vector<int> vec;

    vec.push_back(2);
    vec.push_back(1);
    vec.push_back(4);
    vec.push_back(7);
    vec.push_back(4);
    vec.push_back(8);
    vec.push_back(3);
    vec.push_back(6);
    vec.push_back(4);
    vec.push_back(7);

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
