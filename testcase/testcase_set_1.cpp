#include <set>
#include "set.hpp"
#include "excalibur.hpp"

void testcase_set_1()
{
    srand(time(NULL));

    saber::set<int> s1;
    std::set<int> s2;

    s1.insert(19264);
    s1.insert(23767);

    s2.insert(19264);
    s2.insert(23767);

    for (int i = 0; i < 1024; i++)
    {
        int r = rand();
        s1.insert(r);
        s2.insert(r);
    }

    saber::lawaxis(s1.begin(), s1.end(), s2.begin(), s2.end());
    s1.erase(s1.find(19264), s1.find(23767));
    s2.erase(s2.find(19264), s2.find(23767));
    saber::lawaxis(s1.begin(), s1.end(), s2.begin(), s2.end());
}
