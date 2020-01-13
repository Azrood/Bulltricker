#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "moves.h"
#include "tools.h"

int isEmpty(position *Tab)
{
    if (Tab[0].line != 42) return 0; // si le 1er element n'est pas invalide, alors le tableau n'est pas 'vide'.
    return 1;
}


int inTab(position *Tab, position pos)
{
    for(int i=0;i<SIZE_TAB;i++)
    {
        if (pos.line == Tab[i].line && pos.column == Tab[i].column) return 1;
        // la position entrée est dans la tableau, donc la piece
        // donc la pièce jouée est une pièce avec une prise obligatoire

    }
    return 0; // la piece jouée n'est pas une pièce à prise obligatoire
}

void FlushTab(position **Tab)
{
    for (int i=0;i<SIZE_TAB;i++)
    {
        (*Tab)[i].line = 42;
        (*Tab)[i].column = 42;
    }
}

void RemplirTab(piece **A,int couleur,position **Tab)
{
    int k=0;
    position pos;
    for (int i=0;i<DIM_PLAT;i++)
    {
        for (int j=0;j<DIM_PLAT;j++)
        {
            if ((j%2 == 1 && i%2==1) || A[i][j].type == INTERDIT)
            {
                continue;
            }
            pos.line = i;
            pos.column = j;
            if (A[i][j].color == couleur && AbleToEat(A,pos)==1)
            {
                if (A[i][j].type == DAME) //on insère la dame au début du tableau, pour respecter la règle de priorité.
                {
                    for (int b=k;b>0;b--) // on commence à partir du dernier indice valide
                    {
                        (*Tab)[b]=(*Tab)[b-1];
                    } // on décale les éléments
                    (*Tab)[0]=pos; //on insère la position de la dame au début.
                }
                else
                { //on insère normalement
                    (*Tab)[k].line = i;
                    (*Tab)[k].column = j;
                    k++;
                }
            }
        }
    }
}
