#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "safe_stl_general.hpp"
#include "saber_traits.hpp"
#include "strings.defs.h"
#include <iterator>

namespace saber
{

namespace traits
{

template <typename T, typename = void>
struct has_iterator_subtypes
{
    using value_type = std::false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_iterator_subtypes
       <T, void_t<typename std::iterator_traits<T>::value_type,
                  typename std::iterator_traits<T>::difference_type,
                  typename std::iterator_traits<T>::pointer,
                  typename std::iterator_traits<T>::reference,
                  typename std::iterator_traits<T>::iterator_category>>
{
    using value_type = true_type;
    static constexpr bool value = true;
};

template <typename T, typename = void>
struct has_basic_iterator_func
{
    using value_type = std::false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_basic_iterator_func<T, void_t<decltype(*std::declval<T>()),
                                         decltype(++std::declval<T>())>>
{
    using value_type = true_type;
    static constexpr bool value = true;
};

template <typename T, typename = void>
struct has_input_iterator_func
{
    using value_type = false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_input_iterator_func
        <T, void_t<decltype(std::declval<T>() != std::declval<T>())>>
{
    using value_type = true_type;
    static constexpr bool value = true;
};

template <typename T, typename = void>
struct has_output_iterator_func
{
    using value_type = false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_output_iterator_func
       <T, void_t<decltype(*std::declval<T>() = std::declval<typename T::value_type>()),
                  decltype(*++std::declval<T>() = std::declval<typename T::value_type>())>>
{
    using value_type = true_type;
    static constexpr bool value = true;
};

template <typename T, typename = void>
struct has_forward_iterator_func
{
    using value_type = std::false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_forward_iterator_func
       <T, void_t<decltype(std::declval<T>().operator++(std::declval<int>()))>>
{
    using value_type = true_type;
    static constexpr bool value = true;
};

template <typename T, typename = void>
struct has_bidirectional_iterator_func
{
    using value_type = std::false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_bidirectional_iterator_func
       <T, void_t<decltype(--std::declval<T>()),
                  decltype(std::declval<T>()--)>>
{
    using value_type = true_type;
    static constexpr bool value = true;
};

template <typename T, typename = void>
struct has_random_access_iterator_func
{
    using value_type = std::false_type;
    static constexpr bool value = false;
};

template <typename T>
struct has_random_access_iterator_func
       <T, void_t<decltype(std::declval<T>() += std::declval<int>()),
                  decltype(std::declval<T>() -= std::declval<int>()),
                  decltype(std::declval<T>() + std::declval<int>()),
                  decltype(std::declval<T>() - std::declval<int>()),
                  decltype(std::declval<T>() - std::declval<T>()),
                  decltype(std::declval<T>() > std::declval<T>()),
                  decltype(std::declval<T>() < std::declval<T>()),
                  decltype(std::declval<T>() >= std::declval<T>()),
                  decltype(std::declval<T>() <= std::declval<T>())>>
{
    using value_type = true_type;
    static constexpr bool value = true;
};

template <typename T>
struct is_iterator
{
    static constexpr bool value = has_iterator_subtypes<T>::value
                                  && has_basic_iterator_func<T>::value;

    using value_type = typename int2type<value>::value_type;
};

template <typename T>
struct is_input_iterator
{
    static constexpr bool value = is_iterator<T>::value
                                  && has_input_iterator_func<T>::value;

    using value_type = typename int2type<value>::value_type;
};

template <typename T>
struct is_output_iterator
{
    static constexpr bool value = is_iterator<T>::value
                                  && has_output_iterator_func<T>::value;
};

template <typename T>
struct is_forward_iterator
{
    static constexpr bool value = is_input_iterator<T>::value
                                  && has_forward_iterator_func<T>::value;

    using value_type = typename int2type<value>::value_type;
};

template <typename T>
struct is_bidirectional_iterator
{
    static constexpr bool value = is_forward_iterator<T>::value
                                  && has_bidirectional_iterator_func<T>::value;

    using value_type = typename int2type<value>::value_type;
};

template <typename T>
struct is_random_access_iterator
{
    static constexpr bool value = is_bidirectional_iterator<T>::value
                                  && has_random_access_iterator_func<T>::value;

    using value_type = typename int2type<value>::value_type;
};


template <typename T>
struct is_iterator<T*>
{
    static constexpr bool value = true;
    using value_type = true_type;
};

template <typename T>
struct is_forward_iterator<T*>
{
    static constexpr bool value = true;
    using value_type = true_type;
};

template <typename T>
struct is_bidirectional_iterator<T*>
{
    static constexpr bool value = true;
    using value_type = true_type;
};

template <typename T>
struct is_random_access_iterator<T*>
{
    static constexpr bool value = true;
    using value_type = true_type;
};

}

template <typename Iterator>
class reverse_iterator
{
    static_assert(traits::is_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_ITERATOR);
    static_assert(traits::is_bidirectional_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_BIDIRECTIONAL_ITERATOR);

public:
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using value_type        = typename std::iterator_traits<Iterator>::value_type;
    using pointer           = typename std::iterator_traits<Iterator>::pointer;
    using reference         = typename std::iterator_traits<Iterator>::reference;
    using difference_type   = typename std::iterator_traits<Iterator>::difference_type;
    using iterator_type     = Iterator;

