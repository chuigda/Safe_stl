#include "testcase_vector.h"
#include "vector.hpp"
#include <vector>

void testcase7()
{
    std::printf("Running testcase7\n\n");

    {
        std::printf("Behaviour of std::vector\n");
        std::vector<int> vec;
        vec.reserve(16);

        vec.push_back(1);
        vec.push_back(2);

        auto begin = vec.begin();
        auto end = vec.end();

        vec.push_back(3);

        for (auto it = begin; it != end; ++it)
        {
            std::printf("%d ", *it);
        }

        putchar('\n');
    }

    {
        std::printf("Behaviour of saber::vector\n");
        saber::vector<int> vec;
        vec.reserve(16);

        vec.push_back(1);
        vec.push_back(2);

        auto begin = vec.begin();
        auto end = vec.end();

        vec.push_back(3);

        for (auto it = begin; it != end; ++it)
        {
            std::printf("%d ", *it);
        }

        putchar('\n');
    }

    std::printf("\n\n");
}
