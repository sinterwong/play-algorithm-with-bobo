#include "bst.hpp"
/*
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    root = nullptr;
    count = 0;
}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    //  TODO ~BinarySearchTree()
}

template <typename Key, typename Value>
inline void BinarySearchTree<Key, Value>::insert(Key key, Value value)
{
    root = insert(root, value, key);
}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::Node *BinarySearchTree<Key, Value>::insert(Node *node, Key key, Value value)
{

    // 如果为空的话，意味着已经找到了我们要插入的位置，完成插入之后返回
    if (node == nullptr)
    {
        node->key = key;
        node->value = value;
    }

    if (node->key == key)
    {
        node->value = value;
    }
    else if (node->key > key)
    {
        node->left = insert(node->left, key, value);
    }
    else
    {
        node->right = insert(node->right, key, value);
    }

    return node;
}
*/
// template class BinarySearchTree<string, int>;