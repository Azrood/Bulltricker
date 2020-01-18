#include <stdio.h>
#include <stdlib.h>
#include "moves.h"
#include "checks.h"
#include "tools.h"

int played;

int main()
{

    int i;
    int lost_player=0;
    piece **A=(piece **)malloc(DIM_PLAT*sizeof(piece *));
    for(i=0;i<DIM_PLAT;i++){
        A[i]=(piece *)malloc(DIM_PLAT*sizeof(piece));
    }
    position *Tab;
    Tab = (position *)malloc(SIZE_TAB*sizeof(position));
    initialplateau(A);
    affichage(A);
    printf("\n");
    int k=0;
    while (1)
    {
        printf("\n");
        FlushTab(&Tab);
        while (k%2==0)
        {
            RemplirTab(A,BLANCHE,&Tab);
            printf("\nau tour des blancs\n");
            play(A,Tab,BLANCHE);
            if (played==1)
            {
                played=0;
                k=1;
            }
        }
        affichage(A);
        FlushTab(&Tab);
        if (CheckMat(A,&lost_player)==0) break;
        while(k%2==1)
        {
            RemplirTab(A,NOIRE,&Tab);
            printf("\nau tour des noirs \n");
            play(A,Tab,NOIRE);
            if (played==1)
            {
                played=0;
                k=0;
            }
        }
        affichage(A);
        if (CheckMat(A,&lost_player)==0) break;
    }
    int winner = (lost_player == NOIRE) ? BLANCHE : NOIRE; //on récupère la couleur du joueur
    switch(winner)
    {
        case NOIRE:
            printf("Joueur NOIR gagne !");
            break;
        case BLANCHE:
        printf("Joueur BLANC gagne !");
        break;
    }
    return 0;
}
