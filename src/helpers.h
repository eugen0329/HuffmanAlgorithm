#ifndef HELPERS_H_VHESKYND
#define HELPERS_H_VHESKYND

#include <cstdio>
#include <list>

#ifndef RVAL_ERR
    #define RVAL_ERR -1
#endif

void abortem(const char * msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

template<class T> 
T shiftList(std::list<T>& list)
{
    T elem = list.front();
    list.pop_front();
    return elem;
}


#endif /* end of include guard: HELPERS_H_VHESKYND */
