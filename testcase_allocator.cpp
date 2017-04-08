#include <deque>
#include "testcase_allocator.hpp"
#include "safe_stl_general.hpp"

void testcase()
{
    std::printf("Running testcase for allocator\n\n");

    {
        std::deque<int, saber::default_allocator<int>> vec;

        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.pop_back();
        vec.push_back(4);

        std::deque<int, saber::default_allocator<int>> another = vec;

        for (size_t i = 0; i < another.size(); i++)
        {
            std::printf("%d ", another[i]);
        }
        putchar('\n');
    }

    {
        std::deque<Trace, saber::default_allocator<Trace>> vec;
        vec.push_back(Trace());
        vec.push_back(Trace());

        std::deque<Trace, saber::default_allocator<Trace>> another = vec;
        std::deque<Trace, saber::default_allocator<Trace>> that;

        that = another;
    }

    std::printf("\n\n");
}
