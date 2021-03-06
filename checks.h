#ifndef CHECKS_H_INCLUDED
#define CHECKS_H_INCLUDED

#include "moves.h"

int checkPiece(movement,piece **); // verifie s'il y a une piece qui bloque le mouvement ou pas. 1 si pas de piece, 0 si piece.
int checkKing(movement, piece, piece **); // 1 si pas de roi ne limite le mouvement, 0 si le roi adverse limite le mouvement

int isDefaultMove(piece ,movement); // si le mouvement est par default possible ou non.
int isLegalMove(piece **, movement, piece); // verifie si le mouvement est possible sur le plateau de jeu.

int isOptionalCapture(piece **,movement,piece); // vérifie si le mouvement est une capture. 1 si vrai, 0 sinon.
int isEatingMove(piece **,movement, piece); //verifie si le mouvement est un mouvement de capture ou non.
int AbleToEat(piece **,position); //verifie si la piece dans une position donnée peut capturer (1) ou non (0)

int CheckMat(piece **,int *); // tester la fin de partie 0 oui / 1 non
#endif
