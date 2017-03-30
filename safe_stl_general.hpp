#ifndef SAFE_STL_GENERAL_HPP
#define SAFE_STL_GENERAL_HPP

#include <cstdio>
#include <cstdlib>
#include <new>
#include <ctime>

namespace std
{

FILE*& fp_export(void);
void set_export(FILE *_fp);
void stl_panic(const char* _description);
void stl_warning(const char *_description);

template <typename T>
class allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;

    allocator() = default;
    allocator(const allocator&) = default;
    allocator(allocator&&) = default;

    pointer allocate(size_t _n);
    void deallocate(pointer _p, size_t _n) noexcept;

    void construct(pointer _xptr);
    void destroy(pointer _xptr);


    bool operator== (const allocator&) const noexcept
    {
        return true;
    }

    bool operator!= (const allocator&) const noexcept
    {
        return false;
    }



};

template <typename T>
typename allocator<T>::pointer
allocator<T>::allocate(size_t _n)
{
    pointer *ret = std::malloc(_n * sizeof(value_type));
    if (ret == nullptr) throw std::bad_alloc();
    return ret;
}

template <typename T>
void
allocator<T>::deallocate(pointer _p, size_t) noexcept
{
    free(_p);
}

template <typename T>
void
allocator<T>::construct(pointer _xptr)
{
    new ((void*)_xptr) value_type;
}

template <typename T>
void
allocator<T>::destroy(pointer _xptr)
{
    _xptr->~value_type();
}

}

#endif // SAFE_STL_GENERAL_HPP
