#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_

#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

template <typename Key, typename Value>
class BinarySearchTree
{
private:
    // 定义节点结构体
    struct Node
    {
        Key key;
        Value value;
        Node *left;
        Node *right;

    public:
        Node(Key key, Value value) : key(key), value(value), left(nullptr), right(nullptr) {}
        Node(Node* node) 
        {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }
        // ~Node()
        // {
        //     delete left;
        //     delete right;
        // }
    };

    Node *root;
    int count;

public:
    BinarySearchTree()
    {
        root = nullptr;
        count = 0;
    }
    ~BinarySearchTree()
    {
        destory(root);
    }

    inline int size() { return count; }
    inline bool isEmpty() { return count == 0; }

    void insert(Key key, Value value)
    {
        root = insert(root, key, value);
    }

    bool contain(Key key)
    {
        return contain(root, key);
    }

    Value *search(Key key)
    {
        return search(root, key);
    }

    void preOrder()
    {
        preOrder(root);
    }

    void inOrder()
    {
        inOrder(root);
    }

    void postOrder()
    {
        postOrder(root);
    }

    void levelOrder()
    {
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *node = q.front();
            q.pop();

            cout << node->key << endl;

            if (q->left)
            {
                q.push(q->left);
            }
            if (q->right)
            {
                q.push(q->right);
            }
        }
    }

    Key minimum()
    {
        assert(count > 0);
        Node *node = minimum(root);
        return node->key;
    }

    Key maximum()
    {
        assert(count > 0);
        Node *node = maximun(root);
        return node->key;
    }

    void removeMinimum()
    {
        if (root)
        {
            root = removeMinimum(root);
        }
    }

    void removeMaximum()
    {
        if (root)
        {
            root = removeMaximum(root);
        }
    }

    void remove(Key key)
    {
        root = remove(root, key);
    }

private:
    // 带有私有属性的函数不可以被定义到类外
    Node *insert(Node *node, Key key, Value value)
    {
        // 如果为空的话，意味着已经找到了我们要插入的位置，完成插入之后返回
        if (node == nullptr)
        {
            count++;
            return new Node(key, value);
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

    bool contain(Node *node, Key key)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (node->key == key)
        {
            return true;
        }
        else if (node->key > key)
        {
            return contain(node->left, key);
        }
        else
        {
            return contain(node->right, key);
        }
    }

    Value *search(Node *node, Key key)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (key == node->key)
        {
            return &(node->value);
        }
        else if (node->key > key)
        {
            return search(node->left, key);
        }
        else
        {
            return search(node->right, key);
        }
    }

    void preOrder(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        cout << node->key << endl;
        preOrder(node->left);
        preOder(node->right);
    }

    void inOrder(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        inOrder(node->left);
        cout << node->key << endl;
        inOrder(node->right);
    }

    void postOrder(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        postOrder(node->left);
        postOrder(node->right);
        cout << node->key << endl;
    }

    void destory(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        destory(node->left);
        destory(node->right);
        delete node;
        count--;
    }

    Node *minimum(Node *node)
    {
        if (node->left == nullptr)
        {
            return node;
        }
        return minimum(node->left);
    }

    Node *maximum(Node *node)
    {
        if (node->left == nullptr)
        {
            return node;
        }
        return maximum(node->left);
    }

    Node* removeMinimum(Node* node)
    {
        if (node->left == nullptr)
        {
            Node* rightNode = node->right;
            delete node;
            count--;
            return rightNode;
        }

        node->left = removeMinimum(node->left);
        
    }

    Node* removeMaximum(Node* node)
    {
        if (node->right == nullptr)
        {
            Node* leftNode = node->left;
            delete node;
            count--;
            return leftNode;
        }
        node->right = removeMaximum(node->right);
    }

    Node* remove(Node* node, Key key)
    {
        // 查找结果为null的话，不做任何操作
        if (node == nullptr)
        {
            return nullptr;
        }

        if (node->key > key)
        {
            node->left = remove(node->left, key);
            return node->left;
        }
        else if (node->key < key)
        {
            node->right = remove(node->right, key);
            return node->right;
        }
        else
        {
            if (node->left == nullptr)
            {
                Node* rightNode = node->right;
                delete node;
                count --;
                return rightNode;
            }

            if (node->right == nullptr)
            {
                Node* leftNode = node->left;
                delete node;
                count --;
                return leftNode;
            }

            // 当该节点的左右子树都存在
            Node* successor = Node(minimum(node->right));
            count++;  // 之后的removeMin会执行--操作，因此这里的操作使得配置完successor这个node之前，节点总数不发生变化            
            // 删除后继节点
            successor->right = removeMinimum(node->right);
            successor->left = node->left;
            delete node;
            count--;
            return successor;
        }
    }
};

#endif // __BINARY_SEARCH_TREE_H_