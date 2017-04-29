#include <cstdio>
#include "vector.hpp"
#include <vector>

using std::printf;
using std::putchar;

void testcase_vector_8()
{
    printf("Running testcase8\n\n");
    printf("behaviour of saber::vector\n\n");
    {
        saber::vector<int> vec {2, 3, 5, 7};
        int new_element = 9;

        auto insert_pos = vec.cbegin() + 1;
        vec.insert(insert_pos, new_element);

        for (auto it = vec.cbegin(); it != vec.cend(); ++it)
        {
            printf("%d ", *it);
        }
        putchar('\n');
    }

    printf("behaviour of std::vector\n\n");
    {
        std::vector<int> vec {2, 3, 5, 7};

        auto insert_pos = vec.cbegin() + 1;
        vec.insert(insert_pos, 9);

        for (auto it = vec.cbegin(); it != vec.cend(); ++it)
        {
            printf("%d ", *it);
        }
        putchar('\n');
    }
}

void testcase_vector_9()
{
    printf("Running testcase9\n\n");

    printf("behaviour of saber::vector\n\n");
    {
        saber::vector<int> vec {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
        vec.erase(vec.cbegin() + 2, vec.cbegin() + 5);

        for (auto it = vec.cbegin(); it != vec.cend(); ++it)
        {
            printf("%d ", *it);
        }
        putchar('\n');
    }

    printf("behaviour of std::vector\n\n");
    {
        std::vector<int> vec {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
        vec.erase(vec.cbegin() + 2, vec.cbegin() + 5);

        for (auto it = vec.cbegin(); it != vec.cend(); ++it)
        {
            printf("%d ", *it);
        }
        putchar('\n');
    }
}
