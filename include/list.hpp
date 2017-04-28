#ifndef LIST_HPP
#define LIST_HPP

#include "algorithm.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "saber_traits.hpp"

#include <unordered_set>

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

    explicit list();
    explicit list(const Allocator& _alloc);
    list(const list& _another);
    list(size_type _n);
    list(size_type _n, const value_type& _value);
    template <typename InputIterator>
    list(InputIterator _first, InputIterator _last);
    list(std::initializer_list<value_type> _list);
    ~list();

    size_type size() const;
    bool empty() const;

    iterator insert(const_iterator _position, const value_type& _value);
    iterator insert(const_iterator _position, value_type&& _value);
    iterator insert(const_iterator _position,
                    size_type _n, const value_type &_value);
    template <typename InputIterator>
    iterator insert(const_iterator _position,
                    InputIterator _first, InputIterator _last);
    iterator insert(const_iterator _position,
                    initializer_list<value_type> _ilist);

    template <typename... Args>
    iterator emplace(const_iterator _position, Args&& ...args);
    template <typename... Args>
    iterator emplace_back(Args&& ...args);
    template <typename... Args>
    iterator emplace_front(Args&& ...args);

    void push_back(const value_type& _value);
    void push_front(const value_type& _value);

    iterator erase(const_iterator _position);
    iterator erase(const_iterator _first, const_iterator _last);

    void pop_back();
    void pop_front();

    void clear() noexcept;

    void remove(const value_type& _value);
    template <typename UnaryPredicate>
    void remove_if(UnaryPredicate _pred);

    void unique();

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;

    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;

    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

private:
    struct list_node_base
    {
        list_node_base* prev = nullptr;
        list_node_base* next = nullptr;

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

    template <typename ListIterator>
    void check_iterator(const ListIterator& _it) const;

    using node_allocator_type =
        typename Allocator::template rebind<list_node>::other;

    list_node_base head;

    allocator_type alloc;
    node_allocator_type node_alloc;

    std::unordered_set<const list_node_base*> nodes;
};

template <typename T, typename Allocator>
class list<T, Allocator>::iterator
{
    friend class list;
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = typename list::value_type;
    using difference_type   = typename list::difference_type;
    using pointer           = typename list::pointer;
    using reference         = typename list::reference;
    using const_reference   = typename list::const_reference;

    iterator() = default;
    iterator(const iterator&) = default;
    iterator(const typename list::const_iterator& _const_iterator);
    ~iterator() = default;

    reference operator* (void);
    const_reference operator* (void) const;

    bool operator== (const iterator& _another) const;
    bool operator!= (const iterator& _another) const;

    iterator& operator++ (void);
    iterator& operator-- (void);
    iterator operator++ (int);
    iterator operator-- (int);

private:
    iterator(list *_get_from, typename list::list_node_base *_node);
    void full_check(void) const;
    void basic_check(void) const;

    list *get_from = nullptr;
    typename list::list_node_base *node = nullptr;
};

template <typename T, typename Allocator>
class list<T, Allocator>::const_iterator
{
    friend class list;
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = typename list::value_type;
    using difference_type   = typename list::difference_type;
    using pointer           = typename list::pointer;
    using reference         = typename list::reference;
    using const_reference   = typename list::const_reference;

    const_iterator() = default;
    const_iterator(const const_iterator&) = default;
    // See C++ Defect Report #179
    const_iterator(const typename list::iterator& _mutable_iterator);
    ~const_iterator() = default;

    bool operator== (const const_iterator& _another) const;
    bool operator!= (const const_iterator& _another) const;

    const_reference operator* (void) const;
    const_iterator& operator++ (void);
    const_iterator& operator-- (void);
    const_iterator operator++ (int);
    const_iterator operator-- (int);

private:
    const_iterator(const list *_get_from, const typename list::list_node_base *_node);
    void full_check(void) const;
    void basic_check(void) const;

    const list *get_from = nullptr;
    const typename list::list_node_base *node = nullptr;
};

template <typename T, typename Allocator>
list<T, Allocator>::list() :
    alloc(),
    node_alloc()
{
    head.prev = &head;
    head.next = &head;

    nodes.insert(&head);
}

template <typename T, typename Allocator>
list<T, Allocator>::list(const Allocator &_alloc) :
    alloc(_alloc),
    node_alloc(alloc)
{
    head.prev = &head;
    head.next = &head;

    nodes.insert(&head);
}

template <typename T, typename Allocator>
list<T, Allocator>::list(const list& _another) :
    list(_another.alloc)
{
    for (auto it = _another.cbegin();
         it != _another.cend();
         ++it)
    {
        insert(cend(), *it);
    }
}

template <typename T, typename Allocator>
list<T, Allocator>::list(initializer_list<value_type> _ilist) :
    list()
{
    for (auto it = _ilist.begin();
         it != _ilist.end();
         ++it)
    {
        insert(cend(), *it);
    }
}

