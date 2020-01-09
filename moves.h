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

int isOptionalCapture(piece **,movement,piece); // vérifie si le mouvement est une capture. 1 si vrai, 0 sinon.
int isDefaultMove(piece ,movement); // si le mouvement est par default possible ou non.
int checkPiece(movement,piece **); // verifie s'il y a une piece qui bloque le mouvement ou pas. 1 si pas de piece, 0 si piece.
int checkKing(movement, piece, piece **); //return 1 if no king qui limite le mouvement, 0 if king
int isLegalMove(piece **, movement, piece); // verifie si le mouvement est possible sur le plateau de jeu.
void MoveKing(piece **,movement, piece); // fonction pour faire bouger le roi
void MovePion(piece **, movement, piece); // fonction pour faire bouger le pion
#endif
