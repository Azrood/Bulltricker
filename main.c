#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "moves.h"



int main(){

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
return 0;
}
