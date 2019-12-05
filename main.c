#include "board.h"
#include<stdio.h>
#include<stdlib.h>

int main(){

int i,j;
carre **A=(carre **)malloc(N*sizeof(carre *));
for(i=0;i<N;i++){
    A[i]=(carre *)malloc(N*sizeof(carre));
}
for (i=0;i<N;i++){
    for(j=0;j<N;j++){
        A[i][j].down=(piece *)malloc(sizeof(piece));
        A[i][j].up=(piece *)malloc(sizeof(piece));
        A[i][j].left=(piece *)malloc(sizeof(piece));
        A[i][j].right=(piece *)malloc(sizeof(piece));
        A[i][j].roi=(piece *)malloc(sizeof(piece));
    }
}
initiale(A);
affichage(A);
return 0;
}
