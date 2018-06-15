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

int main()
{
    testcase_flist_1();
    testcase_flist_2();
}

