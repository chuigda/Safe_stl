#include <cstdio>
#include <vector>
#include "safe_stl_general.hpp"
#include "tracer.hpp"
#include "memory.hpp"

void testcase_allocator()
{
    std::printf("Running testcase for allocator\n\n");

    {
        std::vector<int, saber::default_allocator<int>> vec;

        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.pop_back();
        vec.push_back(4);

        std::vector<int, saber::default_allocator<int>> another = vec;

        for (size_t i = 0; i < another.size(); i++)
        {
            std::printf("%d ", another[i]);
        }
        putchar('\n');
    }

    {
        std::vector<Trace, saber::default_allocator<Trace>> vec;
        vec.push_back(Trace());
        vec.push_back(Trace());

        std::vector<Trace, saber::default_allocator<Trace>> another = vec;
        std::vector<Trace, saber::default_allocator<Trace>> that;

        that = another;
    }

    std::printf("\n\n");
}

int main() 
{
    testcase_allocator();
}
