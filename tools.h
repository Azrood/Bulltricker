#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
#define SIZE_TAB 30
#include "moves.h"

int inTab(position *, position); // renvoie 1 si la position entrée est présente dans le tableau. 0 sinon.
void FlushTab(position**); // vide le tableau en remplaçant les positions par ligne = 42, colonne =42, les dames sont placées en 1er.
void RemplirTab(piece **,int,position **); // remplit le tableau avec les pieces(en utilisant les positions) qui ont une capture obligatoire
#endif