#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "safe_stl_general.hpp"
#include "saber_traits.hpp"
#include "iterator.hpp"

namespace saber
{

template <typename T, typename... Args>
void
construct(T* _xptr, Args&&... _args)
{
    ::new (reinterpret_cast<void*>(_xptr)) T(std::forward<Args>(_args)...);
}

template <typename T>
void
destroy_at(T* _xptr)
{
    _xptr->~T();
}

template <class ForwardIterator>
void destroy(ForwardIterator _first, ForwardIterator _last)
{
  for (; _first != _last; ++_first)
  {
    destroy_at(std::addressof(*_first));
  }
}

template <typename InputIterator, typename ForwardIterator>
ForwardIterator
uninitialized_copy(InputIterator _first,
                   InputIterator _last,
                   ForwardIterator _d_first)
{
    static_assert(traits::is_forward_iterator<ForwardIterator>::value,
                  TEMPLATE_ARG_NOT_FORWARD_ITERATOR);
    static_assert(traits::is_input_iterator<InputIterator>::value,
                  TEMPLATE_ARG_NOT_INPUT_ITERATOR);

    {
    ForwardIterator current = _d_first;
    try
    {
        for (; _first != _last; ++_first, (void) ++current)
        {
            construct(std::addressof(*current), *_first);
        }
        return current;
    }
    catch (...)
    {
        for (; _d_first != current; ++_d_first)
        {
            destroy_at(std::addressof(*_d_first));
        }
        throw;
    }
    }
}

template <typename InputIterator, typename Size, typename ForwardIterator>
ForwardIterator uninitialized_copy_n(InputIterator _first,
                                     Size _count,
                                     ForwardIterator _d_first)
{
    static_assert(traits::is_forward_iterator<ForwardIterator>::value,
                  TEMPLATE_ARG_NOT_FORWARD_ITERATOR);
    static_assert(traits::is_input_iterator<InputIterator>::value,
                  TEMPLATE_ARG_NOT_INPUT_ITERATOR);

    {
    ForwardIterator current = _d_first;
    try
    {
        for (; _count > 0; ++_first, (void) ++current, --_count)
        {
            construct(std::addressof(*current), *_first);
        }
        return current;
    }
    catch (...)
    {
        for (; _d_first != current; ++_d_first)
        {
            destroy_at(std::addressof(*_d_first));
        }
        throw;
    }
    }
}

template <typename ForwardIterator, typename T>
void uninitialized_fill(ForwardIterator _first,
                        ForwardIterator _last,
                        const T& _value)
{
    {
    ForwardIterator current = _first;
    try
    {
        for (; current != _last; ++current)
        {
            construct(std::addressof(*current), _value);
        }
    }
    catch (...)
    {
        for (; _first != current; ++_first)
        {
            destroy_at(std::addressof(*_first));
        }
        throw;
    }
    }
}

template <typename ForwardIterator, typename Size, typename T>
ForwardIterator uninitialized_fill_n(ForwardIterator _first,
                                     Size _count,
                                     const T& _value)
{
    {
    ForwardIterator current = _first;
    try
    {
        for (; _count > 0; ++current, (void) --_count)
        {
            construct(std::addressof(*current), _value);
        }
        return current;
    }
    catch (...)
    {
        for (; _first != current; ++_first)
        {
            destroy_at(std::addressof(*_first));
        }
        throw;
    }
    }
}

template <typename T>
class saber_ptr
{
public:
    saber_ptr() : saber_ptr(nullptr) {}

    saber_ptr(T* _ptr) :
        ptr(_ptr),
        shared_count(new size_t(1))
    {
    }

    saber_ptr(const saber_ptr& _another) :
        ptr(_another.ptr),
        shared_count(_another.shared_count)
    {
        (*shared_count)++;
    }

    ~saber_ptr()
    {
        --(*shared_count);
        if (*shared_count == 0)
        {
            delete shared_count;
            delete ptr;
        }
    }

    inline T* get() {return ptr;}
    inline const T* get() const {return ptr;}

private:
    T *ptr;
    size_t *shared_count;
};

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

    pointer allocate(size_type _n, const void * = 0);
    void deallocate(pointer _p, size_type) noexcept;

    template <typename U, typename... Args>
    void construct(U* _xptr, Args&&... args);

    template <typename U>
    void destroy(U* _xptr);

    bool operator== (const default_allocator&) const noexcept;
    bool operator!= (const default_allocator&) const noexcept;
    default_allocator& operator= (const default_allocator&) noexcept;

    template<typename U>
    struct rebind
    {
        typedef default_allocator<U> other;
    };
};

template<typename T>
typename default_allocator<T>::pointer
default_allocator<T>::allocate(size_type _n, const void*)
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


} // namespace saber

#include <list>

#endif // MEMORY_HPP
