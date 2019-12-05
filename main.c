#include "board.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

int i,j;
carre **A=(carre **)malloc(N*sizeof(carre *));
for(i=0;i<N;i++){
    A[i]=(carre *)malloc(N*sizeof(carre));
}
initiale(A);
affichage(A);
return 0;
}
