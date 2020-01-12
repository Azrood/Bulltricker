#include <stdio.h>
#include <stdlib.h>
#include "moves.h"
#include "checks.h"



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
    printf("\n");
    movement moves;
    piece playedpiece;
    playedpiece.firstmove = 0;
    int p;
    if (k%2==0)
    {
        printf("au tour des blancs\n");
        playedpiece.color = BLANCHE;
        k=1;
    }
    else {
        printf("au tour des noirs \n");
        playedpiece.color = NOIRE;
        k=0;}
    fflush(stdin);
    char positionstr[10];
    printf("initiale ");
    gets(positionstr);
    moves.initialmove = ConvertirLocation(positionstr);
    playedpiece.type=A[moves.initialmove.line][moves.initialmove.column].type;
    playedpiece.firstmove=A[moves.initialmove.line][moves.initialmove.column].firstmove;
    printf("finale ");
    gets(positionstr);
    moves.finalmove = ConvertirLocation(positionstr);
    if(playedpiece.type == PION) MovePion(A,moves,playedpiece);
    if(playedpiece.type == DAME) MoveDame(A,moves,playedpiece);
    if(playedpiece.type == ROI) MoveKing(A,moves,playedpiece);
    affichage(A);
}
return 0;
}