    reverse_iterator(void) = default;
    reverse_iterator(Iterator _iter);
    template <typename U>
    reverse_iterator(const reverse_iterator<U>&);
    ~reverse_iterator() = default;

    template <typename U>
    reverse_iterator& operator= (const reverse_iterator<U>& _other);

    reference operator* ();
    reference operator[] (difference_type _n);

    reverse_iterator& operator++();
    reverse_iterator& operator--();
    const reverse_iterator operator ++(int);
    const reverse_iterator operator --(int);
    reverse_iterator operator+ (difference_type _n);
    reverse_iterator operator- (difference_type _n);
    reverse_iterator& operator+= (difference_type _n);
    reverse_iterator& operator-= (difference_type _n);
    difference_type operator- (const reverse_iterator &_another) const;
    bool operator> (const reverse_iterator& _another) const;
    bool operator< (const reverse_iterator& _another) const;
    bool operator>= (const reverse_iterator& _another) const;
    bool operator<= (const reverse_iterator& _another) const;
    bool operator== (const reverse_iterator& _another) const;
    bool operator!= (const reverse_iterator& _another) const;

    iterator_type base() const { return actual_iter; }

private:
    Iterator actual_iter;
};

template <typename Iterator>
reverse_iterator<Iterator>::reverse_iterator(Iterator _iter) :
    actual_iter(_iter)
{}

template <typename Iterator>
template <typename U>
reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<U> &_ri)
    : reverse_iterator(_ri.base())
{}

template <typename Iterator>
typename reverse_iterator<Iterator>::reference
reverse_iterator<Iterator>::operator*()
{
    iterator_type i(actual_iter);
    return *(--i);
}

template <typename Iterator>
typename reverse_iterator<Iterator>::reference
reverse_iterator<Iterator>::operator[] (difference_type _n)
{
    static_assert(traits::is_random_access_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR);
    return *(actual_iter - _n);
}

template <typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator++ ()
{
    static_assert(traits::is_bidirectional_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_BIDIRECTIONAL_ITERATOR);
    --actual_iter;
    return *this;
}

template <typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator-- ()
{
    ++actual_iter;
    return *this;
}

template <typename Iterator>
const reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator++ (int)
{
    static_assert(traits::is_bidirectional_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_BIDIRECTIONAL_ITERATOR);
    return actual_iter++;
}

template <typename Iterator>
const reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator-- (int)
{
    return actual_iter--;
}

template <typename Iterator>
reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator+ (difference_type _n)
{
    static_assert(traits::is_random_access_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR);
    return reverse_iterator(actual_iter + (-_n));
}

template <typename Iterator>
reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator- (difference_type _n)
{
    static_assert(traits::is_random_access_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR);
    return reverse_iterator(actual_iter + (_n));
}

template <typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator+= (difference_type _n)
{
    static_assert(traits::is_random_access_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR);
    return reverse_iterator(actual_iter += _n);
}

template <typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator-= (difference_type _n)
{
    static_assert(traits::is_random_access_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR);
    return reverse_iterator(actual_iter -= _n);
}

template <typename Iterator>
typename reverse_iterator<Iterator>::difference_type
reverse_iterator<Iterator>::operator- (const reverse_iterator &_another) const
{
    static_assert(traits::is_random_access_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR);
    return _another.actual_iter - actual_iter;
}

template <typename Iterator>
bool
reverse_iterator<Iterator>::operator> (const reverse_iterator& _another) const
{
    static_assert(traits::is_random_access_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR);
    return actual_iter < _another.actual_iter;
}

template <typename Iterator>
bool
reverse_iterator<Iterator>::operator< (const reverse_iterator& _another) const
{
    static_assert(traits::is_random_access_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR);
    return actual_iter > _another.actual_iter;
}

template <typename Iterator>
bool
reverse_iterator<Iterator>::operator>= (const reverse_iterator& _another) const
{
    static_assert(traits::is_random_access_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR);
    return actual_iter <= _another.actual_iter;
}

template <typename Iterator>
bool
reverse_iterator<Iterator>::operator<= (const reverse_iterator &_another) const
{
    static_assert(traits::is_random_access_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR);
    return actual_iter >= _another.actual_iter;
}

template <typename Iterator>
bool
reverse_iterator<Iterator>::operator== (const reverse_iterator &_another) const
{
    static_assert(traits::is_random_access_iterator<Iterator>::value,
                  TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR);
    return actual_iter == _another.actual_iter;
}

template <typename Iterator>
bool
reverse_iterator<Iterator>::operator!= (const reverse_iterator &_another) const
{
    return actual_iter != _another.actual_iter;
}

}

#endif // ITERATOR_HPP
