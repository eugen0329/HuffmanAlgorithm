#include <iostream>
#include <cstdlib> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <fstream>
#include <streambuf>

#include <string>
#include <list>
#include <map>

#include "helpers.h"
#include "tree.h"

struct CharCounter {
    double count;
    char ch;
};

typedef std::string::iterator strIter_t;
typedef std::map<char, int> chCountMap_t;
typedef std::map<char, int>::iterator chCountMapIt_t;
typedef BTree<CharCounter>::Node treeChCountNode_t;
typedef std::list<treeChCountNode_t*> nodesList_t;
typedef std::list<treeChCountNode_t*>::iterator nodesListIt_t;

int readInpFile(const char *& fname, std::string& buffer);

void displayNodesList(nodesList_t& list);
void countChars(std::string& buf, nodesList_t& nodesList);

int main(int argc, const char *argv[])
{
    if(argc != 2) {
        std::cout << "ERROR: Wrong cmdline arguments list" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inpBuf;
    if(readInpFile(argv[1], inpBuf) == RVAL_ERR) abortem("Reading file");

    nodesList_t chcount;
    countChars(inpBuf, chcount);
    displayNodesList(chcount);


    return EXIT_SUCCESS;
}

void displayNodesList(nodesList_t& list)
{
    for(nodesListIt_t it = list.begin(); it != list.end(); ++it)
        std::cout << '\'' << (int) (*it)->dat.ch << '\'' << ": " << (*it)->dat.count << std::endl;
}


int readInpFile(const char *& fname, std::string& buffer)
{
    std::ifstream file(fname);
    if(!file.is_open() || file.eof()) return RVAL_ERR;
    buffer.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    return 0;
}


void countChars(std::string& buf, nodesList_t& nodesList)
{
    chCountMap_t countersMap;

    std::string::iterator strLim = buf.end();
    for(strIter_t it = buf.begin(); it != strLim; ++it) countersMap[*it] ++;

    chCountMapIt_t mapLim = countersMap.end();
    for(chCountMapIt_t c = countersMap.begin(); c != mapLim; ++c) {
        CharCounter chcount;
        chcount.ch = (*c).first;
        chcount.count = (*c).second;
        treeChCountNode_t* node = new treeChCountNode_t(chcount);
        nodesList.push_back(node);
    }
}

