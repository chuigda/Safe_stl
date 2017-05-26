namespace saber
{

template <typename Key,
          typename Compare = less<Key>,
          typename Allocator = default_allocator<Key>>
class set
{
public:
    using key_type        = Key;
    using value_type      = Key;
    using key_compare     = Compare;
    using value_compare   = Compare;
    using allocator_type  = Allocator;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using size_type       = size_t;
    using difference_type = std::ptrdiff_t;

    class iterator;
    class const_iterator;

    using reverse_iterator       = reverse_iterator<iterator>;
    using const_reverse_iterator = reverse_iterator<const_iterator>;

    using pointer       = typename allocator_traits<Allocator>::pointer;
    using const_pointer = typename allocator_traits<Allocator>::const_pointer;

    explicit set(const Compare& _comp = Compare(),
                 const Allocator& _alloc = Allocator());
    template <typename InputIterator>
    set(InputIterator _first, InputIterator _last,
        const Compare& _comp = Compare(), 
        const Allocator& _alloc = Allocator());
    set(const set& _another, const Allocator& _alloc = Allocator());
    set(set&& _another, const Allocator& _alloc = Allocator());
    set(std::initializer_list<value_type> _ilist,
        const Compare& _comp = Compare(),
        const Allocator& _alloc = Allocator());
    
    ~set();

    set& operator= (const set& _another);
    set& operator= (set&& _another);
    set& operator= (std::initializer_list<value_type> _ilist);

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

    size_type size() const noexcept;
    size_type max_size() const noexcept;
    bool empty() const noexcept;

    template <typename... Args>
    pair<iterator, bool> emplace(Args&& ...args);
    template <typename... Args>
    iterator emplace_hint(const_iterator _pos, Args&& ...args);

    pair<iterator, bool> insert(const value_type& _value);
    pair<iterator, bool> insert(value_type&& _value);
    iterator insert(const_iterator _pos, const value_type& _value);
    iterator insert(const_iterator _pos, value_type&& _value);
    template <typename InputIterator>
    void insert(InputIterator _first, InputIterator _last);
    void insert(initializer_list<value_type> _ilist);

    void swap(set& _another);
    void clear() noexcept;
    
    key_compare key_comp() const;
    value_compare value_comp() const;

    iterator find(const key_type& _key);
    const_iterator find(const key_type& _key) const;

    size_type count(const key_type& _key) const;
    
    iterator lower_bound(const key_type& _key);
    const_iterator lower_bound(const key_type& _key) const;
    iterator upper_bound(const key_type& _key);
    const_iterator upper_bound(const key_type& _key) const;

}; // class saber::set

} // namespace saber
