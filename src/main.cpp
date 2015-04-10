#include <iostream>
#include <cstdlib> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <fstream>
#include <streambuf>

#include <string>
#include <list>
#include <map>

#include "helpers.h"
#include "Huffman.hpp"


typedef std::string::iterator strIter_t;

typedef std::map<char, int> chCountMap_t;
typedef std::map<char, int>::iterator chCountMapIt_t;

typedef HuffmanCode<char>::Table table_t;
typedef HuffmanCode<char>::Code code_t;
typedef HuffmanCode<char>::Node node_t;
typedef HuffmanCode<char>::Nodes nodes_t;
typedef nodes_t::iterator nodesIt_t;


int readInpFile(const char *& fname, std::string& buffer);
void countChars(std::string& buf, nodes_t& nodesList);

void displayNodes(nodes_t& list);

void inspectTable(table_t& list)
{
    for(table_t::iterator it = list.begin(); it != list.end(); ++it) {
        std::string code;
        for(code_t::iterator cit = it->second.begin(); cit != it->second.end(); ++cit) {
            code += (*cit == 1 ? '1' : '0');
        }
        std::cout <<  it->first << ": " << code << std::endl;
    }
}


int main(int argc, const char *argv[])
{
    if(argc != 2) {
        std::cout << "ERROR: Wrong cmdline arguments list" << std::endl;
        return EXIT_FAILURE;
    }
    std::string inpBuf;
    if(readInpFile(argv[1], inpBuf) == RVAL_ERR) abortem("Reading file");


    nodes_t nodes;
    countChars(inpBuf, nodes);

    HuffmanCode<char> huffman(nodes);
    HuffmanCode<char>::Table* table = huffman.getTable();
    //huffman.inspect();
    inspectTable(*table);

    //for(HuffmanCode<char>::Table::iterator it = table->begin(); it != table->end(); ++it)
        //std::cout << it->first << ": " << it->second << std::endl;

    return EXIT_SUCCESS;
}


int readInpFile(const char *& fname, std::string& buffer)
{
    std::ifstream file(fname);
    if(!file.is_open() || file.eof()) return RVAL_ERR;
    buffer.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    return 0;
}


void countChars(std::string& buf, nodes_t& nodesList)
{
    chCountMap_t countersMap;

    std::string::iterator strLim = buf.end();
    for(strIter_t it = buf.begin(); it != strLim; ++it) countersMap[*it] ++;

    chCountMapIt_t mapLim = countersMap.end();
    for(chCountMapIt_t c = countersMap.begin(); c != mapLim; ++c) {
        node_t* node = new node_t;
        node->dat = (*c).first;
        node->key = (*c).second;
        nodesList.push_back(node);
    }
}

void displayNodes(nodes_t& list)
{
    for(nodesIt_t it = list.begin(); it != list.end(); ++it)
        std::cout << '\'' << (*it)->dat << '\'' << ": " << (*it)->key << std::endl;
}

