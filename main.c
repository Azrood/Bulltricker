#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"



int main(){

int i,j;
piece **A=(piece **)malloc(DIM_PLAT*sizeof(piece *));
for(i=0;i<DIM_PLAT;i++){
    A[i]=(piece *)malloc(DIM_PLAT*sizeof(piece));
}
for (i=0;i<DIM_PLAT;i++){
    for(j=0;j<DIM_PLAT;j++){
        A[i][j]=(piece *)malloc(sizeof(piece));
    }
}


initialplateau(A);
affichage(A);
return 0;
}
