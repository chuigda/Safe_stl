#include <cstdio>
#include <vector>
#include "vector.hpp"

using std::printf;
using std::putchar;

void testcase_vector_11()
{
    printf("Running testcase11\n\n");
    {
        printf("Behaviour of std::vector\n");
        std::vector<int> v1 {1, 2, 3, 4};
        std::vector<int> v2 {9, 8, 7, 6};
        v1.emplace_back(1);
        v1.insert(v1.begin(), 3);

        std::swap(v1, v2);

        for (auto& x : v1)
        {
            printf("%d ", x);
        }
        putchar('\n');
        for (auto& x : v2)
        {
            printf("%d ", x);
        }
        putchar('\n');
    }

    {
        printf("Behaviour of saber::vector\n");
        saber::vector<int> v1 {1, 2, 3, 4};
        saber::vector<int> v2 {9, 8, 7, 6};
        v1.emplace_back(1);
        v1.insert(v1.cbegin(), 3);

        saber::swap(v1, v2);

        for (auto& x : v1)
        {
            printf("%d ", x);
        }
        putchar('\n');
        for (auto& x : v2)
        {
            printf("%d ", x);
        }
        putchar('\n');
    }
}
