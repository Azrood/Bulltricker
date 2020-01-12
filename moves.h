#ifndef MOVES_H_INCLUDED
#define MOVES_H_INCLUDED
#include "board.h"


typedef struct position {
    int line;
    int column;
}position;

typedef struct movement{
    position initialmove;
    position finalmove;
}movement;

position ConvertirLocation(char *); // à enlever (maybe) après SDL

int CompulsoryCapture(piece **,position **,piece); // TO DO
int AbleToEat(piece **,position); //verifie si la piece dans une position donnée peut capturer (1) ou non (0)

void MoveKing(piece **,movement, piece); // fonction pour faire bouger le roi
void MovePion(piece **, movement, piece); // fonction pour faire bouger le pion
void MoveDame(piece **, movement, piece); // fonction pour faire bouger le dame
#endif
