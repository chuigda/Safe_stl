#include "testcase_vector.h"
#include "vector.hpp"
#include <algorithm>

/*
template <typename T, typename A>
struct std::iterator_traits<typename saber::vector<T, A>::iterator>
{
    using value_type =
        typename saber::vector<T, A>::iterator::value_type;
    using pointer =
        typename saber::vector<T, A>::iterator::pointer;
    using size_type =
        typename saber::vector<T, A>::iterator::size_type;
    using difference_type =
        typename saber::vector<T, A>::iterator::difference_type;
};
*/

void testcase5()
{
    saber::vector<int> vec;

    vec.push_back(2);
    vec.push_back(1);
    vec.push_back(4);
    vec.push_back(7);

    std::sort(vec.begin(), vec.end());

    for (auto it = vec.begin();
         it != vec.end();
         ++it)
    {
        std::printf("%d ", *it);
    }

    putchar('\n');
}
