#ifndef MOVES_H_INCLUDED
#define MOVES_H_INCLUDED
#include "board.h"

#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'r'

typedef struct position {
    char position_relative_to_carre;
    int line;
    int column;
}position;

typedef struct move {
    position initial;
    position final;
}move;

int islegalmove(move,piece *,carre **);
position convertirlocation(char *);

#endif