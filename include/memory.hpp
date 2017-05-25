//////////////////////////////////////////////////////////////////////////////

//                             尘飞舞缓落旧纸扇                             //
//                             花一裳绫罗的绸缎                             //
//                              江南烟雨谁痴盼                              //
//                              桃花湖外无人观                              //
//                            几碟小菜酒寒杯两盏                            //

//                             烟消散功名随云淡                             //
//                             叹情缘生生剪不断                             //
//                              你当年的玉发簪                              //
//                              笑靥如花的委婉                              //
//                            赏过菊兰淌过青石滩                            //

//                          一场梨花雨 下得多痴缠                           //
//                            岁月读不尽或悲或欢                            //
//                          又是落花雨 残叶堆离散                           //
//                            夜落诗染人去空留憾                            //

//////////////////////////////////////////////////////////////////////////////

﻿#ifdef _MSC_VER
#pragma once
#endif

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

    void swap(saber_ptr& _another) noexcept
    {
        saber::swap(ptr, _another.ptr);
        saber::swap(shared_count, _another.shared_count);
    }

private:
    T *ptr;
    size_t *shared_count;
};

template <typename T>
void swap(saber_ptr<T>& _a, saber_ptr<T>& _b)
{
    _a.swap(_b);
}

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
