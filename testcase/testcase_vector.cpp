#include <vector>
#include "vector.hpp"

#include <ctime>
#include <cstdlib>
#include "excalibur.hpp"

void testcase_vector_1()
{
    std::srand(std::time(NULL));

    saber::vector<int> v1;
    std::vector<int> v2;

    v1.reserve(65536);
    v2.reserve(65536);

    for (int i = 0; i < 32767; i++)
    {
        int r = std::rand();

        v1.push_back(r);
        v2.push_back(r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_2()
{
    std::srand(std::time(NULL));

    saber::vector<int> v1;
    std::vector<int> v2;

    v1.reserve(65536);
    v2.reserve(65536);

    for (int i = 0; i < 32767; i++)
    {
        int r = std::rand();

        v1.insert(v1.begin(), r);
        v2.insert(v2.begin(), r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_3()
{
    saber::vector<int> v1 {1, 2, 3, 4, 5};
    std::vector<int> v2 {1, 2, 3, 4, 5};

    v1.insert(v1.begin()+2, {2, 1, 4, 7, 4, 8, 3, 6, 4, 7});
    v2.insert(v2.begin()+2, {2, 1, 4, 7, 4, 8, 3, 6, 4, 7});

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}
