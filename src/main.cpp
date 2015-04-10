#include <iostream>
#include <cstdlib> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <fstream>
#include <streambuf>

#include <string>
#include <list>
#include <map>

#include "helpers.h"
#include "Huffman.hpp"

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

void inspectTable(table_t& list);


int main(int argc, const char *argv[])
{
    if(argc != 2) {
        std::cout << "ERROR: Wrong cmdline arguments list" << std::endl;
        return EXIT_FAILURE;
    }
    std::string buf;
    if(readInpFile(argv[1], buf) == RVAL_ERR) abortem("Reading file");

    HuffmanCode<char> huffman(buf);
    huffman.inspectTable();

    return EXIT_SUCCESS;
}


int readInpFile(const char *& fname, std::string& buffer)
{
    std::ifstream file(fname);
    if(!file.is_open() || file.eof()) return RVAL_ERR;
    buffer.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    return 0;
}

