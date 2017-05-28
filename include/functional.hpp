#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

// This part is even rawly copied from EA-STL since I don't know much about
// functional library. However, this may be changed soon.

#include "safe_stl_general.hpp"

namespace saber
{

struct allocator_arg_t {};
constexpr allocator_arg_t allocator_arg = allocator_arg_t();

template <typename Argument, typename Result>
struct unary_function
{
    using argument_type = Argument;
    using result_type = Result;
};

template <typename Argument1, typename Argument2, typename Result>
struct binary_function
{
    using first_argument_type = Argument1;
    using second_argument_type = Argument2;
    using result_type = Result;
};

template <typename T = void>
struct less : public binary_function<T, T, bool>
{
    constexpr bool operator() (const T& _lhs, const T& _rhs) const
        { return _lhs < _rhs; }
};

template<>
struct less<void>
{
    template <typename A, typename B>
    constexpr auto operator() (A&& _lhs, B&& _rhs) const
        -> decltype(std::forward<A>(_lhs) < std::forward<B>(_rhs))
    {
        return std::forward<A>(_lhs) < std::forward<B>(_rhs);
    }
};

} // namespace saber

#endif // FUNCTIONAL_HPP
