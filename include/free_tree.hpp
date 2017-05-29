// Note : this is an internal file.
// Nobody but library developer should try to use it directly.

#ifndef FREE_TREE_HPP
#define FREE_TREE_HPP

#include "functional.hpp"
#include "memory.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

namespace saber
{

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
    using value_type      = ItemType;
    using value_compare   = ItemCompare;
    using size_type       = size_t;
    using difference_type = std::ptrdiff_t;

    class tree_iterator;

    using reference       = ItemType&;
    using const_reference = const ItemType&;
    using pointer       = typename allocator_traits<Allocator>::pointer;
    using const_pointer = typename allocator_traits<Allocator>::const_pointer;

    explicit free_tree(const ItemCompare& _comp = ItemCompare(),
                       const Allocator& _alloc = Allocator());
    ~free_tree();

    template <typename... Args>
    pair<tree_iterator, bool> emplace(Args&& ..._args);
    tree_iterator find(const ItemType& _key);
    tree_iterator erase(tree_iterator _pos);

    tree_iterator begin() noexcept;
    tree_iterator end() noexcept;

private:
    friend class tree_iterator;
    struct tree_node_base
    {
        enum class side_as_child : char
        {
            LeftSide,
            RightSide
        }
        side;

        tree_node_base() = default;
        ~tree_node_base() = default;

        tree_node_base *left_child = nullptr;
        tree_node_base *right_child = nullptr;
        tree_node_base *parent = nullptr;
    };

    struct tree_node : public tree_node_base
    {
        template <typename... Args>
        tree_node(Args&&... _args) :
            tree_node_base(), item(std::forward<Args>(_args)...)
        {}
        ~tree_node() {}
        ItemType item;
        size_type count = 1;
    };

    using node_allocator_type =
        typename Allocator::template rebind<tree_node>::other;

    value_compare less_comp;
    allocator_type alloc;
    node_allocator_type node_alloc;
    tree_node_base *root;
}; // class saber::free_tree



template <typename ItemType,
          typename ItemCompare,
          typename Allocator,
          bool Duplicate>
class free_tree<ItemType, ItemCompare, Allocator, Duplicate>::tree_iterator
{
    friend class free_tree;
public:
    using value_type      = typename free_tree::value_type;
    using reference       = typename free_tree::reference;
    using const_reference = typename free_tree::const_reference;
    using size_type       = typename free_tree::size_type;
    using difference_type = typename free_tree::difference_type;

    explicit tree_iterator() = default;
    ~tree_iterator() = default;

    reference operator* (void);
    tree_iterator& operator++ (void);
    tree_iterator& operator-- (void);

    bool operator== (const tree_iterator& _another) const;
    bool operator!= (const tree_iterator& _another) const;

private:
    using tree_node_base = typename free_tree::tree_node_base;

    explicit tree_iterator(tree_node_base* _node) : actual_node(_node) {}
    tree_node_base *actual_node = nullptr;
}; // class saber::free_tree::tree_iterator



template <typename IT, typename IC, typename AL, bool DUP>
free_tree<IT, IC, AL, DUP>::free_tree(const IC& _comp, const AL& _alloc) :
    less_comp(_comp),
    alloc(_alloc),
    node_alloc(alloc)
{
    root = new tree_node_base();
    root->parent = root;
    root->right_child = root;
    root->left_child = root;
}

template <typename IT, typename IC, typename AL, bool DUP>
free_tree<IT, IC, AL, DUP>::~free_tree()
{
    // On hold.
    delete root;
}