template <typename T, typename Allocator>
list<T, Allocator>::~list()
{
    erase(cbegin(), cend());
}

template <typename T, typename Allocator>
typename list<T, Allocator>::size_type
list<T, Allocator>::size() const
{
    size_type ret = 0;
    for (auto it = cbegin(); it != cend(); ++it, ++ret);
    return ret;
}

template <typename T, typename Allocator>
bool
list<T, Allocator>::empty() const
{
    return (head.next == head);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::insert(const_iterator _position, const value_type &_value)
{
    check_iterator(_position);
    iterator position(this, const_cast<list_node_base*>(_position.node));

    list_node *node =
            allocator_traits<node_allocator_type>::allocate(node_alloc, 1);
    construct(node, _value);

    node->prev = position.node->prev;
    node->next = position.node;

    position.node->prev->next = node;
    position.node->prev = node;

    nodes.insert(node);

    return iterator(this, node);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::insert(const_iterator _position, value_type &&_value)
{
    check_iterator(_position);
    iterator position(this, const_cast<list_node_base*>(_position.node));

    list_node *node =
            allocator_traits<node_allocator_type>::allocate(node_alloc, 1);
    construct(node, std::move(_value));

    node->prev = position.node->prev;
    node->next = position.node;

    position.node->prev->next = node;
    position.node->prev = node;

    nodes.insert(node);

    return iterator(this, node);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::insert(const_iterator _position,
                           size_type _n, const value_type &_value)
{
    check_iterator(_position);
    for (size_type i = 0; i < _n; ++i)
    {
        insert(_position, _value);
    }
}

template <typename T, typename Allocator>
template <typename InputIterator>
typename list<T, Allocator>::iterator
list<T, Allocator>::insert(const_iterator _position,
                           InputIterator _first, InputIterator _last)
{
    for (; _first != _last; ++_first)
    {
        insert(_position, *_first);
    }

    return iterator(this, const_cast<list_node_base*>(_position.node));
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::insert(const_iterator _position,
                           initializer_list<value_type> _ilist)
{
    return insert(_position, _ilist.begin(), _ilist.end());
}

template <typename T, typename Allocator>
void
list<T, Allocator>::push_back(const value_type &_value)
{
    insert(cend(), _value);
}

template <typename T, typename Allocator>
void
list<T, Allocator>::push_front(const value_type &_value)
{
    insert(cbegin(), _value);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::erase(const_iterator _position)
{
    check_iterator(_position);
    list_node_base *prev = _position.node->prev,
                   *next = _position.node->next;

    prev->next = next;
    next->prev = prev;

    list_node_base *mutable_node =
            const_cast<list_node_base*>(_position.node);
    list_node *converted_node =
            reinterpret_cast<list_node*>(mutable_node);

    nodes.erase(mutable_node);
    destroy_at(converted_node);
    allocator_traits<node_allocator_type>::deallocate(node_alloc,
                                                      converted_node, 1);
    return iterator(this, next);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::erase(const_iterator _first, const_iterator _last)
{
    check_iterator(_last);
    for  (; _first != _last; _first = erase(_first));
    return iterator(this, const_cast<list_node_base*>(_last.node));
}

template <typename T, typename Allocator>
void
list<T, Allocator>::pop_back()
{
    erase(--cend());
}

template <typename T, typename Allocator>
void
list<T, Allocator>::pop_front()
{
    erase(cbegin());
}

template <typename T, typename Allocator>
void
list<T, Allocator>::clear() noexcept
{
    erase(cbegin(), cend());
}

template <typename T, typename Allocator>
void
list<T, Allocator>::remove(const value_type &_value)
{
    remove_if(
        [&](const value_type& _another) -> bool
        {
            return _another == _value;
        }
    );
}

template <typename T, typename Allocator>
template <typename UnaryPredicate>
void
list<T, Allocator>::remove_if(UnaryPredicate _pred)
{
    for (auto it = begin(); it != end();)
    {
        if (_pred(*it))
        {
            it = erase(it);
        }
        else
        {
            ++it;
        }
    }
}

template <typename T, typename Allocator>
void
list<T, Allocator>::unique()
{

}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::begin() noexcept
{
    return iterator(this, head.next);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::end() noexcept
{
    return iterator(this, &head);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_iterator
list<T, Allocator>::begin() const noexcept
{
    return const_iterator(this, head.next);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_iterator
list<T, Allocator>::end() const noexcept
{
    return const_iterator(this, &head);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_iterator
list<T, Allocator>::cbegin() const noexcept
{
    return begin();
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_iterator
list<T, Allocator>::cend() const noexcept
{
    return end();
}

template <typename T, typename Allocator>
typename list<T, Allocator>::reverse_iterator
list<T, Allocator>::rbegin() noexcept
{
    return reverse_iterator(end());
}

template <typename T, typename Allocator>
typename list<T, Allocator>::reverse_iterator
list<T, Allocator>::rend() noexcept
{
    return reverse_iterator(begin());
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_reverse_iterator
list<T, Allocator>::rbegin() const noexcept
{
    return const_reverse_iterator(cend());
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_reverse_iterator
list<T, Allocator>::rend() const noexcept
{
    return const_reverse_iterator(cbegin());
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_reverse_iterator
list<T, Allocator>::crbegin() const noexcept
{
    return rbegin();
}

template <typename T, typename Allocator>
typename list<T, Allocator>::const_reverse_iterator
list<T, Allocator>::crend() const noexcept
{
    return rend();
}

template <typename T, typename Allocator>
template <typename ListIterator>
void
list<T, Allocator>::check_iterator(const ListIterator& _it) const
{
    _it.basic_check();
    if (_it.get_from != this)
    {
        stl_panic(UNKNOWN_REGION_ITERATOR);
    }
}



template <typename T, typename Allocator>
list<T, Allocator>::iterator::iterator(
        const typename list::const_iterator& _const_iterator)
{
    get_from = const_cast<list*>(_const_iterator.get_from);
    node = const_cast<typename list::list_node_base*>(_const_iterator.node);
}

template <typename T, typename Allocator>
bool
list<T, Allocator>::iterator::operator== (const iterator& _another) const
{
    return node == _another.node;
}

template <typename T, typename Allocator>
bool
list<T, Allocator>::iterator::operator!= (const iterator& _another) const
{
    return ! operator==(_another);
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator::reference
list<T, Allocator>::iterator::operator*()
{
    full_check();
    return (reinterpret_cast<typename list::list_node*>(node))->value;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator::const_reference
list<T, Allocator>::iterator::operator*() const
{
    full_check();
    return (reinterpret_cast<const typename list::list_node*>(node))->value;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator&
list<T, Allocator>::iterator::operator++()
{
    // basic_check();
    node = node->next;
    return *this;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator&
list<T, Allocator>::iterator::operator--()
{
    // basic_check();
    node = node->prev;
    return *this;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::iterator::operator++(int)
{
    // basic_check();
    iterator ret(*this);
    node = node->next;
    return ret;
}

template <typename T, typename Allocator>
typename list<T, Allocator>::iterator
list<T, Allocator>::iterator::operator--(int)
{
    // basic_check();
    iterator ret(*this);
    node = node->prev;
    return ret;
}

template <typename T, typename Allocator>
list<T, Allocator>::iterator::iterator(list *_get_from,
                                       typename list::list_node_base *_node) :
    get_from(_get_from),
    node(_node)
{
}

template <typename T, typename Allocator>
void
list<T, Allocator>::iterator::full_check() const
{
    basic_check();
    if (get_from->nodes.find(node) == get_from->nodes.cend())
    {
        stl_panic(OLD_ITERATOR);
    }

    if (&(get_from->head) == node)
    {
        assert(nullptr != node);
        stl_panic(ITERATOR_OVERFLOW);
    }
}

template <typename T, typename Allocator>
void
list<T, Allocator>::iterator::basic_check() const
{
    if (nullptr == get_from)
    {
        assert(nullptr == node);
        stl_panic(UNINITIALIZED_ITERATOR);
    }
}

template <typename T, typename Allocator>
list<T, Allocator>::const_iterator::const_iterator(
        const typename list::iterator& _mutable_iterator)
{
    get_from = _mutable_iterator.get_from;
    node = _mutable_iterator.node;
}

template <typename T, typename Allocator>
bool
list<T, Allocator>::const_iterator::operator== (
        const const_iterator& _another) const
{
    return node == _another.node;
}

template <typename T, typename Allocator>
bool
list<T, Allocator>::const_iterator::operator!= (
        const const_iterator& _another) const
{
    return ! operator==(_another);
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
list<T, Allocator>::const_iterator::const_iterator(
        const list *_get_from,
        const typename list::list_node_base *_node) :
    get_from(_get_from),
    node(_node)
{
}

template <typename T, typename Allocator>
void
list<T, Allocator>::const_iterator::full_check() const
{
    basic_check();   
    if ((get_from->nodes.find(node)) == (get_from->nodes.end()))
    {
        stl_panic(OLD_ITERATOR);
    }

    if (&(get_from->head) == node)
    {
        assert(nullptr != node);
        stl_panic(ITERATOR_OVERFLOW);
    }
}

template <typename T, typename Allocator>
void
list<T, Allocator>::const_iterator::basic_check() const
{
    if (nullptr == get_from)
    {
        assert(nullptr == node);
        stl_panic(UNINITIALIZED_ITERATOR);
    }
}

} // namespace saber

#endif // LIST_HPP
