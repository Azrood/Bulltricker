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
/*while (1){
    affichage(A);
    printf("\n");
    movement moves;
    position pos;
    char positionstr[10];
    printf("initiale ");
    gets(positionstr);
    moves.initialmove = ConvertirLocation(positionstr);
    printf("finale ");
    gets(positionstr);
    moves.finalmove = ConvertirLocation(positionstr);
    makemove(A,moves);

}*/
return 0;
}
