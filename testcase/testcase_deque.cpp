#include <deque>
#include "deque.hpp"

#include <ctime>
#include <cstdlib>
#include "excalibur.hpp"

#include "tracer.hpp"

void testcase_deque_ctor_1()
{
    saber::deque<int> v1 = saber::deque<int>(32767);
    std::deque<int> v2 = std::deque<int>(32767);
    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_ctor_2()
{
    saber::deque<int> v1 = saber::deque<int>(saber::deque<int>::size_type(32767),
                                             32);
    std::deque<int> v2 = std::deque<int>(std::deque<int>::size_type(32767),
                                         32);
    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());

    saber::deque<int> v3 = v1;
    saber::lawaxis(v3.begin(), v3.end(), v2.begin(), v2.end());

    saber::deque<int> v4{std::move(v3)};
    saber::lawaxis(v4.begin(), v4.end(), v2.begin(), v2.end());
}

void testcase_deque_ctor_3()
{
    saber::deque<int> v1 = saber::deque<int>(saber::deque<int>::size_type(32767),
                                             32);
    std::deque<int> v2 = std::deque<int>(std::deque<int>::size_type(32767),
                                         32);
    saber::deque<int> v3 = saber::deque<int>(v1,
                                             saber::default_allocator<int>());
    saber::lawaxis(v3.begin(), v3.end(), v2.begin(), v2.end());
}

void testcase_deque_ctor_4()
{
    saber::deque<int> v1 = saber::deque<int>({1, 2, 3, 4, 5});
    std::deque<int> v2 = std::deque<int>({1, 2, 3, 4, 5});
    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_ctor_5()
{
    std::deque<int> v0 = std::deque<int>({1, 2, 3, 4, 5});
    saber::deque<int> v1 = saber::deque<int>(v0.begin(), v0.end());
    saber::lawaxis(v0.begin(), v0.end(), v1.begin(), v1.end());
}

void testcase_deque_assignment_1()
{
    saber::deque<int> v1;
    std::deque<int> v2;

    saber::deque<int> v3 = saber::deque<int>({1, 2, 3, 4, 5});
    std::deque<int> v4 = std::deque<int>({1, 2, 3, 4, 5});

    v1 = v3;
    v2 = v4;

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_assignment_2()
{
    saber::deque<int> v1;
    std::deque<int> v2;

    saber::deque<int> v3 = saber::deque<int>({1, 2, 3, 4, 5});
    std::deque<int> v4 = std::deque<int>({1, 2, 3, 4, 5});

    v1 = std::move(v3);
    v2 = std::move(v4);

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_assignment_3()
{
    saber::deque<int> v1;
    std::deque<int> v2;

    v1 = {1, 2, 3, 4, 5};
    v2 = {1, 2, 3, 4, 5};

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_assign_1()
{
    saber::deque<int> v1 {5, 4, 3, 2, 1};
    std::deque<int> v2 {5, 4, 3, 2, 1};

    v1.assign({1, 2, 3, 4, 5});
    v2.assign({1, 2, 3, 4, 5});

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_assign_2()
{
    saber::deque<int> v1 {5, 4, 3, 2, 1};
    std::deque<int> v2 {5, 4, 3, 2, 1};

    v1.assign(saber::deque<int>::size_type(32), 1);
    v2.assign(std::deque<int>::size_type(32), 1);

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_assign_3()
{
}

// Fixme : testcases for emplaces' needs manual observation
void testcase_deque_emplace_front_1()
{
    saber::deque<Trace> v1;
    std::deque<Trace> v2;

    Trace t1;
    Trace t2;

    v1.emplace_front(t1);
    v2.emplace_front(t2);
}

void testcase_deque_emplace_front_2()
{
    saber::deque<Trace> v1;
    std::deque<Trace> v2;

    v1.emplace_front(Trace());
    v2.emplace_front(Trace());
}

void testcase_deque_emplace_back_1()
{
    saber::deque<Trace> v1;
    std::deque<Trace> v2;

    Trace t1;
    Trace t2;

    v1.emplace_back(t1);
    v2.emplace_back(t2);
}

void testcase_deque_emplace_back_2()
{
    saber::deque<Trace> v1;
    std::deque<Trace> v2;

    v1.emplace_back(Trace());
    v2.emplace_back(Trace());
}

void testcase_deque_emplace()
{
    saber::deque<Trace> v1;
    std::deque<Trace> v2;

    for (int i = 0; i < 256; i++)
    {
        v1.emplace(v1.begin()+v1.size()/2, Trace());
        v2.emplace(v2.begin()+v2.size()/2, Trace());
    }

    saber::lawaxis(v1.size(), v2.size());
    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_push_back()
{
    std::srand(std::time(NULL));

    saber::deque<int> v1;
    std::deque<int> v2;

    for (int i = 0; i < 32767; i++)
    {
        int r = std::rand();

        v1.push_back(r);
        v2.push_back(r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_push_front()
{
    std::srand(std::time(NULL));

    saber::deque<int> v1;
    std::deque<int> v2;

    for (int i = 0; i < 32767; i++)
    {
        int r = std::rand();

        v1.push_front(r);
        v2.push_front(r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_at()
{
    std::srand(std::time(NULL));

    saber::deque<int> v1;
    std::deque<int> v2;

    for (int i = 0; i < 32767; i++)
    {
        int r = std::rand();

        v1.push_back(r);
        v2.push_back(r);
    }

    for (saber::deque<int>::size_type i = 0; i < v1.size(); i++)
    {
        saber::lawaxis(v1.at(i), v2.at(i));
        saber::lawaxis(v1[i], v2[i]);
    }

    saber::lawaxis(v1.front(), v2.front());
    saber::lawaxis(v1.back(), v2.back());
}

void testcase_deque_size()
{
    std::srand(std::time(NULL));

    saber::deque<int> v1;
    std::deque<int> v2;

    for (int i = 0; i < 32767; i++)
    {
        int r = std::rand();

        v1.push_back(r);
        v2.push_back(r);
    }

    saber::lawaxis(v1.size(), v2.size());
}

void testcase_deque_insert_1()
{
    std::srand(std::time(NULL));

    saber::deque<int> v1;
    std::deque<int> v2;

    for (int i = 0; i < 32767; i++)
    {
       int r = std::rand();

       v1.insert(v1.begin(), r);
       v2.insert(v2.begin(), r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_insert_2()
{
    std::srand(std::time(NULL));

    saber::deque<int> v1;
    std::deque<int> v2;

    for (int i = 0; i < 1024; i++)
    {
        int r = std::rand();

        v1.insert(v1.begin()+v1.size()/2, r);
        v2.insert(v2.begin()+v2.size()/2, r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_deque_swap()
{
    saber::deque<int> v1;
    std::deque<int> v2;

    saber::deque<int> v3 = saber::deque<int>({1, 2, 3, 4, 5});
    std::deque<int> v4 = std::deque<int>({1, 2, 3, 4, 5});

    v1.swap(v3);
    v2.swap(v4);

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
    saber::lawaxis(v3.begin(), v3.end(), v4.begin(), v4.end());
}
