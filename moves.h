#ifndef MOVES_H_INCLUDED
#define MOVES_H_INCLUDED
#include "board.h"

#define UP 'u'
#define DOWN 'd'
#define LEFT 'l'
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

int islegalmove(move,piece ,carre **);
position convertirlocation(char *);
carre getpiece(carre **,position,piece);

#endif