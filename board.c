#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include<string.h>

void initialplateau(piece **A){
    int i,j;
    for(i=0;i<DIM_PLAT;i++){
        for(j=0;j<DIM_PLAT;j++){
            A[i][j].type=VIDE;       A[i][j].color=VIDE;
            A[i][j].firstmove=VIDE;
            if (i%2 ==0 && j%2 == 0) {
                A[i][j].type = INTERDIT;
                A[i][j].color = INTERDIT;
                A[i][j].firstmove = INTERDIT;
            }

            if (i==1) {
                if (j==7) {
                    A[i][j].type = ROI; A[i][j].color=NOIRE;
                    A[i][j].firstmove = VIDE;
                }
                else if ( j%2==0) {
                        A[i][j].type = DAME;    A[i][j].color=NOIRE;
                        A[i][j].firstmove = VIDE;
                    }
            }
            if (i==3 && j%2==0)  {
                A[i][j].type = PION;    A[i][j].color=NOIRE;
                A[i][j].firstmove = VIDE;
            }
            if (i==2 && j%2==1) {
                A[i][j].type = PION;    A[i][j].color=NOIRE;
                A[i][j].firstmove = 1;
            }
            if ((i==11 && j%2==0) ) {
                A[i][j].type = PION;    A[i][j].color=BLANCHE;
                A[i][j].firstmove = VIDE;
            }
            if (i==12 && j%2==1){
                A[i][j].type = PION;    A[i][j].color=BLANCHE;
                A[i][j].firstmove = 1;
            }

            if (i==13) {
                if (j==7) {
                A[i][j].type = ROI;    A[i][j].color=BLANCHE;
                A[i][j].firstmove = VIDE;
                }
                else if (j%2==0) {
                    A[i][j].type = DAME;    A[i][j].color=BLANCHE;
                    A[i][j].firstmove = VIDE;
                }
            }
        }
    }
}

void affichage(piece **A) {
    int i,j,k;
    for (i=0;i<DIM_PLAT;i++){
        if(i%2==1){ /*juste pour grandir la case royale*/
            for(j=0;j<DIM_PLAT;j++){
                if(j==0){
                    if(j%2==0) printf("  |  |");
                    if(j%2==1) printf("        ");
                }else{
                    if(j%2==0) printf("|  |");
                    if(j%2==1) printf("      ");
            }}printf("\n");
        }/*termine ici*/
        /*affichage des cases horizontale*/
        for (j=0;j<DIM_PLAT;j++){
                if(i%2==0){
                    if(j==0){
                        if(j%2==0) printf("H%d|**|",(i+1)/2+1);
                        if(j%2==1) {
                            if(A[i][j].type!=VIDE && A[i][j].color!=VIDE) printf("__%c%c__",A[i][j].type,A[i][j].color);
                            else printf("______");

                    }
                    }
                    else{
                        if(j%2==0) printf("|**|");
                        if(j%2==1) {
                            if(A[i][j].type!=VIDE && A[i][j].color!=VIDE) printf("__%c%c__",A[i][j].type,A[i][j].color);
                            else printf("______");

                    }
                    }

                }
                /*affichage contenu des cases royales et les dames a coté*/
                if(i%2==1){
                    if(j==0){
                        if(j%2==0) printf("%c |%c%c|",(i+65)-(i+1)/2,A[i][j].type,A[i][j].color);
                    }
                    else{
                        if(j%2==0) printf("|%c%c|",A[i][j].type,A[i][j].color);
                        if(j%2==1) printf("  %c%c  ",A[i][j].type,A[i][j].color);
                    }

                }
    }printf("\n");
    /*affichage des cases terminer*/
    if(i%2==1){ /*juste pour grandir la case royale*/
            for(j=0;j<DIM_PLAT;j++){
                if(j==0){
                    if(j%2==0) printf("  |  |");
                    if(j%2==1) printf("  ______");
                }else{
                    if(j%2==0) printf("|  |");
                    if(j%2==1) printf("______");
            }}printf("\n");
        } /*termine ici*/
}
/* Affichage des indices des colonnes*/
for(j=0;j<DIM_PLAT;j++){
    if(j%2==0) printf("   V%d ",(j+1)/2+1);
    if(j%2==1) printf("  %d ",(j+1)/2);
}
}
