#ifndef SABER_TRAITS_HPP
#define SABER_TRAITS_HPP

#include <type_traits>
namespace saber
{
namespace traits
{

using std::true_type;
using std::false_type;

template<typename... Ts> struct make_void { typedef void type;};
template<typename... Ts> using void_t = typename make_void<Ts...>::type;

}
}

#endif // SABER_TRAITS_HPP
