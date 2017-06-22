#include <deque>
#include "deque.hpp"

#include <ctime>
#include <cstdlib>
#include "excalibur.hpp"

void testcase_deque_1()
{
    std::srand(std::time(NULL));

    saber::deque<int> v1;
    std::deque<int> v2;

    for (int i = 0; i < 32767; i++)
    {
        int r = std::rand();

        v1.push_back(r);
        v2.push_back(r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_2()
{
    std::srand(std::time(NULL));

    saber::deque<int> v1;
    std::deque<int> v2;

    for (int i = 0; i < 32767; i++)
    {
       int r = std::rand();

       v1.insert(v1.begin(), r);
       v2.insert(v2.begin(), r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}
