#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "moves.h"


position convertirlocation(char positionstr[]) {
    //convertis la position string "A2" ou "GV2" en position int i,j
    int param1,param2,param3;
    position location;
    if (strlen(positionstr)==2) { //cases royales
        param1 = positionstr[0];
        param2= positionstr[1];
        location.line = 2*(param1-'A')+1;
        location.column = 2*(param2-'1')+1;
    }
    else { //des cases rectangulaires
        param1 = positionstr[0];
        param2 = positionstr[1];
        param3 = positionstr[2];
        if (param1=='H') {
                    location.line = 2*(param2 - '1');
                    location.column = 2*(param3 - '1')+1;
        }
        else {
            location.line = 2*(param1 - 'A')+1;
            location.column = 2*(param3 - '1');
        }
    }
    return location;
}

int isvalidemove(piece **A,piece playedpiece,movement moves){
   int i=moves.finalmove.line,j=moves.finalmove.column;
   if (A[moves.initialmove.line][moves.initialmove.column].type == playedpiece.type && A[moves.initialmove.line][moves.initialmove.column].color == playedpiece.color) {
       if  (playedpiece.type == ROI) { //check if moves in a + pattern.
        if ((( (fabs(moves.initialmove.line - moves.finalmove.line)==2 && moves.initialmove.column == moves.finalmove.column) 
        || (fabs(moves.initialmove.column - moves.finalmove.column)==2) && moves.initialmove.line == moves.finalmove.line ) )
        &&  //check si ROI de couleur opposée est présent dans l'entourage de la position finale et ignore le ROI de la couleur jouée.
            ((A[i+2][j].type!=ROI || A[i+2][j].color == playedpiece.color)
            && (A[i-2][j].type!=ROI || A[i-2][j].color == playedpiece.color)
            && (A[i][j+2].type!=ROI || A[i][j+2].color == playedpiece.color)
            && (A[i][j-2].type!=ROI || A[i][j-2].color == playedpiece.color))
        ){
            return 1;
        }    
       }
    }
    else return 0;
    }
}