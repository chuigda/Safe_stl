#include "vector.hpp"
#include <vector>

void testcase6()
{
    saber::vector<NoCopy> *saber_vec;
    saber_vec = new saber::vector<NoCopy>();

    std::vector<NoCopy> std_vec;
    std_vec.push_back(NoCopy());
}
