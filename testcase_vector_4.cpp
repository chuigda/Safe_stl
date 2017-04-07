#include "vector.hpp"
#include <memory>
#include "testcase_vector.h"

void testcase4()
{
    std::printf("Running testcase4\n\n");

    {
        std::vector<int, std::allocator<int>> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.pop_back();
        vec.push_back(4);

        std::vector<int, std::allocator<int>> another = vec;

        for (size_t i = 0; i < another.size(); i++)
        {
            std::printf("%d ", another[i]);
        }
        putchar('\n');
    }

    {
        std::vector<Trace, std::allocator<Trace>> vec;
        vec.push_back(Trace());
        vec.push_back(Trace());

        std::vector<Trace, std::allocator<Trace>> another = vec;
        std::vector<Trace, std::allocator<Trace>> that;

        that = another;
    }

    std::printf("\n\n");
}
