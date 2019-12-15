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
for (i=0;i<DIM_PLAT;i++){
    for(j=0;j<DIM_PLAT;j++){
        A[i][j].type=(int *)malloc(sizeof(int));
        A[i][j].color=(int *)malloc(sizeof(int));
    }
}

initialplateau(A);
affichage(A);
int k=0;
/*while (1){
    affichage(A);
    printf("\n");
    movement moves;
    position pos;
    piece playedpiece;
    playedpiece.firstmove = 1;
    playedpiece.type = PION;
    if (k%2) {
    playedpiece.color = BLANCHE;
    k=0;
    }
    else {
        playedpiece.color = NOIRE; 
        k=1;}
    char positionstr[10];
    printf("initiale ");
    gets(positionstr);
    moves.initialmove = ConvertirLocation(positionstr);
    printf("finale ");
    gets(positionstr);
    moves.finalmove = ConvertirLocation(positionstr);
    if (isDefaultMove(playedpiece,moves))
    {
        printf("YES \n \n \n");
    }
    else printf("NOOOOOO \n \n \n");
    MoveKing(A,moves,playedpiece);

}*/
return 0;
}
