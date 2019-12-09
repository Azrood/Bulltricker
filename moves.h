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

typedef struct moves {
    position initialmove;
    position finalmove;
}movement;

int islegalmove(movement,piece ,carre **);
position convertirlocation(char *);

#endif