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

private:
    using ptr_allocator_type =
        typename Allocator:: template rebind<T*>::other;

    enum {subarray_size = 16};

    struct cmap
    {
        T* *ptr_array;
        size_type array_count;
    }
    center_map;

    class cmap_iterator;

    void add_subarray_at_begin();
    void add_subarray_at_end();

    cmap_iterator *cmap_it_begin;
    cmap_iterator *cmap_it_end;
    cmap_iterator *cmap_it_cap_begin;
    cmap_iterator *cmap_it_cap_end;

    allocator_type alloc;
    ptr_allocator_type ptr_alloc;

    saber_ptr<bool> validating_ptr;
};



template <typename T, typename Allocator>
class deque<T, Allocator>::iterator
{
    friend class deque;
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = typename deque::value_type;
    using difference_type   = typename deque::difference_type;
    using pointer           = typename deque::pointer;
    using reference         = typename deque::reference;
    using const_reference   = typename deque::const_reference;

    iterator(void) = default;
    iterator(const iterator&) = default;
    // See C++ Defect Report #179
    iterator(const typename deque::const_iterator& _const_iterator);
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
    using cmap_iterator = typename deque::cmap_iterator;
    cmap_iterator cmap_it;

    iterator(const cmap_iterator& cmap_it) :
        cmap_it(cmap_it)
    {}
};

template <typename T, typename Allocator>
class deque<T, Allocator>::const_iterator
{
    friend class deque;
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename deque::value_type;
    using difference_type = typename deque::difference_type;
    using pointer = typename deque::pointer;
    using reference = typename deque::reference;
    using const_reference = typename deque::const_reference;

    const_iterator(void) = default;
    const_iterator(const const_iterator&) = default;
    // See C++ Defect Report #179
    const_iterator(const typename deque::iterator& _mutable_iterator);
    ~const_iterator() = default;

    const_reference operator* (void) const;

    bool operator== (const const_iterator& _another) const;
    bool operator!= (const const_iterator& _another) const;

    const_iterator& operator++ (void);
    const_iterator& operator-- (void);
    const_iterator operator++ (int);
    const_iterator operator-- (int);

private:
    using cmap_iterator = typename deque::cmap_iterator;
    cmap_iterator cmap_it;

    const_iterator(const cmap_iterator& cmap_it) :
        cmap_it(cmap_it)
    {}
};


template <typename T, typename Allocator>
class deque<T, Allocator>::cmap_iterator
{
    friend class deque;
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = typename deque::value_type;
    using difference_type   = typename deque::difference_type;
    using pointer           = typename deque::pointer;
    using reference         = typename deque::reference;
    using const_reference   = typename deque::const_reference;

    cmap_iterator(void) = default;
    cmap_iterator(const cmap_iterator&) = default;
    ~cmap_iterator() = default;

    reference operator* (void);
    const_reference operator* (void) const;

    bool operator== (const cmap_iterator& _another) const;
    bool operator!= (const cmap_iterator& _another) const;

    cmap_iterator& operator++(void);
    cmap_iterator& operator--(void);

private:
    using size_type     = typename deque::size_type;
    using subarray_type = typename deque::subarray_type;
    using cmap          = typename deque::cmap;

    cmap_iterator(const deque *_get_from,
                  subarray_type* _subarray_ptr,
                  size_type _subarray_index) :
        get_from(_get_from),
        p_cmap(_get_from->center_map),
        subarray_ptr(_subarray_ptr),
        index(_subarray_index)
    {}

    const deque *get_from = nullptr;
    const cmap *p_cmap = nullptr;
    subarray_type* subarray_ptr = nullptr;
    size_type index = 0;
};


template <typename T, typename Allocator>
deque<T, Allocator>::deque(const Allocator& _alloc) :
    alloc(_alloc),
    ptr_alloc(alloc)
{
    center_map.ptr_array =
            allocator_traits<ptr_allocator_type>::allocate(ptr_alloc, 2);
    center_map.ptr_array[0] =
            allocator_traits<allocator_type>::allocate(alloc, subarray_size);
    center_map.ptr_array[1] =
            allocator_traits<allocator_type>::allocate(alloc, subarray_size);
    center_map.array_count = 2;

    cmap_it_cap_begin =
            new cmap_iterator(this, center_map.ptr_array+0, 0);
    cmap_it_cap_end =
            new cmap_iterator(this, center_map.ptr_array+1, subarray_size-1);
    cmap_it_begin =
            new cmap_iterator(this, center_map.ptr_array+1, 0);
    cmap_it_end =
            new cmap_iterator(this, center_map.ptr_array+1, 0);
}

template <typename T, typename Allocator>
deque<T, Allocator>::deque() :
    deque(Allocator())
{
}

