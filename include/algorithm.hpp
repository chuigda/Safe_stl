#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "memory.hpp"
#include "iterator.hpp"

namespace saber
{

template <typename InputIterator, typename OutputIterator>
OutputIterator
copy(InputIterator _first, InputIterator _last, OutputIterator _d_first)
{
    static_assert(traits::is_input_iterator<InputIterator>::value,
                  TEMPLATE_ARG_NOT_INPUT_ITERATOR);
    static_assert(traits::is_output_iterator<OutputIterator>::value,
                  TEMPLATE_ARG_NOT_OUTPUT_ITERATOR);

    while (_first != _last)
    {
        *_d_first++ = *_first++;
    }

    return _d_first;
}

template <typename InputIterator, typename OutputIterator, typename Predicator>
OutputIterator
copy_if(InputIterator _first,
        InputIterator _last,
        OutputIterator _d_first,
        Predicator _pred)
{
    static_assert(traits::is_input_iterator<InputIterator>::value,
                  TEMPLATE_ARG_NOT_INPUT_ITERATOR);
    static_assert(traits::is_output_iterator<OutputIterator>::value,
                  TEMPLATE_ARG_NOT_OUTPUT_ITERATOR);

    while (_first != _last)
    {
        if (_pred(*_first)) *_d_first++ = *_first;
        _first++;
    }
    return _d_first;
}

template <typename InputIterator, typename Size, typename OutputIterator>
OutputIterator
copy_n(InputIterator _first, Size _count, OutputIterator _d_first)
{
    if (_count > 0)
    {
        *_d_first++ = *_first;
        for (Size i = 1; i < _count; ++i)
        {
            *_d_first++ = *++_first;
        }
    }
    return _d_first;
}

template<class BidirectionalIterator, class OutputIterator>
OutputIterator
reverse_copy(BidirectionalIterator _first,
             BidirectionalIterator _last,
             OutputIterator _d_first)
{
    while (_first != _last)
    {
        *(_d_first++) = *(_last--);
    }
    return _d_first;
}

template <typename ForwardIterator, typename T>
void
fill(ForwardIterator _first, ForwardIterator _last, const T& _value)
{
    for (; _first != _last; ++_first)
    {
        *_first = _value;
    }
}

template <typename OutputIterator, typename Size, typename T>
OutputIterator
fill_n(OutputIterator _first, Size _count, const T& _value)
{
    for (Size i = 0; i < _count; i++)
    {
        *(_first++) = _value;
    }
    return _first;
}

} // namespace saber

#endif // ALGORITHM_HPP
