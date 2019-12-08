#include "board.h"
#include <stdio.h>
#include <stdlib.h>


int main(){

int i,j;
carre **A=(carre **)malloc(DIM_PLAT*sizeof(carre *));
for(i=0;i<DIM_PLAT;i++){
    A[i]=(carre *)malloc(DIM_PLAT*sizeof(carre));
}
for (i=0;i<DIM_PLAT;i++){
    for(j=0;j<DIM_PLAT;j++){
        A[i][j].down=(piece *)malloc(sizeof(piece));
        A[i][j].up=(piece *)malloc(sizeof(piece));
        A[i][j].left=(piece *)malloc(sizeof(piece));
        A[i][j].right=(piece *)malloc(sizeof(piece));
        A[i][j].roi=(piece *)malloc(sizeof(piece));
    }
}


initialplateau(A);
affichage(A);
return 0;
}
