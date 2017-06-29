#include "free_tree.hpp"
#include "excalibur.hpp"
#include <set>

void testcase_freetree()
{
    std::srand(time(NULL));

    saber::free_tree<int, saber::less<int>, saber::default_allocator<int>> ft(
                (saber::less<int>()), (saber::default_allocator<int>()));
    std::set<int, saber::less<int>, saber::default_allocator<int>> sset;
    for (int i = 0; i < 32767; i++)
    {
        int r = rand();

        ft.insert(r);
        sset.insert(r);
    }
    saber::lawaxis(ft.begin(), ft.end(), sset.begin(), sset.end());
}
