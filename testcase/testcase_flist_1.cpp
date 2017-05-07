#include "tracer.hpp"
#include "forward_list.hpp"
#include <forward_list>

void testcase_flist_1(void)
{
    {
        std::forward_list<int> l {2, 1, 4, 7};

        l.insert_after(l.begin(), {6, 5, 6, 7});
        l.erase_after(l.begin()++);
        l.erase_after(l.before_begin());

        for (auto& x : l)
        {
            std::printf("%d ", x);
        }
        std::putchar('\n');
    }

    {
        saber::forward_list<int> l {2, 1, 4, 7};

        l.insert_after(l.begin(), {6, 5, 6, 7});
        l.erase_after(l.begin()++);
        l.erase_after(l.before_begin());

        for (auto& x : l)
        {
            std::printf("%d ", x);
        }
        std::putchar('\n');
    }
}
