#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "safe_stl_general.hpp"
#include "strings.defs.h"

namespace std
{

template <typename T,
          typename Allocator = default_allocator<T>>
class vector
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    vector()
    {
        array = nullptr;
        capacity = 0;
        size = 0;
    }

    vector(const vector& _another)
    {
        array = alloc.allocate(_another.size);

        for (size_t i = 0; i < _another.size; ++i)
        {
            alloc.construct(&array[i], _another[i]);
        }

        size = capacity = _another.size;
    }

    vector(vector&& _another)
    {
        array = _another.array;
        _another.array = nullptr;

        size = _another.size;
        capacity = _another.capacity;

        _another.capacity = _another.size = 0;

        update_time = time(nullptr);
    }

    ~vector()
    {
        for (size_t i = 0; i < size; ++i)
        {
            alloc.destroy(&array[i]);
        }

        alloc.deallocate(array, capacity);
    }

    void shink_to_fit(void) {/* Not implemented */}

    void reserve(size_t _capacity)
    {
        if (capacity > _capacity) return;

        T *new_array = alloc.allocate(_capacity);
        for (size_t i = 0; i < size; ++i)
        {
            alloc.construct(&new_array[i], array[i]);
        }

        for (size_t i = 0; i < size; ++i)
        {
            alloc.destroy(&array[i]);
        }

        alloc.deallocate(array, capacity);
        array = new_array;

        capacity = _capacity;
    }

    void push_back(const T& _element)
    {

    }

    void pop_back(void)
    {

    }

    class iterator
    {
    public:
        iterator() = default;
        iterator(const iterator&) = default;
        ~iterator() = default;

        value_type& operator* () const
        {
            if (update_time != get_from->update_time)
            {
                stl_panic(OLD_ITERATOR);
            }

            return *get_from;
        }

    private:
        friend class vector;

        vector *get_from;
        time_t update_time;
    };

    iterator begin();
    iterator end();
    iterator rbegin();
    iterator rend();

private:
    void update_vector()
    {
        update_time = time(nullptr);
    }

    void auto_increase()
    {

    }

    Allocator alloc;

    T *array;
    time_t update_time;

    size_t capacity;
    size_t size;
};

}


#endif // VECTOR_HPP
