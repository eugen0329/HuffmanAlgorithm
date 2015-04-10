#ifndef HELPERS_H_VHESKYND
#define HELPERS_H_VHESKYND

#include <cstdio>

#ifndef RVAL_ERR
    #define RVAL_ERR -1
#endif

void abortem(const char * msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}


#endif /* end of include guard: HELPERS_H_VHESKYND */
