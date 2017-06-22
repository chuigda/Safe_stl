#include "list.hpp"
#include <list>

#include <ctime>
#include <cstdlib>
#include "excalibur.hpp"

void testcase_list_1()
{
    std::srand(std::time(NULL));

    saber::list<int> l1;
    std::list<int> l2;

    for (int i = 0; i < 65535; i++)
    {
        int r = std::rand();

        l1.insert(l1.begin(), r);
        l2.insert(l2.begin(), r);
    }

    saber::lawaxis(l1.begin(), l1.end(), l2.begin(), l2.end());
}

void testcase_list_2()
{
    std::srand(std::time(NULL));

    saber::list<int> l1;
    std::list<int> l2;

    for (int i = 0; i < 65535; i++)
    {
        int r = std::rand();

        l1.insert(l1.end(), r);
        l2.insert(l2.end(), r);
    }

    saber::lawaxis(l1.begin(), l1.end(), l2.begin(), l2.end());
}

void testcase_list_3()
{
    std::list<int> l0;

    saber::list<int> l1;
    l1.erase(l1.begin(), l1.end());

    saber::list<int> l2 {2, 1, 4, 7};
    l2.erase(l2.begin(), l2.end());

    saber::lawaxis(l0.begin(), l0.end(), l2.begin(), l2.end());
    saber::lawaxis(l0.begin(), l0.end(), l1.begin(), l1.end());
}

void testcase_list_4()
{
    std::srand(std::time(NULL));

    saber::list<int> l1;
    std::list<int> l2;

    for (int i = 0; i < 65535; i++)
    {
        int r = std::rand();

        l1.insert(l1.end(), r);
        l2.insert(l2.end(), r);
    }

    l1.erase(++l1.begin(), --l1.end());
    l2.erase(++l2.begin(), --l2.end());

    saber::lawaxis(l1.begin(), l1.end(), l2.begin(), l2.end());
}

