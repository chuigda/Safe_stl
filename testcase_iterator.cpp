#include "iterator.hpp"
#include <vector>
#include <forward_list>
#include <list>
#include <algorithm>
#include "vector.hpp"

void testcase_iterator()
{
    static_assert(saber::traits::is_random_access_iterator<saber::vector<int>::iterator>::value, "Error");
    static_assert(saber::traits::is_random_access_iterator<saber::vector<int>::const_iterator>::value, "Error");
    static_assert(saber::traits::is_random_access_iterator<std::vector<int>::iterator>::value, "Error");
    // static_assert(saber::traits::is_random_access_iterator<std::forward_list<int>::iterator>::value, "OK");
    // static_assert(saber::traits::is_random_access_iterator<std::list<int>::iterator>::value, "OK");
    static_assert(saber::traits::is_random_access_iterator<int*>::value, "Error");

    static_assert(saber::traits::is_bidirectional_iterator<std::vector<int>::iterator>::value, "Error");
    static_assert(saber::traits::is_bidirectional_iterator<std::list<int>::iterator>::value, "Error");
    // static_assert(saber::traits::is_bidirectional_iterator<std::forward_list<int>::iterator>::value, "OK");
    static_assert(saber::traits::is_bidirectional_iterator<int*>::value, "Error");

    static_assert(saber::traits::is_forward_iterator<std::vector<int>::iterator>::value, "Error");
    static_assert(saber::traits::is_forward_iterator<std::list<int>::iterator>::value, "Error");
    static_assert(saber::traits::is_forward_iterator<std::forward_list<int>::iterator>::value, "Error");
    static_assert(saber::traits::is_forward_iterator<int*>::value, "Error");

    static_assert(saber::traits::is_random_access_iterator<saber::reverse_iterator<std::vector<int>::iterator>>::value, "Error");

    std::printf("running reverse_iterator testcase\n\n");

    std::printf("saber::reverse_iterator + saber::vector\n");
    {
        saber::vector<int> vec;

        for (size_t i = 0; i < 16; ++i)
        {
            vec.push_back(rand() % 100 + 1);
        }

        std::sort(saber::reverse_iterator<saber::vector<int>::iterator>(vec.end()),
                  saber::reverse_iterator<saber::vector<int>::iterator>(vec.begin()));

        for (saber::reverse_iterator<saber::vector<int>::iterator> it(vec.end());
             it != saber::reverse_iterator<saber::vector<int>::iterator>(vec.begin());
             ++it)
        {
             std::printf("%d ", *it);
        }
        std::putchar('\n');
    }

    std::printf("saber::reverse_iterator + std::vector\n");
    {
        std::vector<int> vec;

        for (size_t i = 0; i < 16; ++i)
        {
            vec.push_back(rand() % 100 + 1);
        }

        std::sort(saber::reverse_iterator<std::vector<int>::iterator>(vec.end()),
                  saber::reverse_iterator<std::vector<int>::iterator>(vec.begin()));

        for (saber::reverse_iterator<std::vector<int>::iterator> it(vec.end());
             it != saber::reverse_iterator<std::vector<int>::iterator>(vec.begin());
             ++it)
        {
            std::printf("%d ", *it);
        }
        std::putchar('\n');
    }

    std::printf("std::reverse_iterator + saber::vector\n");
    {
        saber::vector<int> vec;

        for (size_t i = 0; i < 16; ++i)
        {
            vec.push_back(rand() % 100 + 1);
        }

        std::sort(std::reverse_iterator<saber::vector<int>::iterator>(vec.end()),
                  std::reverse_iterator<saber::vector<int>::iterator>(vec.begin()));

        for (std::reverse_iterator<saber::vector<int>::iterator> it(vec.end());
             it != std::reverse_iterator<saber::vector<int>::iterator>(vec.begin());
             ++it)
        {
             std::printf("%d ", *it);
        }
        std::putchar('\n');
    }

    std::printf("\n\n");
}

