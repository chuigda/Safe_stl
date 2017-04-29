#include <cstdio>
#include "tracer.hpp"
#include "vector.hpp"

using std::printf;
using std::putchar;

void testcase_vector_1()
{
    printf("Running testcase1\n\n");

    saber::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.pop_back();
    vec.push_back(3);

    saber::vector<int> another = vec;
    saber::vector<int> that;

    that = vec;

    for (size_t i = 0; i < another.size(); i++)
    {
        printf("%d ", another[i]);
    }
    std::putchar('\n');

    for (size_t i = 0; i < that.size(); i++)
    {
        printf("%d ", another[i]);
    }

    std::putchar('\n');

    printf("\n\n");
}

void testcase_vector_2()
{
    printf("Running testcase2\n\n");

    saber::vector<Trace> vec;
    vec.push_back(Trace());
    vec.push_back(Trace());

    saber::vector<Trace> another = vec;
    saber::vector<Trace> that;

    that = another;

    printf("\n\n");
}

void testcase_vector_3()
{
    printf("Running testcase3\n\n");

    saber::vector<float> vec;
    vec.push_back(3);
    vec.push_back(4);

    for (auto it = vec.cbegin(); it != vec.cend(); ++it)
    {
        printf("%f ", *it);
    }
    putchar('\n');

    for (const auto &it : vec)
    {
        printf("%f ", it);
    }
    putchar('\n');

    printf("\n\n");
}
