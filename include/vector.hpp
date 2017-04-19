#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "memory.hpp"
#include "strings.defs.h"
#include "algorithm.hpp"
#include <limits>

namespace saber
{

template <typename T,
          typename Allocator = default_allocator<T>>
class vector
{
    static_assert(std::is_copy_constructible<T>::value,
                  ELEM_COPY_CONSTRUCT_ERROR);
    static_assert(std::is_destructible<T>::value,
                  ELEM_DESTROY_ERROR);

public:
    using value_type      = T;
    using pointer         = T*;
    using reference       = T&;
    using const_reference = const T&;
    using size_type       = size_t;
    using difference_type = std::ptrdiff_t;
    using allocator_type  = Allocator;

    class iterator;
    class const_iterator;

    using reverse_iterator       = saber::reverse_iterator<iterator>;
    using const_reverse_iterator = saber::reverse_iterator<const_iterator>;

    vector();
    vector(const vector& _another);
    vector(const vector& _another, const allocator_type& _allocator);
    vector(size_type _n, const allocator_type& _allocator);
    vector(size_type _n,
           const value_type& _value,
           const allocator_type& _allocator);
    vector(vector&& _another);
    vector(vector&& _another, const allocator_type& _allocator);

    vector(initializer_list<value_type> _list,
           const allocator_type& _allocator = Allocator());

    template <typename InputIterator>
    vector(InputIterator _first,
           InputIterator _last,
           const allocator_type& _allocator = Allocator());
    ~vector();

    vector& operator= (const vector& _another);
    vector& operator= (vector&& _another);

    void assign(size_type _n, const value_type& _value);
    void assign(initializer_list<value_type> _list);
    template <typename InputIterator>
    void assign(InputIterator _begin, InputIterator _end);

    size_type size() const;
    size_type max_size() const;
    bool empty() const;

    void shink_to_fit(void);
    void reserve(size_type _capacity);
    void push_back(const T& _element);
    void pop_back(void);
    template<typename... Args>
    void emplace_back(Args... _args);
    void clear(void);

    iterator insert(const_iterator _position, const value_type& _value);
    iterator insert(const_iterator _position, value_type&& _value);
    iterator insert(const_iterator _position,
                    size_type _n,
                    const value_type& _value);
    template <typename InputIterator>
    iterator insert(const_iterator _position,
                    InputIterator _begin,
                    InputIterator _end);
    iterator insert(const_iterator _position,
                    initializer_list<value_type> _list);

    template <typename... Args>
    iterator emplace(const_iterator _position, Args... _args);

    iterator erase(const_iterator _position);
    iterator erase(const_iterator _begin, const_iterator _end);

    reverse_iterator erase(const_reverse_iterator _position);
    reverse_iterator erase(const_reverse_iterator _begin,
                           const_reverse_iterator _end);

    reference at(size_type _index);
    reference operator[] (size_type _index);
    const_reference at(size_type _index) const;
    const_reference operator[] (size_type _index) const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    reverse_iterator rend();

    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

private:
    void update_vector();
    void auto_increase();
    void clear_capacity();

    template <typename U>
    void check_iterator(const U& _it);

    Allocator alloc;
    T *array;
    size_type capacity;
    size_type size_val;

    size_t update_count = 0;
};

template <typename T, typename Allocator>
class vector<T, Allocator>::iterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = typename vector::value_type;
    using difference_type   = typename vector::difference_type;
    using pointer           = typename vector::pointer;
    using reference         = typename vector::reference;
    using const_reference   = typename vector::const_reference;

    iterator(const iterator&) = default;
    ~iterator() = default;

    reference operator* ();
    reference operator[] (difference_type _n);
    const_reference operator* () const;
    const_reference operator[] (difference_type _n) const;

    iterator& operator+= (difference_type _n);
    iterator& operator-= (difference_type _n);
    iterator& operator++ ();
    iterator& operator-- ();
    const iterator operator++(int);
    const iterator operator--(int);

