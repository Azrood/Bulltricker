#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
#define SIZE_TAB 30

#include "moves.h"
#include "graphic.h"

int inTab(position *, position); // 1 si la position entrée est présente dans le tableau. 0 sinon.
int isEmpty(position *); // 1 s'il n'y a aucune piece dans le tableau qui peuvent capturer. 0 sinon
void FlushTab(position**); // vide le tableau en remplaçant les positions par ligne = 42, colonne =42, les dames sont placées en 1er.
void RemplirTab(piece **,int,position **); // remplit le tableau avec les pieces(en utilisant les positions) qui ont une capture obligatoire
void RemplirPoint(Point **); //remplit le tableau avec les intervalles de pixels qui correspondent aux cases du plateau de jeu
char * SavoirLocationX(int ); //convertit la position pixel en position "A4, AV1" pour les x
char * SavoirLocationY(int ); // même chose pour les y
void InitialiseTableauTexture(SDL_Texture **,SDL_Renderer *); // initialise le tableau F avec les textures des pièces

#endif