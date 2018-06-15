#include "tracer.hpp"
#include "iterator.hpp"
#include "vector.hpp"
#include <vector>
#include <list>

struct fake_iterator
{
    using value_type = void;
    using pointer = void*;
    using reference = std::reference_wrapper<void>;
    using difference_type = void;
    using iterator_category = std::forward_iterator_tag;

    void operator* () {}
    void operator++ () {}
};

void testcase_saber_traits()
{
    static_assert(saber::traits::has_random_access_iterator_func<std::vector<int>::iterator>::value, "std::vector::iterator is not a rand-access iterator");
    // static_assert(saber::traits::has_random_access_iterator_func<std::list<int>::iterator>::value, "std::list::iterator is not a rand-access iterator");
    static_assert(saber::traits::has_random_access_iterator_func<saber::vector<int>::iterator>::value, "saber::vector::iterator is not a rand-access iterator");
}

int main()
{
    testcase_saber_traits();
}