    iterator operator+ (difference_type _n) const;
    iterator operator- (difference_type _n) const;
    difference_type operator- (const iterator& _another) const;
    bool operator< (const iterator& _another) const;
    bool operator> (const iterator& _another) const;
    bool operator<= (const iterator& _another) const;
    bool operator>= (const iterator& _another) const;
    bool operator== (const iterator& _another) const;
    bool operator!= (const iterator& _another) const;

private:
    friend class vector;

    iterator(vector* _from, value_type* _ptr) :
        get_from(_from),
        ptr(_ptr),
        update_count(_from->update_count)
    {}

    void version_check() const
    {
        if (update_count != get_from->update_count)
        {
            stl_panic(OLD_ITERATOR);
        }
    }

    void boundary_check(difference_type _offset) const
    {
        if (ptr + _offset >= &(get_from->array[get_from->size_val])
            || ptr + _offset < &(get_from->array[0]))
        {
            stl_panic(ITERATOR_OVERFLOW);
        }
    }

    vector *get_from;
    value_type *ptr;
    size_t update_count;
};

template <typename T, typename Allocator>
class vector<T, Allocator>::const_iterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = typename vector::value_type;
    using difference_type   = typename vector::difference_type;
    using pointer           = typename vector::pointer;
    using reference         = typename vector::const_reference;
    using const_reference   = typename vector::const_reference;

    const_iterator(const const_iterator&) = default;
    ~const_iterator() = default;

    const_reference operator* ();
    const_reference operator[] (difference_type _index);

    const_iterator& operator+= (difference_type _n);
    const_iterator& operator-= (difference_type _n);
    const_iterator& operator++ ();
    const_iterator& operator-- ();
    const const_iterator operator++ (int);
    const const_iterator operator-- (int);

    const_iterator operator+ (difference_type _n) const;
    const_iterator operator- (difference_type _n) const;
    difference_type operator- (const const_iterator& _another) const;

    bool operator< (const const_iterator& _another) const;
    bool operator> (const const_iterator& _another) const;
    bool operator<= (const const_iterator& _another) const;
    bool operator>= (const const_iterator& _another) const;
    bool operator== (const const_iterator& _another) const;
    bool operator!= (const const_iterator& _another) const;

private:
    friend class vector;

    const_iterator(const vector* _from, const value_type* _ptr) :
        get_from(_from),
        ptr(_ptr),
        update_count(_from->update_count)
    {}

    void version_check() const
    {
        if (update_count != get_from->update_count)
        {
            stl_panic(OLD_ITERATOR);
        }
    }

    void boundary_check(difference_type _offset) const
    {
        if (ptr + _offset >= &(get_from->array[get_from->size_val])
            || ptr + _offset < &(get_from->array[0]))
        {
            stl_panic(ITERATOR_OVERFLOW);
        }
    }

    const vector *get_from;
    const value_type *ptr;
    size_t update_count;
};

