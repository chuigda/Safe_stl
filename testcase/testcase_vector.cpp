#include <vector>
#include "vector.hpp"

#include <ctime>
#include <cstdlib>
#include "excalibur.hpp"

void testcase_vector_ctor_1()
{
    // vector(size_type, const allocator_type& = Allocator());
    std::vector<int> v1 =
            std::vector<int>(1024);
    saber::vector<int> v2 =
            saber::vector<int>(1024);

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());

    std::srand(std::time(NULL));
    int r = std::rand();

    // vector(size_type,
    //        const value_type&,
    //        const allocator_type& = Allocator());
    std::vector<int> v3 =
            std::vector<int>(std::vector<int>::size_type(1024), r);
    saber::vector<int> v4 =
            saber::vector<int>(saber::vector<int>::size_type(1024), r);

    saber::lawaxis(v3.begin(), v3.end(), v4.begin(), v4.end());
}

void testcase_vector_ctor_2()
{
    std::srand(std::time(NULL));
    int r = std::rand();

    std::vector<int> v1 =
            std::vector<int>(std::vector<int>::size_type(1024), r);
    saber::vector<int> v2 =
            saber::vector<int>(saber::vector<int>::size_type(1024), r);

    // vector(const vector&);
    std::vector<int> v3 =
            std::vector<int>(v1);
    saber::vector<int> v4 =
            saber::vector<int>(v2);

    saber::lawaxis(v3.begin(), v3.end(), v4.begin(), v4.end());

    // vector(vector&&);
    std::vector<int> v5 = std::vector<int>(std::move(v3));
    saber::vector<int> v6 = saber::vector<int>(saber::move(v4));

    saber::lawaxis(v5.begin(), v5.end(), v6.begin(), v6.end());
    saber::lawaxis(v3.begin(), v3.end(), v4.begin(), v4.end());
}

