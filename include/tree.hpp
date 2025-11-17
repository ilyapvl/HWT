#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>

namespace Trees
{
    // AVL tree class
    template <typename KeyT, typename Comp = std::less<KeyT>>
    class Tree
    {
    private:
        struct Node
        {
            KeyT key_;
            Node* parent_;
            Node* left_;
            Node* right_;
            int height_;

            Node(const KeyT& key);
            ~Node();

            int balanceFactor() const;
            void updateHeight();
        };

        Node* root_;
        Comp comp_;

    public:
        using iterator = Node*;

        Tree();
        ~Tree();

        Tree(const Tree&) = delete;
        Tree& operator=(const Tree&) = delete;

        void insert(const KeyT& key);
        bool contains(const KeyT& key) const;
        iterator find(const KeyT& key) const;
        iterator lower_bound(const KeyT& key) const;
        iterator upper_bound(const KeyT& key) const;
        int count_in_range(const KeyT& low, const KeyT& high) const;
        size_t size() const;
        bool empty() const;
        int height() const;
        Node* getRoot() const { return root_; }

    private:
        Node* insert(Node* node, const KeyT& key);
        Node* balance(Node* node);
        Node* rotateLeft(Node* x);
        Node* rotateRight(Node* y);
        Node* find(Node* node, const KeyT& key) const;
        Node* lower_bound(Node* node, const KeyT& key) const;
        Node* upper_bound(Node* node, const KeyT& key) const;
        Node* minNode(Node* node) const;
        Node* successor(Node* node) const;
        size_t size(Node* node) const;
    };
}

#endif // TREE_HPP
