#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void initiale(carre **A){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            A[i][j].up=NULL;
            A[i][j].down=NULL;
            A[i][j].left=NULL;
            A[i][j].right=NULL;
            A[i][j].roi=0;
            if(i==0){
                // A[i][j].up=NULL;
                A[i][j].down=PION;
                A[i][j].left=DAME;
                A[i][j].right=DAME;
                A[i][j].roi=0;
                if(j==3) A[i][j].roi=1;
            }
            if(i==1){
                A[i][j].up=PION;
                // A[i][j].down=NULL;
                A[i][j].left=PION;
                A[i][j].right=PION;
                A[i][j].roi=0;
            }
            if(i==5){
                // A[i][j].up=NULL;
                A[i][j].down=PION;
                A[i][j].left=PION;
                A[i][j].right=PION;
                A[i][j].roi=0;
            }
            if(i==6){
                A[i][j].up=PION;
                // A[i][j].down=NULL;
                A[i][j].left=DAME;
                A[i][j].right=DAME;
                A[i][j].roi=0;
                if(j==3) A[i][j].roi=1;
            }

        }
    }
}
void affichage(carre **A){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("  %c  ",A[i][j].up);
        }printf("\n");
        for(j=0;j<N;j++){
            printf("%c ",A[i][j].left);
            printf("%d ",A[i][j].roi);
            printf("%c",A[i][j].right);

        }printf("\n");
        for(j=0;j<N;j++){
            printf("  %c  ",A[i][j].down);
        }printf("\n");
    }
}