void testcase_vector_ctor_3()
{
    // vector(initializer_list, const allocator_type& = Allocator());
    std::vector<int> v1 = std::vector<int>({1, 2, 3, 4, 5});
    saber::vector<int> v2 = saber::vector<int>({1, 2, 3, 4, 5});

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_ctor_4()
{
    // template <typename InputIterator>
    // vector(InputIterator begin,
    //        InputIterator end,
    //        const allocator_type& = Allocator());
    std::srand(std::time(NULL));
    int r = std::rand();

    std::vector<int> v1 =
            std::vector<int>(std::vector<int>::size_type(1024), r);

    std::vector<int> v2 = std::vector<int>(v1.begin(), v1.end());
    saber::vector<int> v3 = saber::vector<int>(v1.begin(), v1.end());

    saber::lawaxis(v2.begin(), v2.end(), v3.begin(), v3.end());
}

void testcase_vector_operator_assign_1()
{
    // vector& operator= (const vector&);

    std::srand(time(NULL));
    int r = std::rand();

    std::vector<int> v1 =
            std::vector<int>(std::vector<int>::size_type(512), r);
    saber::vector<int> v2 =
            saber::vector<int>(saber::vector<int>::size_type(512), r);

    std::vector<int> v3;
    saber::vector<int> v4;

    v3 = v1;
    v4 = v2;

    saber::lawaxis(v3.begin(), v3.end(), v4.begin(), v4.end());
}

void testcase_vector_operator_assign_2()
{
    // vector& operator= (vector&&);

    std::srand(time(NULL));
    int r = std::rand();

    std::vector<int> v1 =
            std::vector<int>(std::vector<int>::size_type(512), r);
    saber::vector<int> v2 =
            saber::vector<int>(saber::vector<int>::size_type(512), r);

    std::vector<int> v3;
    saber::vector<int> v4;

    v3 = std::move(v1);
    v4 = saber::move(v2);

    saber::lawaxis(v3.begin(), v3.end(), v4.begin(), v4.end());
    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_assign_1()
{
    // void assign(size_type, const value_type&);
    std::srand(std::time(NULL));
    int r = std::rand();

    std::vector<int> v1;
    saber::vector<int> v2;

    v1.assign(std::vector<int>::size_type(512), r);
    v2.assign(saber::vector<int>::size_type(512), r);

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_assign_2()
{
    // void assign(InputIterator, InputIterator);

    std::initializer_list<int> ilist{1, 2, 3, 4, 5};

    std::vector<int> v1;
    saber::vector<int> v2;

    v1.assign(ilist.begin(), ilist.end());
    v2.assign(ilist.begin(), ilist.end());

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_assign_3()
{
    // void assign(initializer_list);

    std::vector<int> v1;
    saber::vector<int> v2;

    v1.assign({1, 2, 3, 4, 5});
    v2.assign({1, 2, 3, 4, 5});

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_size()
{
    // size_type size();

    std::srand(time(NULL));
    int r = std::rand();

    std::vector<int> v1 =
            std::vector<int>(std::vector<int>::size_type(512), r);
    saber::vector<int> v2 =
            saber::vector<int>(saber::vector<int>::size_type(512), r);

    saber::lawaxis(v1.size(), v2.size());
}

void testcase_vector_empty()
{
    // bool empty();

    saber::vector<int> v1;
    assert(v1.empty());
    v1.push_back(1);
    assert(!v1.empty());
}

void testcase_vector_push_back_n_pop_back()
{
    // void push_back();
    // void pop_back();

    std::vector<int> v1;
    saber::vector<int> v2;

    std::srand(time(NULL));

    for (int i = 0; i < 32768; i++)
    {
        int r = std::rand();

        v1.push_back(r);
        v2.push_back(r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());

    for (int i = 0; i < 12345; i++)
    {
        v1.pop_back();
        v2.pop_back();
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_emplace_back()
{
    // template <typename... Args>
    // void emplace_back(Args&&...);

    std::vector<int> v1;
    saber::vector<int> v2;

    for (int i = 0; i < 32768; i++)
    {
        int r = std::rand();

        v1.emplace_back(r);
        v2.emplace_back(r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_clear()
{
    // void clear();

    saber::vector<int> v;

    for (int i = 0; i < 32768; i++)
    {
        int r = std::rand();
        v.push_back(r);
    }

    v.clear();
    saber::lawaxis(v.size(), saber::vector<int>::size_type(0));
}

void testcase_vector_insert_1()
{
    // iterator insert(const_iterator, const value_type&);
    // iterator insert(const_iterator, value_type&&);

    std::vector<int> v1;
    saber::vector<int> v2;

    for (int i = 0; i < 32768; i++)
    {
        int r = std::rand();
        v1.insert(v1.cbegin()+i, r);
        v2.insert(v2.cbegin()+i, r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_insert_2()
{
    // iterator insert(const_iterator, size_type, const value_type&);

    std::vector<int> v1;
    saber::vector<int> v2;

    int r = std::rand();
    auto i1 = v1.insert(v1.cbegin(), std::vector<int>::size_type(65536), r);
    auto i2 = v2.insert(v2.cbegin(), saber::vector<int>::size_type(65536), r);

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
    saber::lawaxis(*i1, *i2);
}

void testcase_vector_insert_3()
{
    // iterator insert(const_iterator, initializer_list<value_type>);

    std::vector<int> v1 {1, 2, 3, 4};
    saber::vector<int> v2 {1, 2, 3, 4};

    v1.insert(v1.cbegin()+2, {1, 2, 8, 9});
    v2.insert(v2.cbegin()+2, {1, 2, 8, 9});

    v1.insert(v1.cend()-2, {2, 1, 4, 7});
    v2.insert(v2.cend()-2, {2, 1, 4, 7});

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_insert_4()
{
    // template <typename InputIterator>
    // iterator insert(const_iterator, InputIterator, InputIterator);

    std::vector<int> v0;

    std::vector<int> v1;
    saber::vector<int> v2;

    for (int i = 0; i < 32767; i++)
    {
        v0.push_back(std::rand());
    }

    v1.insert(v1.cbegin(), v0.cbegin(), v0.cend());
    v2.insert(v2.cbegin(), v0.cbegin(), v0.cend());

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_emplace()
{
    // template <typename... Args>
    // iterator emplace(const_iterator, Args&&...);

    std::vector<int> v1;
    saber::vector<int> v2;

    for (int i = 0; i < 32767; i++)
    {
        int r = std::rand();
        v1.emplace(v1.cbegin() + i/2, r);
        v2.emplace(v2.cbegin() + i/2, r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_erase_1()
{
    // iterator erase(const_iterator);
    std::vector<int> v1;
    saber::vector<int> v2;

    std::srand(time(NULL));

    for (int i = 0; i < 32768; i++)
    {
        int r = std::rand();

        v1.push_back(r);
        v2.push_back(r);
    }

    for (int i = 0; i < 1024; i++)
    {
        int r = std::rand()%v1.size();

        v1.erase(v1.cbegin()+r);
        v2.erase(v2.cbegin()+r);
    }

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

void testcase_vector_erase_2()
{
    // iteraror erase(const_iterator, const_iterator);
    std::vector<int> v1;
    saber::vector<int> v2;

    std::srand(time(NULL));

    for (int i = 0; i < 32768; i++)
    {
        int r = std::rand();

        v1.push_back(r);
        v2.push_back(r);
    }

    int left_delim = std::rand() % v1.size();
    int right_delim = std::rand() % (v1.size() - left_delim) + left_delim;

    v1.erase(v1.cbegin()+left_delim, v1.cbegin()+right_delim);
    v2.erase(v2.cbegin()+left_delim, v2.cbegin()+right_delim);

    saber::lawaxis(v1.begin(), v1.end(), v2.begin(), v2.end());
}

int main()
{
    testcase_vector_ctor_1();
    testcase_vector_ctor_2();
    testcase_vector_ctor_3();
    testcase_vector_ctor_4();

    testcase_vector_operator_assign_1();
    testcase_vector_operator_assign_2();

    testcase_vector_assign_1();
    testcase_vector_assign_2();
    testcase_vector_assign_3();

    testcase_vector_size();
    testcase_vector_empty();
    testcase_vector_push_back_n_pop_back();
    testcase_vector_emplace_back();
    testcase_vector_emplace();
    testcase_vector_clear();

    testcase_vector_insert_1();
    testcase_vector_insert_2();
    testcase_vector_insert_3();
    testcase_vector_insert_4();

    testcase_vector_erase_1();
    testcase_vector_erase_2();
}

