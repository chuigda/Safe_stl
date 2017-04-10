#ifndef SAFE_STL_GENERAL_HPP
#define SAFE_STL_GENERAL_HPP

#define SAFE_STL_ENABLE_WARNING

#include <cstdio>
#include <cstdlib>
#include <new>
#include <ctime>
#include <utility>
#include <initializer_list>
#include <memory>

namespace saber
{
using std::allocator_traits;

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

    pointer allocate(size_type _n);
    void deallocate(pointer _p, size_type) noexcept;

    template <typename U, typename... Args>
    void construct(U* _xptr, Args&&... args);

    template <typename U>
    void destroy(U* _xptr);

    bool operator== (const default_allocator&) const noexcept;
    bool operator!= (const default_allocator&) const noexcept;
    default_allocator& operator= (const default_allocator&) noexcept;

    template <typename U>
    using other = default_allocator<U>;
};

template<typename T>
typename default_allocator<T>::pointer
default_allocator<T>::allocate(size_type _n)
{
    pointer ret =
            reinterpret_cast<pointer>(::operator new[](sizeof(T) * _n));
    return ret;
}

template<typename T>
void
default_allocator<T>::deallocate(pointer _p, size_type) noexcept
{
    ::operator delete[] (reinterpret_cast<void*>(_p));
}

template <typename T>
template <typename U, typename... Args>
void
default_allocator<T>::construct(U *_xptr, Args&& ...args)
{
    ::new ((void *)_xptr) U(std::forward<Args>(args)...);
}

template <typename T>
template <typename U>
void
default_allocator<T>::destroy(U *_xptr)
{
    _xptr->~U();
}

template<typename T>
bool
default_allocator<T>::operator==(const default_allocator &) const noexcept
{
    return true;
}

template<typename T>
bool
default_allocator<T>::operator!=(const default_allocator &) const noexcept
{
    return false;
}

template<typename T>
default_allocator<T>&
default_allocator<T>::operator=(const default_allocator &) noexcept
{
    return *this;
}

}

#endif // SAFE_STL_GENERAL_HPP
