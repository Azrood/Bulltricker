#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "moves.h"
#include "tools.h"
#include "graphic.h"

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

void RemplirPoint(Point **P)
{
    P[1][0].x = 47;
    P[1][0].y = 67;
    for(int j=2 ; j<15 ; j+=2)
    {
            P[1][j].x =  P[1][j-2].x + 77;
            P[1][j].y = 67;
    }
    for(int i=3 ; i<15 ; i+=2)//chargement des coordonnées des piece verticales
    {
        P[i][0].x = 47;
        P[i][0].y = P[i-2][0].y + 77;
        for(int j=2 ; j<15 ; j+=2)
        {
            P[i][j].x = P[i][j-2].x + 77;
            P[i][j].y = P[i][0].y;
        }

    }

    P[0][1].x = 67;
    P[0][1].y = 47;
    for(int j=3 ; j<15 ; j+=2)
    {
            P[0][j].x =  P[0][j-2].x + 77;
            P[0][j].y = 47;
    }
    for(int i=2 ; i<15 ; i+=2)//chargement des coordonnées  des piece Horizontale
    {
        P[i][1].x = 67;
        P[i][1].y = P[i-2][1].y + 77;
        for(int j=3 ; j<15 ; j+=2)
        {
            P[i][j].x = P[i][j-2].x + 77;
            P[i][j].y = P[i][1].y;
        }
    }
    P[1][1].x = 77;
    P[1][1].y = 77;
    for(int j=3 ; j<15 ; j+=2)
    {
            P[1][j].x =  P[1][j-2].x + 77;
            P[1][j].y = 77;
    }
    for(int i=3 ; i<15 ; i+=2)//chargement des coordonnées  des cases royales
    {
        P[i][1].x = 77;
        P[i][1].y = P[i-2][1].y + 77;
        for(int j=3 ; j<15 ; j+=2)
        {
            P[i][j].x = P[i][j-2].x + 77;
            P[i][j].y = P[i][1].y;
        }
    }
}

char * SavoirLocationX(int x)
{
    char *pos=(char *)malloc(2);

    if(x <= 604 && x >= 46)
    {
        if (x <= 64 && x >= 46)   strcpy(pos,"V1");
        if (x <= 121 && x >= 64)  strcpy(pos,"1");
        if (x <= 159 && x >= 123) strcpy(pos,"V2");
        if (x <= 198 && x >= 141) strcpy(pos,"2");
        if (x <= 218 && x >= 200) strcpy(pos,"V3");
        if (x <= 275 && x >= 218) strcpy(pos,"3");
        if (x <= 295 && x >= 277) strcpy(pos,"V4");
        if (x <= 352 && x >= 295) strcpy(pos,"4");
        if (x <= 372 && x >= 354) strcpy(pos,"V5");
        if (x <= 429 && x >= 372) strcpy(pos,"5");
        if (x <= 449 && x >= 431) strcpy(pos,"V6");
        if (x <= 506 && x >= 449) strcpy(pos,"6");
        if (x <= 526 && x >= 508) strcpy(pos,"V7");
        if (x <= 583 && x >= 526) strcpy(pos,"7");
        if (x <= 603 && x >= 585) strcpy(pos,"V8");
    }
    return pos;
}

char * SavoirLocationY(int y)
{
    char *pos = (char *)malloc(2);
    if(y <= 604 && y>= 46)
    {
        if(y <= 67 && y >= 46) strcpy(pos,"H1");
        if(y <= 114 && y >= 78) strcpy(pos,"A");
        if(y <= 143 && y >= 123) strcpy(pos,"H2");
        if(y <= 191 && y >= 155) strcpy(pos,"B");
        if(y <= 220 && y >= 200) strcpy(pos,"H3");
        if(y <= 268 && y >= 232) strcpy(pos,"C");
        if(y <= 297 && y >= 277) strcpy(pos,"H4");
        if(y <= 345 && y >= 309) strcpy(pos,"D");
        if(y <= 374 && y >= 354) strcpy(pos,"H5");
        if(y <= 422 && y >= 386) strcpy(pos,"E");
        if(y <= 451 && y >= 431) strcpy(pos,"H6");
        if(y <= 499 && y >= 463) strcpy(pos,"F");
        if(y <= 528 && y >= 508) strcpy(pos,"H7");
        if(y <= 576 && y >= 540) strcpy(pos,"G");
        if(y <= 604 && y >= 585) strcpy(pos,"H8");

    }
    return pos;
}

void InitialiseTableauTexture(SDL_Texture **F,SDL_Renderer *render)
{
    F[ind_DAMEBH]=CreateTexture(DAMEBH,render);
    F[ind_DAMENH]=CreateTexture(DAMENH,render);
    F[ind_DAMENV]=CreateTexture(DAMENV,render);
    F[ind_PIONNV]=CreateTexture(PIONNV,render);
    F[ind_PIONNV]=CreateTexture(PIONNV,render);
    F[ind_PIONNH]=CreateTexture(PIONNH,render);
    F[ind_DAMEBV]=CreateTexture(DAMEBV,render);
    F[ind_PIONBV]=CreateTexture(PIONBV,render);
    F[ind_PIONBH]=CreateTexture(PIONBH,render);
    F[ind_ROIB]=CreateTexture(ROIB,render);
    F[ind_ROIN]=CreateTexture(ROIN,render);
}
