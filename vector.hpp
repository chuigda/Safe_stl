#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "safe_stl_general.hpp"
#include "strings.defs.h"
#include <iterator>

namespace saber
{

template <typename T,
          typename Allocator = default_allocator<T>>
class vector
{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    vector();
    vector(const vector& _another);
    vector(vector&& _another);

    vector& operator= (const vector& _another);
    vector& operator= (vector&& _another);
    ~vector();

    size_type size() const;
    size_type max_size() const;

    void shink_to_fit(void);
    void reserve(size_type _capacity);
    void push_back(const T& _element);
    void pop_back(void);

    T& at(size_type _index);
    T& operator[] (size_type _index);
    const T& at(size_type _index) const;
    const T& operator[] (size_type _index) const;

    class iterator;

    iterator begin();
    iterator end();

private:
    void update_vector();
    void auto_increase();

    Allocator alloc;

    T *array;
    time_t update_time;

    size_type capacity;
    size_type size_val;
};

template <typename T, typename Allocator>
vector<T, Allocator>::vector()
{
    array = allocator_traits<Allocator>::allocate(alloc, 4);
    capacity = 4;
    size_val = 0;

    update_vector();
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const vector &_another) :
    alloc(_another.alloc)
{
    stl_warning(CONTAINER_COPY);

    array = allocator_traits<Allocator>::allocate(alloc,_another.size_val);

    for (size_type i = 0; i < _another.size_val; ++i)
    {
        allocator_traits<Allocator>::construct(alloc,&array[i], _another[i]);
    }

    size_val = capacity = _another.size_val;
    update_vector();
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
vector<T, Allocator>&
vector<T, Allocator>::operator=(const vector &_another)
{
    stl_warning(CONTAINER_COPY);

    if (&_another == this)
    {
        return *this;
    }

    alloc = _another.alloc;
    array = allocator_traits<Allocator>::allocate(alloc,_another.size_val);
    for (size_type i = 0; i < _another.size_val; ++i)
    {
        allocator_traits<Allocator>::construct(alloc,&array[i], _another[i]);
    }

    size_val = capacity = _another.size_val;

    update_vector();
    return *this;
}

template <typename T, typename Allocator>
vector<T, Allocator>&
vector<T, Allocator>::operator =(vector&& _another)
{
    if (&_another == this)
    {
        return *this;
    }

    alloc = std::move(_another.alloc);
    array = _another.array;

    size_val = _another.size_val;
    capacity = _another.capacity;

    _another.size_val = 0;
    _another.capacity = 0;
    _another.array = nullptr;
}

template <typename T, typename Allocator>
vector<T, Allocator>::~vector()
{
    for (size_type i = 0; i < size_val; ++i)
    {
        allocator_traits<Allocator>::destroy(alloc,&array[i]);
    }

    allocator_traits<Allocator>::deallocate(alloc,array, capacity);
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
    return capacity;
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
vector<T, Allocator>::reserve(vector::size_type _capacity)
{
    if (capacity > _capacity) return;

    T *new_array = allocator_traits<Allocator>::allocate(alloc,_capacity);
    for (size_type i = 0; i < size_val; ++i)
    {
        allocator_traits<Allocator>::construct(alloc,&new_array[i], array[i]);
    }

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

    allocator_traits<Allocator>::construct(alloc,&array[size_val], _element);
    ++size_val;

    update_vector();
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::pop_back()
{
    allocator_traits<Allocator>::destroy(alloc,&array[size_val-1]);
    --size_val;

    update_vector();
}

template <typename T, typename Allocator>
T&
vector<T, Allocator>::at(vector::size_type _index)
{
    if (_index >= size_val)
        stl_panic(ARRAY_OVERFLOW);

    return array[_index];
}

template <typename T, typename Allocator>
T&
vector<T, Allocator>::operator[](vector::size_type _index)
{
    return at(_index);
}

template <typename T, typename Allocator>
const T&
vector<T, Allocator>::at(vector::size_type _index) const
{
    if (_index >= size_val)
        stl_panic(ARRAY_OVERFLOW);

    return array[_index];
}

template <typename T, typename Allocator>
const T&
vector<T, Allocator>::operator[](vector::size_type _index) const
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

template<typename T, typename Allocator>
void
vector<T, Allocator>::update_vector()
{
    update_time = time(nullptr);
}

template<typename T, typename Allocator>
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
}

template <typename T, typename Allocator>
class vector<T, Allocator>::iterator :
        public std::iterator<std::random_access_iterator_tag,
        value_type,
        difference_type,
        pointer,
        reference>
{
public:
    iterator(const iterator&) = default;
    ~iterator() = default;

    value_type& operator* ();
    value_type& operator[] (size_type _n);
    difference_type operator- (const iterator& _another);
    iterator operator+ (size_type _n);
    iterator operator- (size_type _n);
    iterator& operator+= (size_type _n);
    iterator& operator-= (size_type _n);
    iterator& operator++ ();
    iterator& operator-- ();
    bool operator< (const iterator& _another) const;
    bool operator> (const iterator& _another) const;
    bool operator== (const iterator& _another) const;
    bool operator!= (const iterator& _another) const;

private:
    friend class vector;

    iterator(vector* _from, T* _ptr) :
        get_from(_from),
        ptr(_ptr),
        update_time(_from->update_time)
    {}

    vector *get_from;
    T *ptr;
    time_t update_time;
};

template<typename T, typename Allocator>
typename vector<T, Allocator>::value_type&
vector<T, Allocator>::iterator::operator*()
{
    return operator[](0);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::value_type&
vector<T, Allocator>::iterator::operator[](size_type _n)
{
    if (update_time != get_from->update_time)
    {
        stl_panic(OLD_ITERATOR);
    }

    if (ptr+_n >= &(get_from->array[get_from->size_val])
            || ptr+_n < &(get_from->array[0]))
    {
        stl_panic(ITERATOR_OVERFLOW);
    }

    return *(ptr+_n);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::difference_type
vector<T, Allocator>::iterator::operator-
    (const saber::vector<T, Allocator>::iterator &_another)
{
    return ptr - _another.ptr;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::iterator::operator+(size_type _n)
{
    return iterator(get_from, ptr + _n);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::iterator::operator-(size_type _n)
{
    return iterator(get_from, ptr - _n);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator&
vector<T, Allocator>::iterator::operator+=(size_type _n)
{
    ptr += _n;
    return *this;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator&
vector<T, Allocator>::iterator::operator-=(size_type _n)
{
    ptr -= _n;
    return *this;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator&
vector<T, Allocator>::iterator::operator++()
{
    if (update_time != get_from->update_time)
    {
        stl_panic(OLD_ITERATOR);
    }

    ++ptr;

    return *this;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator&
saber::vector<T, Allocator>::iterator::operator--()
{
    if (update_time != get_from->update_time)
    {
        stl_panic(OLD_ITERATOR);
    }

    --ptr;

    return *this;
}

template<typename T, typename Allocator>
bool vector<T, Allocator>::iterator::operator<
    (const saber::vector<T, Allocator>::iterator &_another) const
{
    return (ptr < _another.ptr);
}

template<typename T, typename Allocator>
bool vector<T, Allocator>::iterator::operator>
    (const saber::vector<T, Allocator>::iterator &_another) const
{
    return ! operator<(_another);
}

template<typename T, typename Allocator>
bool vector<T, Allocator>::iterator::operator==
    (const saber::vector<T, Allocator>::iterator &_another) const
{
    return (ptr == _another.ptr);
}

template<typename T, typename Allocator>
bool vector<T, Allocator>::iterator::operator!=
    (const saber::vector<T, Allocator>::iterator &_another) const
{
    return ! operator==(_another);
}

}

#endif // VECTOR_HPP
