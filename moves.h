#ifndef MOVES_H_INCLUDED
#define MOVES_H_INCLUDED

#include <SDL.h>
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

int CompulsoryCapture(piece **,position *,movement); // retourne 1 si la piece à capturer est dans la liste des pieces qui peuvent capturer, 0 sinon.
// elle sert à vérifier que si on a des pieces qui peuvent capturer, la piece jouée en fait partie

int AbleToEat(piece **,position); //verifie si la piece dans une position donnée peut capturer (1) ou non (0)

void MoveKing(piece **,movement, piece); // fonction pour faire bouger le roi
void MovePion(piece **, movement, piece, position *); // fonction pour faire bouger le pion
void MoveDame(piece **, movement, piece, position *); // fonction pour faire bouger le dame
void play(piece **,position *,movement *,piece *,SDL_MouseButtonEvent, int *,int);//fonction pour jouer le tour.
#endif
