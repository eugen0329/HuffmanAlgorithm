#ifndef TREE_H_QEQFYJB1
#define TREE_H_QEQFYJB1

template <typename T> class BTree {
private:
    struct Node {
        Node() : data(NULL), left(NULL), right(NULL) {}
        T* data;
        Node* left;
        Node* right;
    };

    Node* root;

public:
    BTree();
    ~BTree();
};

template <typename T> BTree<T>::BTree()
{
    root = new Node;
}

template <typename T> BTree<T>::~BTree()
{
    delete root;
}


#endif /* end of include guard: TREE_H_QEQFYJB1 */
