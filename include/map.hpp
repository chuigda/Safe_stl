#ifndef MAP_HPP
#define MAP_HPP

#include "safe_stl_general.hpp"
#include "functional.hpp"
#include "memory.hpp"
#include "free_tree.hpp"
#include "iterator.hpp"

namespace saber
{

template <typename Key,
          typename T,
          typename Compare = less<Key>,
          typename Allocator = default_allocator<Key>>
class map
{
public:
    using key_type        = Key;
    using mapped_type     = T;
    using value_type      = pair<const Key, T>;
    using key_compare     = Compare;
    using allocator_type  = Allocator;
    using reference       = value_type&;
    using const_reference = const value_type&;

    class iterator;
    class const_iterator;

    using reverse_iterator       = saber::reverse_iterator<iterator>;
    using const_reverse_iterator = saber::reverse_iterator<const_iterator>;

    using size_type       = size_t;
    using difference_type = std::ptrdiff_t;

    using pointer       = allocator_traits<Allocator>::pointer;
    using const_pointer = allocator_traits<Allocator>::const_pointer;

    class value_compare
    {
        friend class map;
    protected:
        Compare comp;
        value_compare(Compare _comp) : comp(_comp) {}

    public:
        using result_type = bool;
        using first_argument_type = value_type;
        using second_argument_type = value_type;

        void operator()(const value_type& _x, const value_type& _y) const
        { return comp(_x.first, _y.first); }
    };

    explicit map(const Compare& _comp = Compare(),
                 const Allocator& _alloc = Allocator());
    template <typename InputIterator>
    map(InputIterator _first, InputIterator _last,
        const Compare& _comp = Compare(),
        const Allocator& _alloc = Allocator());
    map(const map& _another);
    map(map&& _another);
    map(const map& _another, const Allocator& _alloc);
    map(map&& _another, const Allocator& _alloc);
    map(initializer_list<value_type> _ilist,
        const Compare& _comp = Allocator(),
        const Allocator& _alloc = Allocator());
    ~map();

    map& operator= (const map& _another);
    map& operator= (map&& _another);
    allocator_type get_allocator() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;

    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    bool empty();
    size_type size();
    size_type max_size();

    T& operator[] (const key_type& _key);
    T& operator[] (key_type&& _key);

    T& at(const key_type& _key);
    const T& at(const key_type &_key) const;

    template <typename... Args>
    pair<iterator, bool> emplace(Args&& ..._args);
    template <typename... Args>
    iterator emplace_hint(const_iterator _pos, Args&& ..._args);

    pair<iterator, bool> insert(const value_type& _pair);
    iterator insert(const_iterator _pos, const value_type& _pair);
    template <typename Pair>
    pair<iterator, bool> insert(Pair&& _pair);
    template <typename Pair> iterator
    insert(const_iterator _pos, Pair&& _pair);

    template <typename InputIterator>
    insert(InputIterator _first, InputIterator _last);
    insert(initializer_list<value_type> _ilist);

    iterator erase(const_iterator _pos);
    size_type erase(const key_type& _x);
    iterator erase(const_iterator _first, const_iterator _last);

    void swap(map& _another);
    void clear() noexcept;

    key_compare key_comp() const;
    value_compare key_comp() const;

    iterator find(const key_type& _x);
    const_iterator find(const key_type &_x) const;
    size_type count(const key_type& _x) const;

    iterator lower_bound(const key_type& _x);
    const_iterator lower_bound(const key_type& _x) const;
    iterator upper_bound(const key_type& _x);
    const_iterator upper_bound(const key_type &_x) const;

    pair<iterator, iterator> equal_range(const key_type& _x);
    pair<const_iterator, const_iterator> equal_range(const key_type &_x) const;
};

} // namespace saber

#endif // MAP_HPP
