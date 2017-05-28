// Note : this is an internal class.
// Nobody but library developer should try to use it directly.

#ifndef FREE_TREE_HPP
#define FREE_TREE_HPP

#include "functional.hpp"
#include "memory.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

namespace saber
{

template <typename T = void, typename LessPredicator = void>
struct c8_equivalent
{
    constexpr bool operator() (const T& _a, const T& _b,
                               const LessPredicator& _less_pred) const
    { return (!_less_pred(_a, _b)) && (!_less_pred(_b, _a)); }
};

template <>
struct c8_equivalent<void, void>
{
    template <typename A, typename B, typename LessPredicator>
    constexpr auto operator() (A&& _a, B&& _b,
                               const LessPredicator& _less_pred) const
        ->
        decltype( (! _less_pred(std::forward<A>(_a), std::forward<B>(_b)) ) &&
                  (! _less_pred(std::forward<B>(_b), std::forward<A>(_a)) ) )
    { return (!_less_pred(_a, _b)) && (!_less_pred(_b, _a)); }
};

// I don't use RB-Tree or AVL-Tree since I'm not good at data structure
// However, this problem could be solved soon
template <typename ItemType,
          typename ItemCompare,
          typename Allocator,
          bool Duplicate>
class free_tree
{
public:
    using allocator_type  = Allocator;
    using size_type       = size_t;
    using difference_type = std::ptrdiff_t;

    class tree_iterator;

    using pointer       = typename allocator_traits<Allocator>::pointer;
    using const_pointer = typename allocator_traits<Allocator>::const_pointer;

    explicit free_tree(const ItemCompare& _comp = ItemCompare(),
                       const Allocator& _alloc = Allocator());
    ~free_tree();

    template <typename... Args>
    pair<tree_iterator, bool> emplace(Args&& ..._args);

    tree_iterator find(const ItemType& _key);
    tree_iterator erase(tree_iterator _pos);

private:
    struct tree_node
    {
        ItemType item;
        size_type count;
        tree_node *left_child = nullptr;
        tree_node *right_child = nullptr;
    };

    using node_allocator_type =
        typename Allocator::template rebind<tree_node>::other;

    tree_node *root = nullptr;
}; // class saber::free_tree



template <typename ItemType,
          typename ItemCompare,
          typename Allocator,
          bool DuplicateAllowed>
class free_tree::tree_iterator
{
public:

private:
}; // class saber::free_tree::tree_iterator

} // namespace saber

#endif // FREE_TREE_HPP
