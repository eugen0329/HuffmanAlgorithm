#ifndef TREE_H_QEQFYJB1
#define TREE_H_QEQFYJB1

#include <list>
#include <vector>
#include <map>
#include <functional>
#include <initializer_list>

#include "helpers.h"

typedef std::string::iterator strIter_t;

template <typename T, typename K = int>
class HuffmanCode {
public:
    struct Node {
        Node(K key = 0, T dat = 0) : key(key), dat(dat), left(NULL), right(NULL) {}
        Node(Node* left, Node* right, K key = 0) : key(key), dat(0), left(left), right(right) {}

        K key;
        T dat;
        Node* left;
        Node* right;
    };
    typedef std::list<Node*> Nodes;

    typedef std::vector<short> Code;
    typedef std::map<T, Code> Table;
    typedef typename std::map<T, int> counters_t;
    typedef typename std::map<T, int>::iterator countersIter_t;

    typedef typename Table::iterator tableIt_t;
    typedef typename Code::iterator codeIt_t;
private:
    Node* root;
    Table table;

public:
    HuffmanCode(std::string& buf)
    {
        Nodes nodes;
        makeNodes(buf, nodes);
        if(nodes.size() == 0) return ;
        while(nodes.size() != 1) {
            nodes.sort([](Node* a, Node* b){ return a->key < b->key; });
            Node* left = shiftList(nodes);
            Node* right = shiftList(nodes);
            nodes.push_back(new Node(left, right, left->key + right->key));
        }
        root = nodes.front();
        nodes.pop_front();
        makeTable();
    }

private:
    void makeNodes(std::string& buf, Nodes& nodes)
    {
        std::map<T, int> countersMap;

        std::string::iterator strLim = buf.end();
        for(strIter_t it = buf.begin(); it != strLim; ++it) countersMap[*it] ++;

        countersIter_t mapLim = countersMap.end();
        for(countersIter_t c = countersMap.begin(); c != mapLim; ++c) {
            nodes.push_back(new Node((*c).second, (*c).first));
        }
    }

public:
    void makeTable()
    {
        Code code;
        std::function<void(Node*)> pass;
        pass = [&code, this, &pass](Node* node) {
            if(node->left != NULL) {
                code.push_back(0); //code <<= 1;
                pass(node->left);
            }
            if(node->right != NULL) {
                code.push_back(1); //code = (code << 1) + 1;
                pass(node->right);
            }
            if(node->dat != 0) table[node->dat] = code;
            code.pop_back();
        };
        pass(root);
    }

    HuffmanCode(Nodes&);
    HuffmanCode() { root = new Node; }
    ~HuffmanCode() {}

    void inspectTable()
    {
        for(tableIt_t it = table.begin(); it != table.end(); ++it) {
            std::string code;
            for(codeIt_t cit = it->second.begin(); cit != it->second.end(); ++cit) {
                code += (*cit == 1 ? '1' : '0');
            }
            std::cout <<  it->first << ": " << code << std::endl;
        }
    }
    void inspectHeap()
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
};

#endif /* end of include guard: TREE_H_QEQFYJB1 */
