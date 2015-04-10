#ifndef TREE_H_QEQFYJB1
#define TREE_H_QEQFYJB1

#include <list>
#include <map>

template <typename T, typename K = int> 
class MinHeap {
public:
    struct Node {
        Node() : key(0), dat(0), left(NULL), right(NULL) {}
        Node(T dat) : key(0), dat(dat), left(NULL), right(NULL) {}
        Node(Node* left, Node* right) : dat(dat), left(left), right(right) {}

        K key;
        T dat;
        Node* left;
        Node* right;
    };
    typedef int height_t;
    typedef std::list<Node*> Nodes;
    typedef std::map<T, short> Table;

private:
    Node* root;

public:
    MinHeap();
    MinHeap(Nodes&);
    ~MinHeap();

    Table getTable();

};


template <typename T, typename K> MinHeap<T, K>::MinHeap()
{
    root = new Node;
}

template <typename T, typename K>
typename MinHeap<T, K>::Table MinHeap<T, K>::getTable()
{
    short code;
    Table table;
    auto pass = [&code, &table, &pass](Node* node) {
        if(node->left) {
            code <<= 1;
            pass(node->left);
        }
        if(node->right) {
            code = (code << 1) + 1;
            pass(node->left);
        }
        table[node->dat] = node->key;
    };
    return table;
}

template <typename T, typename K> MinHeap<T, K>::MinHeap(Nodes& nodes)
{
    while(nodes.size() != 1) {
        nodes.sort([](const Node* a, const Node* b) {
            return a->key < b->key;
        });
        Node* left = nodes.front();
        nodes.pop_front();
        Node* right = nodes.front();
        nodes.pop_front();
        nodes.push(new Node(left, right));
    }
    root = nodes.front();
    nodes.pop_front();
}

template <typename T, typename K> MinHeap<T, K>::~MinHeap()
{
    delete root;
}

#endif /* end of include guard: TREE_H_QEQFYJB1 */
