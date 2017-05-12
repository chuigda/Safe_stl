#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "safe_stl_general.hpp"
#include "strings.defs.h"
#include "iterator.hpp"
#include "memory.hpp"
#include "algorithm.hpp"

namespace saber
{

template <typename T, typename Allocator>
class deque
{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using allocator_type = Allocator;

    class iterator;
    class const_iterator;

    using reverse_iterator = saber::reverse_iterator<iterator>;
    using const_reverse_iterator = saber::reverse_iterator<const_iterator>;

    deque();
    explicit deque(const Allocator& _alloc);
    explicit deque(size_type _n);
    deque(size_type _n, const T& _value, const Allocator& _alloc = Allocator());
    deque(const deque& _another);
    deque(deque&& _another);
    deque(const deque& _another, const Allocator& _alloc);
    deque(deque&& _another, const Allocator& _alloc);
    deque(initializer_list<T> _ilist, const Allocator& _alloc);
    ~deque();

    deque& operator= (const deque& _another);
    deque& operator= (deque&& _another);
    deque& operator= (initializer_list<T> _ilist);
    
    template <typename InputIterator>
    void assign(InputIterator _first, InputIterator _last);
    void assign(size_type _n, const value_type& _value);
    void assign(initializer_list<T> _ilist);

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

    size_type size() const noexcept;
    size_type max_size() const noexcept;
    bool empty() const noexcept;

    reference at(size_type _n);
    const_reference at(size_type _n) const;

    reference operator[](size_type _n);
    const_reference operator[](size_type _n) const;

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    template <typename... Args>
    void emplace_front(Args... _args);
    template <typename... Args>
    void emplace_back(Args... _args);
    template <typename... Args>
    void emplace(const_iterator _pos, Args... _args);

    void push_back(const value_type& _value);
    void push_front(const value_type& _value);
    void push_back(value_type&& _value);
    void push_front(value_type&& _value);

    iterator insert(const_iterator _pos, const value_type& _value);
    iterator insert(const_iterator _pos, value_type&& _value);
    iterator insert(const_iterator _pos, size_type _n, const value_type& _value);
    template <typename InputIterator>
    iterator insert(const_iterator _pos, InputIterator _first, InputIterator _last);
    iterator insert(const_iterator _pos, initializer_list<T> _ilist);

    iterator erase(const_iterator _position);
    iterator erase(const_iterator _first, const_iterator _last);

    void swap(deque& _another);
};

} // namespace saber

#endif // deque.hpp
