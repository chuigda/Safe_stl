#include "deque.hpp"
#include <deque>

#include <algorithm>
#include <cstdio>
#include "excalibur.hpp"

using std::printf;

void testcase_deque_2()
{
    printf("\n\nRunning testcase 2:\n");
    {
        printf("Behaviour of std::deque:\n");
        std::deque<int> d {2, 1, 4, 7, 4, 8, 3};
        d.insert(d.cbegin()+2, {9, 9, 8, 4});
        std::sort(d.begin(), d.end());
        d.insert(d.cbegin()+2, {9, 9, 8, 4});
        saber::avalon(d.cbegin(), d.cend());
    }

    {
        printf("Behaviour of saber::deque:\n");
        saber::deque<int> d {2, 1, 4, 7, 4, 8, 3};
        d.insert(d.cbegin()+2, {9, 9, 8, 4});
        std::sort(d.begin(), d.end());
        d.insert(d.cbegin()+2, {9, 9, 8, 4});
        saber::avalon(d.cbegin(), d.cend());
    }
}
