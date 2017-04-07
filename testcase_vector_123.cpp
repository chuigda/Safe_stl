#include "vector.hpp"
#include "testcase_vector.h"

void testcase1()
{
    std::printf("Running testcase1\n\n");

    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.pop_back();
    vec.push_back(3);

    std::vector<int> another = vec;
    std::vector<int> that;

    that = vec;

    for (size_t i = 0; i < another.size(); i++)
    {
        std::printf("%d ", another[i]);
    }
    std::putchar('\n');

    for (size_t i = 0; i < that.size(); i++)
    {
        std::printf("%d ", another[i]);
    }
    std::putchar('\n');

    std::printf("\n\n");
}

void testcase2()
{
    std::printf("Running testcase2\n\n");

    std::vector<Trace> vec;
    vec.push_back(Trace());
    vec.push_back(Trace());

    std::vector<Trace> another = vec;
    std::vector<Trace> that;

    that = another;

    std::printf("\n\n");
}

void testcase3()
{
    std::printf("Running testcase3\n\n");

    std::vector<float> vec;
    vec.push_back(3);
    vec.push_back(4);

    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        std::printf("%f ", *it);
    }
    putchar('\n');

    for (auto &it : vec)
    {
        std::printf("%f ", it);
    }
    putchar('\n');

    std::printf("\n\n");
}
