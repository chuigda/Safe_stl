#include "testcase_vector.h"
#include <vector>
#include "safe_stl_general.hpp"

void testcase5()
{
    std::printf("Running testcase5\n\n");

    {
        std::vector<int, std::default_allocator<int>> vec;

        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.pop_back();
        vec.push_back(4);

        std::vector<int, std::default_allocator<int>> another = vec;

        for (size_t i = 0; i < another.size(); i++)
        {
            std::printf("%d ", another[i]);
        }
        putchar('\n');
    }

    {
        std::vector<Trace, std::default_allocator<Trace>> vec;
        vec.push_back(Trace());
        vec.push_back(Trace());

        std::vector<Trace, std::default_allocator<Trace>> another = vec;
        std::vector<Trace, std::default_allocator<Trace>> that;

        that = another;
    }

    std::printf("\n\n");
}
