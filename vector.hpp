#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "safe_stl_general.hpp"
#include "strings.defs.h"

namespace std
{

template <typename T, typename Allocator = allocator<T>>
class vector
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    vector()
    {
    }

    vector(const vector& _another)
    {
        Q_UNUSED(_another);
    }

    ~vector()
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

private:
    Allocator alloc;

    T *array = nullptr;
    time_t update_time;
};

}


#endif // VECTOR_HPP
