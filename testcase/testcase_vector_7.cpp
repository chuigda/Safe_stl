#include <cstdio>
#include "vector.hpp"
#include <vector>

using std::printf;
using std::putchar;

void testcase_vector_7()
{
    printf("Running testcase7\n\n");

    {
        printf("Behaviour of std::vector\n");
        std::vector<int> vec;
        vec.reserve(16);

        vec.push_back(1);
        vec.push_back(2);

        auto begin = vec.begin();
        auto end = vec.end();

        vec.push_back(3);

        for (auto it = begin; it != end; ++it)
        {
            printf("%d ", *it);
        }

        putchar('\n');
    }

    {
        printf("Behaviour of saber::vector\n");
        saber::vector<int> vec;
        vec.reserve(16);

        vec.push_back(1);
        vec.push_back(2);

        auto begin = vec.begin();
        auto end = vec.end();

        vec.push_back(3);

        for (auto it = begin; it != end; ++it)
        {
            printf("%d ", *it);
        }

        putchar('\n');
    }

    printf("\n\n");
}
