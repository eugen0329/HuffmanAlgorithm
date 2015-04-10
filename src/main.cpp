#include <iostream>
#include <cstdlib> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <fstream>
#include <streambuf>

#include <string>

#include "helpers.h"
#include "Huffman.hpp"

int readInpFile(const char *& fname, std::string& buffer);

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

