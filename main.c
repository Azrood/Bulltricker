#include <stdio.h>
#include <stdlib.h>
#include "moves.h"



int main()
{

int i,j;
piece **A=(piece **)malloc(DIM_PLAT*sizeof(piece *));
for(i=0;i<DIM_PLAT;i++){
    A[i]=(piece *)malloc(DIM_PLAT*sizeof(piece));
}

initialplateau(A);
affichage(A);
printf("\n");
int k=0;
while (1){
    affichage(A);
    printf("\n");
    movement moves;
    position pos;
    piece playedpiece;
    playedpiece.firstmove = 0;
    playedpiece.type = PION;
    if (k%2==0) {
    playedpiece.color = BLANCHE;
    k=1;
    }
    else {
        playedpiece.color = NOIRE; 
        k=0;}
    char positionstr[10];
    printf("initiale ");
    gets(positionstr);
    moves.initialmove = ConvertirLocation(positionstr);
    printf("finale ");
    gets(positionstr);
    moves.finalmove = ConvertirLocation(positionstr);
    MovePion(A,moves,playedpiece);

}
return 0;
}
