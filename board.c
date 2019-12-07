#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void initiale(carre **A){
    int i,j;
    for(i=0;i<DIM_PLAT;i++){
        for(j=0;j<DIM_PLAT;j++){
            A[i][j].up->type=NULL;       A[i][j].up->color=NULL;
            A[i][j].down->type=NULL;     A[i][j].down->color=NULL;
            A[i][j].left->type=NULL;     A[i][j].left->color=NULL;
            A[i][j].right->type=NULL;    A[i][j].right->color=NULL;
            A[i][j].roi->type=NULL;      A[i][j].roi->color=NULL;
            if(i==0){
                A[i][j].down->type=PION;        A[i][j].down->color=BLANCHE;
                A[i][j].left->type=DAME;        A[i][j].left->color=BLANCHE;
                A[i][j].right->type=DAME;       A[i][j].right->color=BLANCHE;
                if(j==3){
                    A[i][j].roi->type=ROI;      A[i][j].roi->color=BLANCHE;
                }
            }
            if(i==1){
                A[i][j].up->type=PION;       A[i][j].up->color=BLANCHE;
                A[i][j].left->type=PION;     A[i][j].left->color=BLANCHE;
                A[i][j].right->type=PION;    A[i][j].right->color=BLANCHE;
            }
            if(i==5){
                A[i][j].down->type=PION;     A[i][j].down->color=NOIRE;
                A[i][j].left->type=PION;     A[i][j].left->color=NOIRE;
                A[i][j].right->type=PION;    A[i][j].right->color=NOIRE;
                if(j==3){
                    A[i][j].roi->type=ROI;      A[i][j].roi->color=BLANCHE;
                }
            }
            if(i==6){
                A[i][j].up->type=PION;           A[i][j].up->color=NOIRE;
                A[i][j].left->type=DAME;         A[i][j].left->color=NOIRE;
                A[i][j].right->type=DAME;        A[i][j].right->color=NOIRE;
            }

        }
    }
}
void affichage(carre **A){
    int i,j;
    for(i=0;i<DIM_PLAT;i++){
        for(j=0;j<DIM_PLAT;j++){
            printf("  %c  ",A[i][j].up->type);
        }printf("\n");
        for(j=0;j<DIM_PLAT;j++){
            printf("%c ",A[i][j].left->type);
            printf("%d ",A[i][j].roi->type);
            printf("%c",A[i][j].right->type);

        }printf("\n");
        for(j=0;j<DIM_PLAT;j++){
            printf("  %c  ",A[i][j].down->type);
        }printf("\n");
    }
}

