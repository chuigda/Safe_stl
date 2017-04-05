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
        size_val = 0;
    }

    vector(const vector& _another)
    {
        stl_warning(CONTAINER_COPY);

        array = alloc.allocate(_another.size_val);

        for (size_type i = 0; i < _another.size_val; ++i)
        {
            alloc.construct(&array[i], _another[i]);
        }

        size_val = capacity = _another.size_val;
    }

    vector(vector&& _another)
    {
        array = _another.array;
        _another.array = nullptr;

        size_val = _another.size_val;
        capacity = _another.capacity;

        _another.capacity = _another.size_val = 0;

        update_time = time(nullptr);
    }

    ~vector()
    {
        for (size_type i = 0; i < size_val; ++i)
        {
            alloc.destroy(&array[i]);
        }

        alloc.deallocate(array, capacity);
    }

    size_type size() const
    {
        return size_val;
    }

    size_type max_size() const
    {
        return capacity;
    }

    void shink_to_fit(void) {/* Not implemented */}

    void reserve(size_type _capacity)
    {
        if (capacity > _capacity) return;

        T *new_array = alloc.allocate(_capacity);
        for (size_type i = 0; i < size_val; ++i)
        {
            alloc.construct(&new_array[i], array[i]);
        }

        for (size_type i = 0; i < size_val; ++i)
        {
            alloc.destroy(&array[i]);
        }

        alloc.deallocate(array, capacity);
        array = new_array;

        capacity = _capacity;

        update_vector();
    }

    void push_back(const T& _element)
    {
        if (size_val == capacity) auto_increase();

        alloc.construct(&array[size_val], _element);
        ++size_val;

        update_vector();
    }

    void pop_back(void)
    {
        alloc.destroy(&array[size_val-1]);
        --size_val;

        update_vector();
    }

    T& at(size_type _index)
    {
        if (_index >= size_val)
            stl_panic(ARRAY_OVERFLOW);

        return array[_index];
    }

    T& operator[] (size_type _index)
    {
        if (_index >= size_val)
            stl_panic(ARRAY_OVERFLOW);

        return array[_index];
    }

    const T& at(size_type _index) const
    {
        if (_index >= size_val)
            stl_panic(ARRAY_OVERFLOW);

        return array[_index];
    }

    const T& operator[] (size_type _index) const
    {
        if (_index >= size_val)
            stl_panic(ARRAY_OVERFLOW);

        return array[_index];
    }

    class iterator
    {
    public:
        iterator() = default;
        iterator(const iterator&) = default;
        ~iterator() = default;

        value_type& operator* ()
        {
            if (update_time != get_from->update_time)
            {
                stl_panic(OLD_ITERATOR);
            }

            if (ptr == get_from->array[get_from->size_val])
            {
                stl_panic(ITERATOR_OVERFLOW);
            }

            return *ptr;
        }

        void operator++ () const
        {
            if (update_time != get_from->update_time)
            {
                stl_panic(OLD_ITERATOR);
            }

            ++ptr;
        }

        bool operator== (const iterator& _another) const
        {
            return (_another.ptr == ptr);
        }

        bool operator!= (const iterator& _another) const
        {
            return !operator==(_another);
        }

    private:
        friend class vector;

        vector *get_from;
        T *ptr;
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
        T *new_array = alloc.allocate(capacity * 2);

        for (size_type i = 0; i < size_val; i++)
        {
            alloc.construct(&new_array[i], array[i]);
            alloc.destroy(&array[i]);
        }

        alloc.deallocate(array);
        array = new_array;
    }

    Allocator alloc;

    T *array;
    time_t update_time;

    size_type capacity;
    size_type size_val;
};

}

#endif // VECTOR_HPP
