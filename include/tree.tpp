#ifndef TREE_TPP
#define TREE_TPP

#include "tree.hpp"
namespace Trees
{
    template <typename KeyT, typename Comp>
    Tree<KeyT, Comp>::Node::Node(const KeyT& key)
        : key_(key), parent_(nullptr), left_(nullptr), right_(nullptr), height_(0)
    {
    }

    template <typename KeyT, typename Comp>
    Tree<KeyT, Comp>::Node::~Node()
    {
        delete left_;
        delete right_;
    }

    template <typename KeyT, typename Comp>
    int Tree<KeyT, Comp>::Node::balanceFactor() const
    {
        int leftHeight = left_ ? left_->height_ : -1;
        int rightHeight = right_ ? right_->height_ : -1;

        return leftHeight - rightHeight;
    }

    template <typename KeyT, typename Comp>
    void Tree<KeyT, Comp>::Node::updateHeight()
    {
        int leftHeight = left_ ? left_->height_ : -1;
        int rightHeight = right_ ? right_->height_ : -1;
        height_ = std::max(leftHeight, rightHeight) + 1;
    }

    template <typename KeyT, typename Comp>
    Tree<KeyT, Comp>::Tree() : root_(nullptr)
    {
    }

    template <typename KeyT, typename Comp>
    Tree<KeyT, Comp>::~Tree()
    {
        delete root_;
    }

    template <typename KeyT, typename Comp>
    void Tree<KeyT, Comp>::insert(const KeyT& key)
    {
        root_ = insert(root_, key);
    }

    template <typename KeyT, typename Comp>
    bool Tree<KeyT, Comp>::contains(const KeyT& key) const
    {
        return find(key) != nullptr;
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::iterator Tree<KeyT, Comp>::find(const KeyT& key) const
    {
        return find(root_, key);
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::iterator Tree<KeyT, Comp>::lower_bound(const KeyT& key) const
    {
        return lower_bound(root_, key);
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::iterator Tree<KeyT, Comp>::upper_bound(const KeyT& key) const
    {
        return upper_bound(root_, key);
    }

    template <typename KeyT, typename Comp>
    int Tree<KeyT, Comp>::count_in_range(const KeyT& low, const KeyT& high) const
    {
        if (comp_(high, low)) return 0;
        
        auto start = upper_bound(low);
        if (!start) return 0;
        
        int count = 0;
        auto current = start;
        
        while (current && !comp_(high, current->key_))
        {
            if (comp_(low, current->key_))
            {
                count++;
            }

            current = successor(current);
        }
        
        return count;
    }

    template <typename KeyT, typename Comp>
    size_t Tree<KeyT, Comp>::size() const
    {
        return size(root_);
    }

    template <typename KeyT, typename Comp>
    bool Tree<KeyT, Comp>::empty() const
    {
        return root_ == nullptr;
    }

    template <typename KeyT, typename Comp>
    int Tree<KeyT, Comp>::height() const
    {
        return root_ ? root_->height_ : -1;
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::Node* Tree<KeyT, Comp>::insert(Node* node, const KeyT& key)
    {
        if (!node)
        {
            return new Node(key);
        }

        if (comp_(key, node->key_))
        {
            node->left_ = insert(node->left_, key);
            if (node->left_) node->left_->parent_ = node;
        }
        else if (comp_(node->key_, key))
        {
            node->right_ = insert(node->right_, key);
            if (node->right_) node->right_->parent_ = node;
        }
        else
        {
            return node;
        }

        node->updateHeight();
        return balance(node);
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::Node* Tree<KeyT, Comp>::balance(Node* node)
    {
        int bf = node->balanceFactor();

        if (bf > 1)
        {
            if (node->left_ && node->left_->balanceFactor() < 0)
            {
                node->left_ = rotateLeft(node->left_);
            }

            return rotateRight(node);
        }
        
        if (bf < -1)
        {
            if (node->right_ && node->right_->balanceFactor() > 0)
            {
                node->right_ = rotateRight(node->right_);
            }

            return rotateLeft(node);
        }

        return node;
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::Node* Tree<KeyT, Comp>::rotateLeft(Node* x)
    {
        Node* y = x->right_;
        Node* T2 = y->left_;

        y->left_ = x;
        x->right_ = T2;

        if (T2) T2->parent_ = x;
        y->parent_ = x->parent_;
        x->parent_ = y;

        x->updateHeight();
        y->updateHeight();

        return y;
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::Node* Tree<KeyT, Comp>::rotateRight(Node* y)
    {
        Node* x = y->left_;
        Node* T2 = x->right_;

        x->right_ = y;
        y->left_ = T2;

        if (T2) T2->parent_ = y;
        x->parent_ = y->parent_;
        y->parent_ = x;

        y->updateHeight();
        x->updateHeight();

        return x;
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::Node* Tree<KeyT, Comp>::find(Node* node, const KeyT& key) const
    {
        while (node)
        {
            if (comp_(key, node->key_))
            {
                node = node->left_;
            }

            else if (comp_(node->key_, key))
            {
                node = node->right_;
            }


            else
            {
                return node;
            }
        }
        return nullptr;
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::Node* Tree<KeyT, Comp>::lower_bound(Node* node, const KeyT& key) const
    {
        Node* result = nullptr;
        while (node)
        {
            if (!comp_(node->key_, key))
            {
                result = node;
                node = node->left_;
            }

            else
            {
                node = node->right_;
            }
        }

        return result;
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::Node* Tree<KeyT, Comp>::upper_bound(Node* node, const KeyT& key) const
    {
        Node* result = nullptr;
        while (node)
        {
            if (comp_(key, node->key_))
            {
                result = node;
                node = node->left_;
            }

            else
            {
                node = node->right_;
            }
        }

        return result;
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::Node* Tree<KeyT, Comp>::minNode(Node* node) const
    {
        while (node && node->left_)
        {
            node = node->left_;
        }



        return node;
    }

    template <typename KeyT, typename Comp>
    typename Tree<KeyT, Comp>::Node* Tree<KeyT, Comp>::successor(Node* node) const
    {
        if (!node) return nullptr;
        
        if (node->right_)
        {
            return minNode(node->right_);
        }
        
        Node* parent = node->parent_;

        while (parent && node == parent->right_)
        {
            node = parent;
            parent = parent->parent_;
        }

        return parent;
    }

    template <typename KeyT, typename Comp>
    size_t Tree<KeyT, Comp>::size(Node* node) const
    {
        if (!node) return 0;
        return 1 + size(node->left_) + size(node->right_);
    }
}

#endif // TREE_CPP
