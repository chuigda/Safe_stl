#ifndef LIST_HPP
#define LIST_HPP

#include "algorithm.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "saber_traits.hpp"

namespace saber
{

template <typename T, typename Allocator = default_allocator<T>>
class list
{
public:
    using value_type       = T;
    using pointer          = T*;
    using reference        = T&;
    using const_reference  = const T&;
    using size_type        = size_t;
    using difference_type  = std::ptrdiff_t;

    class iterator;
    class const_iterator;

    using reverse_iterator = saber::reverse_iterator<iterator>;
    using const_reverse_iterator = saber::reverse_iterator<const_iterator>;
    using allocator_type = Allocator;

    list();
    list(const list& _another);
    list(size_type _n);
    list(size_type _n, const value_type& _value);
    template <typename InputIterator>
    list(InputIterator _first, InputIterator _last);
    list(std::initializer_list<value_type> _list);

    ~list();

private:
    struct list_node
    {
        template <typename... Args>
        list_node(Args... _args) : value(_args...) {}

        T value;
        mutable list_node *prev = nullptr,
                          *next = nullptr;
    };

    using node_allocator_type =
        typename Allocator::template rebind<list_node>::other;

    list_node *head = nullptr,
              *tail = nullptr;

    allocator_type alloc;
    node_allocator_type node_alloc;
};

template <typename T, typename Allocator>
class list<T, Allocator>::iterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = typename list::value_type;
    using difference_type   = typename list::difference_type;
    using pointer           = typename list::pointer;
    using reference         = typename list::reference;
    using const_reference   = typename list::const_reference;

    iterator() = default;
    iterator(const iterator&) = default;
    ~iterator() = default;

    reference operator* (void);
    const_reference operator* (void) const;

    iterator& operator++ (void);
    iterator& operator-- (void);
    iterator operator++ (int);
    iterator operator-- (int);

private:
    iterator(list *_get_from, list::list_node *_node);
    void full_check(void);
    void basic_check(void);

    list *get_from = nullptr;
    list::list_node *node = nullptr;
};

template <typename T, typename Allocator>
class list<T, Allocator>::const_iterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = typename list::value_type;
    using difference_type   = typename list::difference_type;
    using pointer           = typename list::pointer;
    using reference         = typename list::reference;
    using const_reference   = typename list::const_reference;

    const_iterator() = default;
    const_iterator(const const_iterator&) = default;
    ~const_iterator() = default;

    const_reference operator* (void) const;

    const_iterator& operator++ (void);
    const_iterator& operator-- (void);
    const_iterator operator++ (int);
    const_iterator operator-- (int);

private:
    const_iterator(const list *_get_from, const list::list_node *_node);
    void full_check(void);
    void basic_check(void);

    const list *get_from = nullptr;
    const list::list_node *node = nullptr;
};

template <typename T, typename Allocator>
list<T, Allocator>::list() :
    alloc(),
    node_alloc()
{
}

template <typename T, typename Allocator>
list<T, Allocator>::list(const list& _another) :
    alloc(_another.alloc),
    node_alloc(_another.alloc)
{
    // Incomplete part
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator::reference
list<T, Allocator>::iterator::operator*()
{
    full_check();
    return node->value;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator::const_reference
list<T, Allocator>::iterator::operator*() const
{
    full_check();
    return node->value;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator&
list<T, Allocator>::iterator::operator++()
{
    basic_check();
    node = node->next;
    return *this;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator&
list<T, Allocator>::iterator::operator--()
{
    basic_check();
    node = node->prev;
    return *this;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::iterator::operator++(int)
{
    basic_check();
    iterator ret(*this);
    node = node->next;
    return ret;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::iterator::operator--(int)
{
    basic_check();
    iterator ret(*this);
    node = node->prev;
    return ret;
}

template <typename T, typename Allocator>
list<T, Allocator>::iterator::iterator(list *_get_from,
                                       list::list_node *_node) :
    get_from(_get_from),
    node(_node)
{
}

template <typename T, typename Allocator>
void
list<T, Allocator>::iterator::full_check()
{
    basic_check();
    /* On hold */
}

template <typename T, typename Allocator>
void
list<T, Allocator>::iterator::basic_check()
{
    if (nullptr == get_from)
    {
        stl_panic(UNINITIALIZED_ITERATOR);
    }

    if (nullptr == node)
    {
        stl_panic(ITERATOR_OVERFLOW);
    }
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_iterator&
list<T, Allocator>::const_iterator::operator++()
{
    basic_check();
    node = node->next;
    return *this;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_iterator&
list<T, Allocator>::const_iterator::operator--()
{
    basic_check();
    node = node->prev;
    return *this;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_iterator
list<T, Allocator>::const_iterator::operator++(int)
{
    basic_check();
    const_iterator ret(*this);
    node = node->next;
    return ret;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_iterator
list<T, Allocator>::const_iterator::operator--(int)
{
    basic_check();
    const_iterator ret(*this);
    node = node->prev;
    return ret;
}

template <typename T, typename Allocator>
list<T, Allocator>::const_iterator::const_iterator(const list *_get_from,
                                                   const list::list_node *_node) :
    get_from(_get_from),
    node(_node)
{
}

template <typename T, typename Allocator>
void
list<T, Allocator>::const_iterator::full_check()
{
    basic_check();
    /* On hold */
}

template <typename T, typename Allocator>
void
list<T, Allocator>::const_iterator::basic_check()
{
    if (nullptr == get_from)
    {
        stl_panic(UNINITIALIZED_ITERATOR);
    }

    if (nullptr == node)
    {
        stl_panic(ITERATOR_OVERFLOW);
    }
}

} // namespace saber

#endif // LIST_HPP
