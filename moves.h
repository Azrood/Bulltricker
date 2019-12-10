#ifndef MOVES_H_INCLUDED
#define MOVES_H_INCLUDED
#include "board.h"


typedef struct position {
    int line;
    int column;
}position;

typedef struct moves {
    position initialmove;
    position finalmove;
}movement;

position ConvertirLocation(char *);
int isDefaultMove(piece ,movement);

#endif
