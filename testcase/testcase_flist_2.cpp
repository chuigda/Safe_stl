#include <forward_list>
#include "forward_list.hpp"

void testcase_flist_2()
{
    {
        std::forward_list<int> l {1, 2, 3, 4};
        std::forward_list<int> la {5, 5, 5, 5};

        l.splice_after(++l.cbegin(), la, ++la.cbegin(), la.cend());
        l.unique();
        l.remove(3);

        for (auto& x : l)
        {
            std::printf("%d ", x);
        }
        std::putchar('\n');
        for (auto& x : la)
        {
            std::printf("%d ", x);
        }
        std::putchar('\n');
    }

    {
        saber::forward_list<int> l {1, 2, 3, 4};
        saber::forward_list<int> la {5, 5, 5, 5};

        l.splice_after(++l.cbegin(), la, ++la.cbegin(), la.cend());
        l.unique();
        l.remove(3);

        for (auto& x : l)
        {
            std::printf("%d ", x);
        }
        std::putchar('\n');
        for (auto& x : la)
        {
            std::printf("%d ", x);
        }
        std::putchar('\n');
    }
}