template <typename IT, typename IC, typename AL, bool DUP>
template <typename... Args>
pair<typename free_tree<IT, IC, AL, DUP>::tree_iterator, bool>
free_tree<IT, IC, AL, DUP>::emplace(Args&& ..._args)
{
    tree_node *new_node =
            allocator_traits<node_allocator_type>::allocate(node_alloc, 1);
    construct(new_node, std::forward<Args>(_args)...);

    if (root->left_child == root)
    {
        root->left_child = new_node;
        new_node->parent = root;
        new_node->side = tree_node_base::side_as_child::LeftSide;

        return pair<tree_iterator, bool>(
                    tree_iterator(root->left_child),
                    true);
    }
    else
    {
        for (tree_node_base *node_iter = root->left_child;;)
        {
            if (less_comp(new_node->item,
                          reinterpret_cast<tree_node*>(node_iter)->item))
            {
                if (node_iter->left_child == nullptr)
                {
                    node_iter->left_child = new_node;
                    new_node->parent = node_iter;
                    new_node->side = tree_node_base::side_as_child::LeftSide;

                    return pair<tree_iterator, bool>(
                                tree_iterator(node_iter->left_child),
                                true);
                }
                else
                {
                    node_iter = node_iter->left_child;
                }
            }
            else if (less_comp(reinterpret_cast<tree_node*>(node_iter)->item,
                               new_node->item))
            {
                if (node_iter->right_child == nullptr)
                {
                    node_iter->right_child = new_node;
                    new_node->parent = node_iter;
                    new_node->side = tree_node_base::side_as_child::RightSide;

                    return pair<tree_iterator, bool>(
                                tree_iterator(node_iter->right_child),
                                true);
                }
                else
                {
                    node_iter = node_iter->right_child;
                }
            }
            else
            {
                reinterpret_cast<tree_node*>(node_iter)->count++;
                destroy_at(new_node);
                allocator_traits<node_allocator_type>::deallocate(node_alloc,
                                                                  new_node,
                                                                  1);
                return pair<tree_iterator, bool>(
                            tree_iterator(node_iter),
                            DUP);
            }
        }
    }
}

template <typename IT, typename IC, typename AL, bool DUP>
typename free_tree<IT, IC, AL, DUP>::tree_iterator
free_tree<IT, IC, AL, DUP>::begin() noexcept
{
    if (root->left_child == root) return tree_iterator(root);

    tree_node_base *node_it;
    for(node_it = root->left_child;
        node_it->left_child != nullptr;
        node_it = node_it->left_child);
    return tree_iterator(node_it);
}

template <typename IT, typename IC, typename AL, bool DUP>
typename free_tree<IT, IC, AL, DUP>::tree_iterator
free_tree<IT, IC, AL, DUP>::end() noexcept
{
    return tree_iterator(root);
}



template <typename IT, typename IC, typename AL, bool DUP>
typename free_tree<IT, IC, AL, DUP>::tree_iterator::reference
free_tree<IT, IC, AL, DUP>::tree_iterator::operator*()
{
    return reinterpret_cast<tree_node*>(actual_node)->item;
}

template <typename IT, typename IC, typename AL, bool DUP>
typename free_tree<IT, IC, AL, DUP>::tree_iterator&
free_tree<IT, IC, AL, DUP>::tree_iterator::operator++ ()
{
    // This algorithm is also copy-pasted from EA-STL.
    if (actual_node->right_child != nullptr)
    {
        actual_node = actual_node->right_child;

        while (actual_node->left_child)
        {
            actual_node = actual_node->left_child;
        }
    }
    else
    {
        tree_node_base *node_iter = actual_node->parent;

        while (actual_node == node_iter->right_child)
        {
            actual_node = node_iter;
            node_iter = node_iter->parent;
        }

        if (actual_node->right_child != node_iter)
        {
            actual_node = node_iter;
        }
    }

    return *this;
}

template <typename IT, typename IC, typename AL, bool DUP>
bool
free_tree<IT, IC, AL, DUP>::tree_iterator::operator== (
        const tree_iterator& _another) const
{
    return actual_node == _another.actual_node;
}

template <typename IT, typename IC, typename AL, bool DUP>
bool
free_tree<IT, IC, AL, DUP>::tree_iterator::operator!= (
        const tree_iterator& _another) const
{
    return !operator== (_another);
}

} // namespace saber

#endif // FREE_TREE_HPP
