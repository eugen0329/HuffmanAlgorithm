#ifndef TREE_H_QEQFYJB1
#define TREE_H_QEQFYJB1

template <typename T> class BTree {
public:
    struct Node {
        Node() : dat(NULL), left(NULL), right(NULL) {}
        Node(T dat) : dat(dat), left(NULL), right(NULL) {}

        T dat;
        Node* left;
        Node* right;
    };

private:
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
