#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void initialplateau(piece **A){
    int i,j;
    for(i=0;i<DIM_PLAT;i++){
        for(j=0;j<DIM_PLAT;j++){
            A[i][j].type=VIDE;       A[i][j].color=VIDE;
            if (i%2 ==0 && j%2 == 0) {
                A[i][j].type = INTERDIT;
                A[i][j].color = INTERDIT;
            }

            if (i==1) { 
                if (j==7) {
                    A[i][j].type = ROI; A[i][j].color=NOIRE;
                }
                else if ( j%2==0) {
                        A[i][j].type = DAME;    A[i][j].color=NOIRE;
                    }
            }
            if ((i==2 && j%2==1) || (i==3 && j%2==0) ) {
                A[i][j].type = PION;    A[i][j].color=NOIRE;
            }
            if ((i==11 && j%2==0) || (i==12 && j%2==1)) {
                A[i][j].type = PION;    A[i][j].color=BLANCHE;
            }

            if (i==13) {
                if (j==7) {
                A[i][j].type = ROI;    A[i][j].color=BLANCHE;
                }
                else if (j%2==0) {
                    A[i][j].type = DAME;    A[i][j].color=BLANCHE;
                }
            }
        }
    }
}

void affichage(piece **A) {
    int i,j;
    for (i=0;i<DIM_PLAT;i++){
        for (j=0;j<DIM_PLAT;j++){
            printf("  |%c/%c|  ",A[i][j].type,A[i][j].color);
        }printf("\n");
    }
}
                