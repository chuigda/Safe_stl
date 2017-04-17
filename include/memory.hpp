#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "safe_stl_general.hpp"
#include "saber_traits.hpp"
#include "iterator.hpp"

namespace saber
{

template <typename T, typename... Args>
void
construct(T* _xptr, Args... _args)
{
    ::new (static_cast<void*>(_xptr)) T(_args...);
}

template <typename T, typename... Args>
void
destroy(T* _xptr)
{
    _xptr->~T();
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

    using value_type = typename iterator_traits<ForwardIterator>::value_type;

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
            _d_first->~value_type();
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

    using value_type = typename std::iterator_traits<ForwardIterator>::value_type;

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
        for (; _d_first != current; ++_d_first) {
            _d_first->~value_type();
        }
        throw;
    }
    }
}



} // namespace saber

#endif // MEMORY_HPP
