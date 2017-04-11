#ifndef SABER_TRAITS_HPP
#define SABER_TRAITS_HPP

#include <cstdint>
#include <type_traits>
#include <iterator>

namespace saber
{
template<typename... Ts> struct make_void { typedef void type;};
template<typename... Ts> using void_t = typename make_void<Ts...>::type;

namespace traits
{

template <typename T, typename = void>
struct is_iterable
{
    using value_type = std::false_type;
    static constexpr bool value = false;
};

template <typename T>
struct is_iterable<T, void_t<decltype(std::declval<T>().begin()),
                             decltype(std::declval<T>().end())>>
{
    using value_type = std::true_type;
    static constexpr bool value = true;
};


template <typename T, typename = void>
struct has_iterator_subtypes
{
    using value_type = std::false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_iterator_subtypes<T, void_t<typename std::iterator_traits<T>::value_type,
                                       typename std::iterator_traits<T>::difference_type,
                                       typename std::iterator_traits<T>::pointer,
                                       typename std::iterator_traits<T>::reference,
                                       typename std::iterator_traits<T>::iterator_category>>
{
    using value_type = std::true_type;
    static constexpr bool value = true;
};

template <typename T, typename = void>
struct has_basic_iterator_func
{
    using value_type = std::false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_basic_iterator_func<T, void_t<decltype(std::declval<T>().operator*()),
                                         decltype(std::declval<T>().operator++())>>
{
    using value_type = std::true_type;
    static constexpr bool value = true;
};

template <typename T, typename = void>
struct has_forward_iterator_func
{
    using value_type = std::false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_forward_iterator_func<T, void_t<decltype(std::declval<T>().operator++(std::declval<int>()))>>
{
    using value_type = std::true_type;
    static constexpr bool value = true;
};

template <typename T, typename = void>
struct has_bidirectional_iterator_func
{
    using value_type = std::false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_bidirectional_iterator_func<T, void_t<decltype(std::declval<T>().operator--()),
                                                 decltype(std::declval<T>().operator--(std::declval<int>()))>>
{
    using value_type = std::true_type;
    static constexpr bool value = true;
};

template <typename T, typename = void>
struct has_random_access_iterator_func
{
    using value_type = std::false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_random_access_iterator_func<T, void_t<decltype(std::declval<T>() += std::declval<int>()),
                                                 decltype(std::declval<T>() -= std::declval<int>()),
                                                 decltype(std::declval<T>() + std::declval<int>()),
                                                 decltype(std::declval<T>() - std::declval<int>()),
                                                 decltype(std::declval<T>() - std::declval<T>()),
                                                 decltype(std::declval<T>() > std::declval<T>()),
                                                 decltype(std::declval<T>() < std::declval<T>()),
                                                 decltype(std::declval<T>() >= std::declval<T>()),
                                                 decltype(std::declval<T>() <= std::declval<T>())>>
{
    using value_type = std::true_type;
    static constexpr bool value = true;
};

}
}

#endif // SABER_TRAITS_HPP