template <typename T, typename Allocator>
vector<T, Allocator>::vector() :
    alloc()
{
    array = allocator_traits<Allocator>::allocate(alloc, 4);
    capacity = 4;
    size_val = 0;

    update_vector();
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const vector &_another) :
    vector(_another, _another.alloc)
{
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const vector &_another,
                             const allocator_type &_allocator) :
    alloc(_allocator)
{
    stl_warning(CONTAINER_COPY);
    array = allocator_traits<Allocator>::allocate(alloc, _another.size_val);

    saber::uninitialized_copy(_another.begin(), _another.end(), array);

    size_val = capacity = _another.size_val;
    update_vector();
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(size_type _n, const allocator_type &_allocator) :
    alloc(_allocator)
{
    array = allocator_traits<Allocator>::allocate(alloc, _n);
    capacity = _n;
    size_val = 0;
    update_vector();
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(size_type _n,
                             const value_type &_value,
                             const allocator_type &_allocator) :
    alloc(_allocator)
{
    array = allocator_traits<Allocator>::allocate(alloc, _n);
    capacity = _n;
    uninitialized_fill_n(array, _n, _value);
    size_val = _n;
    update_vector();
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(initializer_list<value_type> _list,
                             const allocator_type &_allocator) :
    vector(_list.begin(), _list.end(), _allocator)
{
}

template <typename T, typename Allocator>
template <typename InputIterator>
vector<T, Allocator>::vector(InputIterator _begin,
                             InputIterator _end,
                             const allocator_type& _allocator) :
    alloc(_allocator)
{
    static_assert(traits::is_input_iterator<InputIterator>::value,
                  TEMPLATE_ARG_NOT_INPUT_ITERATOR);

    array = allocator_traits<Allocator>::allocate(alloc, 4);
    capacity = 4;
    size_val = 0;

    for(; _begin != _end; ++_begin)
    {
        push_back(*_begin);
    }
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(vector &&_another) :
    alloc(std::move(_another.alloc))
{
    array = _another.array;
    _another.array = nullptr;

    size_val = _another.size_val;
    capacity = _another.capacity;

    _another.capacity = _another.size_val = 0;

    update_vector();
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(vector &&_another,
                             const allocator_type &_allocator) :
    alloc(_allocator)
{
    array = _another.array;
    _another.array = nullptr;

    size_val = _another.size_val;
    capacity = _another.capacity;

    _another.capacity = _another.size_val = 0;

    update_vector();
}

template <typename T, typename Allocator>
vector<T, Allocator>::~vector()
{
    clear();
    allocator_traits<Allocator>::deallocate(alloc, array, capacity);
}


template <typename T, typename Allocator>
vector<T, Allocator>&
vector<T, Allocator>::operator=(const vector &_another)
{
    stl_warning(CONTAINER_COPY);

    if (&_another == this)
    {
        return *this;
    }

    clear();
    alloc = _another.alloc;

    while (capacity < _another.size()) auto_increase();
    uninitialized_copy(_another.begin(), _another.end(), array);
    size_val = _another.size_val;
    update_vector();
    return *this;
}

template <typename T, typename Allocator>
vector<T, Allocator>&
vector<T, Allocator>::operator= (vector&& _another)
{
    if (&_another == this)
    {
        return *this;
    }

    clear();
    allocator_traits<Allocator>::deallocate(alloc, array, capacity);

    alloc = std::move(_another.alloc);
    array = _another.array;

    size_val = _another.size_val;
    capacity = _another.capacity;

    _another.size_val = 0;
    _another.capacity = 0;
    _another.array = nullptr;
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::assign(size_type _n, const value_type &_value)
{
    clear();

    while (capacity < _n) auto_increase();
    uninitialized_fill_n(array, _n, _value);
    update_vector();
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::assign(initializer_list<value_type> _list)
{
    assign(_list.begin(), _list.end());
}

template <typename T, typename Allocator>
template <typename InputIterator>
void
vector<T, Allocator>::assign(InputIterator _begin, InputIterator _end)
{
    static_assert(traits::is_input_iterator<InputIterator>::value,
                  TEMPLATE_ARG_NOT_INPUT_ITERATOR);

    clear();

    for (; _begin != _end; ++_begin)
    {
        push_back(*_begin);
    }

    update_vector();
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type
vector<T, Allocator>::size() const
{
    return size_val;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type
vector<T, Allocator>::max_size() const
{
    return std::numeric_limits<size_type>::max();
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::empty() const
{
    return size_val;
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::shink_to_fit()
{
    // This function makes no actual work
    // However, it manipulates the container according to ISO C++
    // So the container should be "updated"
    update_vector();
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::reserve(typename vector::size_type _capacity)
{
    if (capacity > _capacity) return;

    T *new_array = allocator_traits<Allocator>::allocate(alloc,_capacity);
    uninitialized_copy(begin(), end(), new_array);

    for (size_type i = 0; i < size_val; ++i)
    {
        allocator_traits<Allocator>::destroy(alloc,&array[i]);
    }

    allocator_traits<Allocator>::deallocate(alloc,array, capacity);
    array = new_array;

    capacity = _capacity;

    update_vector();
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::push_back(const T &_element)
{
    if (size_val == capacity) auto_increase();

    allocator_traits<Allocator>::construct(alloc, &array[size_val], _element);
    ++size_val;

    update_vector();
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::pop_back()
{
    allocator_traits<Allocator>::destroy(alloc, &array[size_val-1]);
    --size_val;

    update_vector();
}

template <typename T, typename Allocator>
template <typename... Args>
void
vector<T, Allocator>::emplace_back(Args... _args)
{
    if (size_val == capacity) auto_increase();

    allocator_traits<Allocator>::construct(alloc, &array[size_val], _args...);
    ++size_val;

    update_vector();
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::clear()
{
    for (size_type i = 0; i < size_val; ++i)
    {
        allocator_traits<Allocator>::destroy(alloc, array + i);
    }

    size_val = 0;
    update_vector();
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator _position,
                             const value_type &_value)
{
    static_assert(std::is_copy_assignable<T>::value, "" /* On hold */);
    return insert(_position, size_type(1), _value);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator _position,
                             value_type &&_value)
{
    static_assert(std::is_copy_assignable<T>::value,
                  TEMPLATE_ARG_NOT_COPY_ASSIGNABLE);
    static_assert(std::is_move_assignable<T>::value,
                  TEMPLATE_ARG_NOT_MOVE_ASSIGNABLE);
    check_iterator(_position);
    Q_UNUSED(_value);
    // Incomplete part
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator _position,
                             size_type _n,
                             const value_type &_value)
{
    static_assert(std::is_copy_assignable<T>::value,
                  TEMPLATE_ARG_NOT_COPY_ASSIGNABLE);
    check_iterator(_position);

    size_type size_after = _n + size_val;

    size_type position_diff = static_cast<size_type>(_position - cbegin());
    value_type *new_array =
            allocator_traits<Allocator>::allocate(alloc, size_after);
    {
        size_type i;
        for (i = 0; i < position_diff; ++i)
        {
            allocator_traits<Allocator>::construct(alloc,
                                                   &new_array[i],
                                                   this->operator[](i));
        }

        size_type j;
        for (j = 0; j < _n; ++j)
        {
            allocator_traits<Allocator>::construct(alloc,
                                                   &new_array[i + j],
                                                   _value);
        }
        for (; i + j < size_after; ++i)
        {
            allocator_traits<Allocator>::construct(alloc,
                                                   &new_array[i + j],
                                                   this->operator[](i));
        }
    }

    for (size_t i = 0; i < size_val; ++i)
    {
        allocator_traits<Allocator>::destroy(alloc, &array[i]);
    }
    allocator_traits<Allocator>::deallocate(alloc, array, capacity);

    array = new_array;
    new_array = nullptr;
    capacity = size_val = size_after;

    update_vector();
    return iterator(this, array + position_diff);
}

template <typename T, typename Allocator>
template <typename InputIterator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator _position,
                             InputIterator _begin,
                             InputIterator _end)
{
    static_assert(std::is_copy_assignable<T>::value, "" /* On hold */);
    check_iterator(_position);

    difference_type position_diff = _position - cbegin();

    for (; _begin != _end; ++_begin, ++_position)
    {
        _position = const_iterator(this, insert(_position, *_begin).ptr);
    }

    return begin() + position_diff;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator _position,
                             initializer_list<value_type> _list)
{
    static_assert(std::is_copy_assignable<T>::value, "" /* On hold */);
    check_iterator(_position);

    return insert(_position, _list.begin(), _list.end());
}

template <typename T, typename Allocator>
template <typename... Args>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::emplace(const_iterator _position,
                              Args...)
{
    static_assert(std::is_copy_assignable<T>::value, "" /* On hold */);
    static_assert(std::is_move_assignable<T>::value, "" /* On hold */);
    check_iterator(_position);

    // Incomplete part
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::erase(const_iterator _position)
{
    check_iterator(_position);


    // Incomplete part
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::erase(const_iterator _begin,
                            const_iterator _end)
{
    check_iterator(_begin);
    check_iterator(_end);

    for (auto it = _begin; it != _end; ++it)
    {
        allocator_traits<Allocator>::destroy(alloc, it.ptr);
    }
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator
vector<T, Allocator>::erase(const_reverse_iterator _position)
{
    check_iterator(_position.base());

    // Incomplete part
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator
vector<T, Allocator>::erase(const_reverse_iterator _begin,
                            const_reverse_iterator _end)
{
    static_assert(std::is_move_assignable<T>::value,
                  "" /* On hold */);

    check_iterator(_begin.base());
    check_iterator(_end.base());

    // Incomplete part
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference
vector<T, Allocator>::at(typename vector::size_type _index)
{
    if (_index >= size_val)
        stl_panic(ARRAY_OVERFLOW);

    return array[_index];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference
vector<T, Allocator>::operator[](typename vector::size_type _index)
{
    return at(_index);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::at(typename vector::size_type _index) const
{
    if (_index >= size_val)
        stl_panic(ARRAY_OVERFLOW);

    return array[_index];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::operator[](typename vector::size_type _index) const
{
    return at(_index);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::begin()
{
    return iterator(this, &array[0]);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::end()
{
    return iterator(this, &array[size_val]);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::begin() const
{
    return const_iterator(this, &array[0]);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::end() const
{
    return const_iterator(this, &array[size_val]);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::cbegin() const
{
    return const_iterator(this, &array[0]);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::cend() const
{
    return const_iterator(this, &array[size_val]);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator
vector<T, Allocator>::rbegin()
{
    return reverse_iterator(end());
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator
vector<T, Allocator>::rend()
{
    return reverse_iterator(begin());
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::rbegin() const
{
    return const_reverse_iterator(end());
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::rend() const
{
    return const_reverse_iterator(begin());
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::crbegin() const
{
    return const_reverse_iterator(rend());
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::crend() const
{
    return const_reverse_iterator(rbegin());
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::update_vector()
{
    if (update_count != std::numeric_limits<size_t>::max())
    {
        update_count++;
    }
    else
    {
        update_count = 0;
    }
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::auto_increase()
{
    T *new_array = allocator_traits<Allocator>::allocate(alloc,capacity * 2);

    for (size_type i = 0; i < size_val; i++)
    {
        allocator_traits<Allocator>::construct(alloc,&new_array[i], array[i]);
        allocator_traits<Allocator>::destroy(alloc,&array[i]);
    }

    allocator_traits<Allocator>::deallocate(alloc,array, capacity);
    array = new_array;
    capacity *= 2;

    update_vector();
}

template <typename T, typename Allocator>
template <typename U>
void
vector<T, Allocator>::check_iterator(const U& _it)
{
    if (_it.get_from != this)
    {
        stl_panic(UNKNOWN_REGION_ITERATOR);
    }

    _it.version_check();
    _it.boundary_check(0);
}


//template <typename T, typename Allocator>
//void vector<T, Allocator>::clear_capacity()
//{
//    for (size_type i = 0; i < size_val; i++)
//    {
//        destroy(array + i);
//    }

//    allocator_traits<Allocator>::deallocate(alloc, array, capacity);
//    capacity = 0;
//    size_val = 0;
//}



template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator::reference
vector<T, Allocator>::iterator::operator* ()
{
    return operator[](0);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator::reference
vector<T, Allocator>::iterator::operator[](difference_type _n)
{
    version_check();
    boundary_check(_n);
    return *(ptr+_n);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator::const_reference
vector<T, Allocator>::iterator::operator* () const
{
    return operator[](0);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator::const_reference
vector<T, Allocator>::iterator::operator[](difference_type _n) const
{
    version_check();
    boundary_check(_n);
    return const_cast<const_reference>(*(ptr+_n));
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator::difference_type
vector<T, Allocator>::iterator::operator-
    (const iterator &_another) const
{
    return ptr - _another.ptr;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::iterator::operator+(difference_type _n) const
{
    return iterator(get_from, ptr + _n);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::iterator::operator-(difference_type _n) const
{
    return iterator(get_from, ptr - _n);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator&
vector<T, Allocator>::iterator::operator+=(difference_type _n)
{
    version_check();
    ptr += _n;
    return *this;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator&
vector<T, Allocator>::iterator::operator-=(difference_type _n)
{
    version_check();
    ptr -= _n;
    return *this;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator&
vector<T, Allocator>::iterator::operator++()
{
    version_check();
    ++ptr;

    return *this;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator&
vector<T, Allocator>::iterator::operator--()
{
    version_check();
    --ptr;

    return *this;
}

template <typename T, typename Allocator>
const typename vector<T, Allocator>::iterator
vector<T, Allocator>::iterator::operator++(int)
{
    iterator ret = *this;
    ++ptr;
    return ret;
}

template <typename T, typename Allocator>
const typename vector<T, Allocator>::iterator
vector<T, Allocator>::iterator::operator--(int)
{
    iterator ret = *this;
    --ptr;
    return ret;
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::iterator::operator<
    (const iterator &_another) const
{
    return (ptr < _another.ptr);
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::iterator::operator>
    (const iterator &_another) const
{
    return (ptr > _another.ptr);
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::iterator::operator<=
    (const iterator &_another) const
{
    return ! operator>(_another);
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::iterator::operator>=
    (const iterator &_another) const
{
    return ! operator<(_another);
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::iterator::operator==
    (const iterator &_another) const
{
    return (ptr == _another.ptr);
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::iterator::operator!=
    (const iterator &_another) const
{
    return ! operator==(_another);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator::const_reference
vector<T, Allocator>::const_iterator::operator* ()
{
    return operator[](0);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator::const_reference
vector<T, Allocator>::const_iterator::operator[] (difference_type _n)
{
    version_check();
    boundary_check(_n);
    return *(ptr+_n);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator&
vector<T, Allocator>::const_iterator::operator+= (difference_type _n)
{
    version_check();

    ptr += _n;
    return *this;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator&
vector<T, Allocator>::const_iterator::operator-= (difference_type _n)
{
    version_check();
    ptr -= _n;
    return *this;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator&
vector<T, Allocator>::const_iterator::operator++ ()
{
    version_check();
    ++ptr;
    return *this;
}


template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator&
vector<T, Allocator>::const_iterator::operator--()
{
    version_check();
    ++ptr;
    return *this;
}

template <typename T, typename Allocator>
const typename vector<T, Allocator>::const_iterator
vector <T, Allocator>::const_iterator::operator++(int)
{
    version_check();
    iterator ret = *this;
    ++ptr;
    return ret;
}

template <typename T, typename Allocator>
const typename vector<T, Allocator>::const_iterator
vector <T, Allocator>::const_iterator::operator--(int)
{
    version_check();
    iterator ret = *this;
    --ptr;
    return ret;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::const_iterator::operator+ (difference_type _n) const
{
    return const_iterator(get_from, ptr + _n);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::const_iterator::operator- (difference_type _n) const
{
    return const_iterator(get_from, ptr - _n);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator::difference_type
vector<T, Allocator>::const_iterator::operator-
    (const const_iterator& _another) const
{
    return ptr - _another.ptr;
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::const_iterator::operator<
    (const const_iterator& _another) const
{
    return (ptr < _another.ptr);
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::const_iterator::operator>
    (const const_iterator& _another) const
{
    return (ptr > _another.ptr);
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::const_iterator::operator<=
    (const const_iterator& _another) const
{
    return ! operator>(_another);
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::const_iterator::operator>=
    (const const_iterator& _another) const
{
    return ! operator<(_another);
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::const_iterator::operator==
    (const const_iterator& _another) const
{
    return (ptr == _another.ptr);
}

template <typename T, typename Allocator>
bool
vector<T, Allocator>::const_iterator::operator!=
    (const const_iterator& _another) const
{
    return ! operator==(_another);
}

} // namespace saber

#endif // VECTOR_HPP
