#include "iterator.hpp"
#include <vector>
#include <forward_list>
#include <list>
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
}
