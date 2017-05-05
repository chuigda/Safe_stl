#ifdef _MSC_VER
#pragma once
#endif

#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include "algorithm.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "saber_traits.hpp"

#include <unordered_set>

namespace saber
{

template <typename T, typename Allocator = default_allocator<T>>
class forward_list
{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    class iterator;
    class const_iterator;

    using reverse_iterator = saber::reverse_iterator<iterator>;
    using const_reverse_iterator = saber::reverse_iterator<const_iterator>;
    using allocator_type = Allocator;

    explicit forward_list();
    explicit forward_list(const Allocator& _alloc);
    forward_list(const forward_list& _another);
    forward_list(size_type _n);
    forward_list(size_type _n, const value_type& _value);
    template <typename InputIterator>
    list(InputIterator _first, InputIterator _last);
    list(std::initializer_list<value_type> _list);

    size_type size() const;
    bool empty() const; 

private:
    struct list_node_base
    {
        list_node_base *prev = nullptr;
        list_node_base *next = nullptr;

        list_node_base() = default;
        ~list_node_base() = default;
    };

    struct list_node : public list_node_base
    {
        T value;
        template <typename... Args>
        list_node(Args&& ..._args) : value(_args...) {}
        ~list_node() = default;
    };

    void register_node(const list_node_base *_node);
    void detach_node(const list_node_base *_node);
    bool search_node(const list_node_base *_node) const;

    template <typename ForwardListIterator>
    void check_iterator(const ForwardListIterator& _iter) const noexcept;

    using node_allocator_type = 
        typename Allocator::template rebind<list_node>::other;

    list_node_base *head;
    allocator_type alloc;
    node_allocator_type node_alloc;

    saber_ptr<bool> validating_ptr;
    std::unordered_set<const list_node_base*> nodes;
};

template <typename T, typename Allocator>
class list<T, Allocator>::iterator
{
    friend class list;
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = typename forward_list::value_type;
    using difference_type   = typename forward_list::difference_type;
    using pointer           = typename forward_list::pointer;
    using reference         = typename forward_list::reference;
    using const_reference   = typename forward_list::const_reference;

    iterator(void) = default;
    iterator(const iterator& _another) = default;
    // See C++ Defect Report #179
    iterator(const typename forward_list::const_iterator& _const_iterator);
    ~iterator() = default;

    reference operator* (void);
    const_reference operator* (void) const;

    bool operator== (const iterator& _another) const;
    bool operator!= (const iterator& _another) const;

    iterator& operator++ (void);
    iterator operator++ (int);

private:
    iterator(forward_list *_get_from,
             typename forward_list::list_node_base *_node);
    void check_initialized(void) const noexcept;
    void check_valid(void) const noexcept;
    void check_dereferencable(void) const noexcept;

    forward_list *get_from = nullptr;
    typename forward_list::list_node_base *node = nullptr;
    saber_ptr<bool> validating_ptr; 
};

template <typename T, typename Allocator>
class forward_list<T, Allocator>::const_iterator
{
    friend class list;
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = typename forward_list::value_type;
    using difference_type = typename forward_list::difference_type;
    using pointer = typename forward_list::pointer;
    using reference = typename forward_list::reference;
    using const_reference = typename forward_list::const_reference;

    const_iterator() = default;
    const_iterator(const const_iterator& _another) = default;
    // See C++ Defect Report #179
    const_iterator(const typename iterator& _mutable_iterator) const;
    ~const_iterator();

    bool operator== (const const_iterator& _another) const;
    bool operator!= (const const_iterator& _another) const;

    const_reference operator* (void) const;
    const_iterator& operator++ (void);
    const_iterator operator++ (int);

private:
    const_iterator(const list* _get_from,
                   const typename list::list_node_base *_node);

    void check_initialized(void) const noexcept;
    void check_valid(void) const noexcept;
    void check_dereferencable(void) const noexcept;

    const forward_list *get_from = nullptr;
    const typename forward_list::list_node_base *node = nullptr;
    saber_ptr<bool> validating_ptr;
};

template <typename T, typename Allocator>
forward_list<T, Allocator>::forward_list() :
    forward_list(Allocator())
{
}

template <typename T, typename Allocator>
forward_list<T, Allocator>::forward_list(const Allocator& _alloc) :
    head(new list_node_base()),
    alloc(_alloc),
    node_alloc(alloc),
    validating_ptr(new bool(true))
    head->prev = head;
    head->next = head;

    nodes.insert(head);
}

template <typename T, typename Allocator>
forward_list<T, Allocator>::~forward_list()
{
#error This part is incomplete, this information should not be removed before completing forward_list
}

} // namespace saber

#endif // FORWARD_LIST_HPP

