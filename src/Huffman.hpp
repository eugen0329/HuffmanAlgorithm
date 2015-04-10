#ifndef TREE_H_QEQFYJB1
#define TREE_H_QEQFYJB1

#include <list>
#include <vector>
#include <map>
#include <functional>

template <typename T, typename K = int> 
class HuffmanCode {
public:
    struct Node {
        Node() : key(0), dat(0), left(NULL), right(NULL) {}
        Node(T dat) : key(0), dat(dat), left(NULL), right(NULL) {}
        Node(Node* left, Node* right) : key(0), dat(0), left(left), right(right) {}

        K key;
        T dat;
        Node* left;
        Node* right;
    };
    typedef int height_t;
    typedef std::list<Node*> Nodes;
    typedef std::vector<short> Code;
    typedef std::map<T, Code> Table;

private:
    Node* root;

public:
    HuffmanCode();
    HuffmanCode(Nodes&);
    ~HuffmanCode();

    Table* getTable();
    void inspect();
};

template <typename T, typename K>
void HuffmanCode<T, K>::inspect()
{
    std::function<void(Node*)> pass;
    pass = [&pass](Node* node) {
        if(! node->dat) {
            std::cout << "Node with no data" << std::endl;
        } else {
            std::cout << node->key << ": " << node->dat << std::endl;
        }
        if(node->left) pass(node->left);
        if(node->right) pass(node->right);
    };
    pass(root);
}

template <typename T, typename K> HuffmanCode<T, K>::HuffmanCode()
{
    root = new Node;
}

template <typename T, typename K>
typename HuffmanCode<T, K>::Table* HuffmanCode<T, K>::getTable()
{
    Code code;
    Table* table = new Table;
    std::function<void(Node*)> pass;
    pass = [&code, &table, &pass](Node* node) {
        if(node->left != NULL) {
            //code <<= 1;
            code.push_back(0);
            pass(node->left);
        }
        if(node->right != NULL) {
            //code = (code << 1) + 1;
            code.push_back(1);
            pass(node->right);
        }
        if(node->dat != 0) (*table)[node->dat] = code;
        code.pop_back();
    };
    pass(root);
    return table;
}

template <typename T, typename K> HuffmanCode<T, K>::HuffmanCode(Nodes& nodes)
{
    if(nodes.size() == 0) return ;
    while(nodes.size() != 1) {
        nodes.sort([](const Node* a, const Node* b) ->bool{
            return a->key < b->key;
        });
        Node* left = nodes.front();
        nodes.pop_front();
        Node* right = nodes.front();
        nodes.pop_front();
        Node* parent = new HuffmanCode<T, K>::Node(left, right);
        parent->key = parent->left->key + parent->right->key;
        nodes.push_back(parent);
    }
    root = nodes.front();
    nodes.pop_front();
}

template <typename T, typename K> HuffmanCode<T, K>::~HuffmanCode()
{
    delete root;
}

#endif /* end of include guard: TREE_H_QEQFYJB1 */
