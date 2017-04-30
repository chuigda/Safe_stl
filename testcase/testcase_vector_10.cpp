#include <cstdio>
#include <vector>
#include "vector.hpp"

#include "excalibur.hpp"

using std::printf;
using std::putchar;

void testcase_vector_10()
{
    printf("Running testcase10\n\n");
    {
        saber::vector<int> *vec = new saber::vector<int> {1, 2, 3, 4, 5};

        auto it1 = vec->cbegin(),
             it2 = vec->cend();
        delete vec;
        for (; it1 != it2; ++it1)
        {
            printf("%d ", *it1);
        }
        putchar('\n');
    }
    printf("\n\n");
}