template <typename T, typename Allocator>
deque<T, Allocator>::~deque()
{
#error this part is still incomplete.

    delete cmap_it_begin;
    delete cmap_it_end;
    delete cmap_it_cap_begin;
    delete cmap_it_cap_end;
    (*validating_ptr.get()) = false;
}

template <typename T, typename Allocator>
template <typename... Args>
void
deque<T, Allocator>::emplace_back(Args... _args)
{
    if (*cmap_it_end == *cmap_it_cap_end) add_subarray_at_end();
    construct(std::addressof(cmap_it_end), std::forward<Args>(_args)...);
    cmap_it_end++;
}

template <typename T, typename Allocator>
template <typename... Args>
void
deque<T, Allocator>::emplace_front(Args... _args)
{
    if (*cmap_it_begin == *cmap_it_cap_begin) add_subarray_at_begin();
    construct(std::addressof(*cmap_it_begin), std::forward<Args>(_args)...);
    cmap_it_begin++;
}



template <typename T, typename Allocator>
deque<T, Allocator>::iterator::iterator(
        const typename deque::const_iterator& _const_iterator) :
    iterator(_const_iterator.cmap_it)
{
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator::reference
deque<T, Allocator>::iterator::operator* ()
{
    return cmap_it.operator* ();
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator::const_reference
deque<T, Allocator>::iterator::operator* () const
{
    return cmap_it.operator* ();
}

template <typename T, typename Allocator>
bool
deque<T, Allocator>::iterator::operator== (const iterator& _another) const
{
    return cmap_it == _another.cmap_it;
}

template <typename T, typename Allocator>
bool
deque<T, Allocator>::iterator::operator!= (const iterator& _another) const
{
    return cmap_it != _another.cmap_it;
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator&
deque<T, Allocator>::iterator::operator++ ()
{
    cmap_it++;
    return *this;
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator&
deque<T, Allocator>::iterator::operator-- ()
{
    cmap_it--;
    return *this;
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator
deque<T, Allocator>::iterator::operator++ (int)
{
    iterator temp = *this;
    operator++ ();
    return temp;
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator
deque<T, Allocator>::iterator::operator-- (int)
{
    iterator temp = *this;
    operator-- ();
    return temp;
}



template <typename T, typename Allocator>
deque<T, Allocator>::const_iterator::const_iterator(
        const typename deque::iterator& _mutable_iterator) :
    const_iterator(_mutable_iterator.cmap_it)
{
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::const_iterator::const_reference
deque<T, Allocator>::const_iterator::operator* () const
{
    return cmap_it.operator* ();
}

template <typename T, typename Allocator>
bool
deque<T, Allocator>::const_iterator::operator== (const const_iterator& _another) const
{
    return cmap_it == _another.cmap_it;
}

template <typename T, typename Allocator>
bool
deque<T, Allocator>::const_iterator::operator!= (const const_iterator& _another) const
{
    return cmap_it != _another.cmap_it;
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::const_iterator&
deque<T, Allocator>::const_iterator::operator++ ()
{
    cmap_it++;
    return *this;
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::const_iterator&
deque<T, Allocator>::const_iterator::operator-- ()
{
    cmap_it--;
    return *this;
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::const_iterator
deque<T, Allocator>::const_iterator::operator++ (int)
{
    const_iterator temp = *this;
    operator++ ();
    return temp;
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::const_iterator
deque<T, Allocator>::const_iterator::operator-- (int)
{
    const_iterator temp = *this;
    operator-- ();
    return temp;
}



template <typename T, typename Allocator>
typename deque<T, Allocator>::cmap_iterator::reference
deque<T, Allocator>::cmap_iterator::operator* ()
{
    return subarray_ptr[0][index];
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::cmap_iterator::const_reference
deque<T, Allocator>::cmap_iterator::operator* () const
{
    return subarray_ptr[0][index];
}

template <typename T, typename Allocator>
bool
deque<T, Allocator>::cmap_iterator::operator== (
        const cmap_iterator& _another) const
{
    return (get_from == _another.get_from)
            && (p_cmap == _another.p_cmap)
            && (subarray_ptr == _another.subarray_ptr)
            && (index == _another.index);
}

template <typename T, typename Allocator>
bool
deque<T, Allocator>::cmap_iterator::operator!= (
        const cmap_iterator& _another) const
{
    return !operator== (_another);
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::cmap_iterator&
deque<T, Allocator>::cmap_iterator::operator++ ()
{
    index++;
    if (index == subarray_size)
    {
        index = 0;
        subarray_ptr++;
    }
    return *this;
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::cmap_iterator&
deque<T, Allocator>::cmap_iterator::operator-- ()
{
    index--;
    if (index < 0)
    {
        index = subarray_size - 1;
        subarray_ptr--;
    }
    return *this;
}

} // namespace saber

#endif // deque.hpp
