#include <iostream>
#include <cstdlib> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <fstream>
#include <streambuf>

#include <string>
#include <map>

#include "helpers.h"
#include "tree.h"

typedef std::map<char, int> charsCounter_t ;
int readInpFile(const char *& fname, std::string& buffer);

void countChars(std::string& buffer, charsCounter_t& charsCounter);

int main(int argc, const char *argv[])
{
    if(argc != 2) {
        std::cout << "ERROR: Wrong cmdline arguments list" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inpBuf;
    if(readInpFile(argv[1], inpBuf) == RVAL_ERR) abortem("Reading file");

    charsCounter_t chcount;

    countChars(inpBuf, chcount);
    std::cout << "Char a count is " << chcount['a'] << std::endl;

    return EXIT_SUCCESS;
}


int readInpFile(const char *& fname, std::string& buffer)
{
    std::ifstream file(fname);
    if(!file.is_open() || file.eof()) return RVAL_ERR;
    buffer.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    return 0;
}

void countChars(std::string& buffer, charsCounter_t& charsCounter)
{
    std::string::iterator lim = buffer.end();
    for(std::string::iterator it = buffer.begin(); it != lim; ++it) {
        charsCounter[*it] ++;
    }
}

