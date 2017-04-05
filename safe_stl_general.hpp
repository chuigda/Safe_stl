#ifndef SAFE_STL_GENERAL_HPP
#define SAFE_STL_GENERAL_HPP

#define SAFE_STL_ENABLE_WARNING

#include <cstdio>
#include <cstdlib>
#include <new>
#include <ctime>

namespace std
{

FILE*& fp_export(void);

void set_export(FILE* _fp);
void stl_panic(const char* _description);
void stl_warning(const char *_description);

template <typename T>
class default_allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;

    default_allocator() = default;
    default_allocator(const default_allocator&) = default;
    default_allocator(default_allocator&&) = default;

    pointer allocate(size_t _n);
    void deallocate(pointer _p, size_t _n) noexcept;

    void construct(pointer _xptr);
    void construct(pointer _xptr, const T& _another);
    void destroy(pointer _xptr);

    bool operator== (const default_allocator&) const noexcept
    {
        return true;
    }

    bool operator!= (const default_allocator&) const noexcept
    {
        return false;
    }
};

template <typename T>
typename default_allocator<T>::pointer
default_allocator<T>::allocate(size_t _n)
{
    pointer *ret = std::malloc(_n * sizeof(value_type));
    if (ret == nullptr) throw std::bad_alloc();
    return ret;
}

template <typename T>
void
default_allocator<T>::deallocate(pointer _p, size_t) noexcept
{
    free(_p);
}

template <typename T>
void
default_allocator<T>::construct(pointer _xptr)
{
    new ((void*)_xptr) value_type;
}

template <typename T>
void
default_allocator<T>::construct(pointer _xptr, const T &_another)
{
    new ((void*)_xptr) value_type(_another);
}

template <typename T>
void
default_allocator<T>::destroy(pointer _xptr)
{
    _xptr->~value_type();
}

}

#endif // SAFE_STL_GENERAL_HPP
