#ifndef SAFE_STL_GENERAL_HPP
#define SAFE_STL_GENERAL_HPP

#define SAFE_STL_ENABLE_WARNING

#include <cstdio>
#include <cstdlib>
#include <new>
#include <ctime>
#include <utility>
#include <initializer_list>

namespace saber
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
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    default_allocator() = default;
    default_allocator(const default_allocator&) = default;
    default_allocator(default_allocator&&) = default;

    template <typename U>
    default_allocator(const default_allocator<U>&) {}

    pointer allocate(size_type _n)
    {
        pointer ret =
            reinterpret_cast<pointer>( std::malloc(_n * sizeof(value_type)) );
        if (ret == nullptr) throw std::bad_alloc();
        return ret;
    }

    void deallocate(pointer _p, size_type) noexcept
    {
        free(_p);
    }

    template <typename U, typename... Args>
    void construct(U* _xptr, Args&&... args)
    {
        ::new ((void *)_xptr) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* _xptr)
    {
        _xptr->~value_type();
    }

    bool operator== (const default_allocator&) const noexcept
    {
        return true;
    }

    bool operator!= (const default_allocator&) const noexcept
    {
        return false;
    }

    default_allocator& operator= (const default_allocator&) noexcept
    {
        return *this;
    }

    template <typename U>
    using other = default_allocator<U>;
};

}

#endif // SAFE_STL_GENERAL_HPP
