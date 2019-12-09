#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "moves.h"


position convertirlocation(char positionstr[]) {
    int param1,param2,param3; // Param1Param2 for example : A2
    // or Param1Param2Param3 for example : H23 or GV3
    position location;
    location.position_relative_to_carre='0';
    if (strlen(positionstr)==2) {
        param1 = positionstr[0];
        param2= positionstr[1];
        location.line = param1-'A';
        location.column = param2-'1';
    }
    else {
        param1 = positionstr[0];
        param2 = positionstr[1];
        param3 = positionstr[2];
        if (param1=='H') {
            if (param2!= '8' ) {
                    location.line = param2 - '1';
                    location.column = param3 - '1';
                    location.position_relative_to_carre = UP;
            }
            else {
                location.line = 6;
                location.column = param3 -'1';
                location.position_relative_to_carre = DOWN;
            }
        }
        else {
            location.line = param1 - 'A';
            if (param3!='8') {
                location.column = param3 - '1';
                location.position_relative_to_carre= LEFT;
            }
            else {
                location.column = 6;
                location.position_relative_to_carre = RIGHT;
            }
        }
    }
    return location;
}


int isdefaultmove(movement moves,piece playedpiece,carre **A) {
    if (playedpiece.type == ROI) {
        if ((fabs(moves.finalmove.line - moves.initialmove.line) == 1 && moves.finalmove.column == moves.initialmove.column)
            || 
            (fabs(moves.finalmove.column - moves.initialmove.column == 1) && moves.finalmove.line == moves.initialmove.line)
            ) {
            int i=moves.finalmove.line,j=moves.finalmove.column;
            if (   (A[i+1][j].roi == ROI && A[i+1][j].roi->color != playedpiece.color) 
                || (A[i][j+1].roi == ROI && A[i][j+1].roi->color != playedpiece.color) 
                || (A[i][j-1].roi == ROI && A[i][j-1].roi->color != playedpiece.color)
                || (A[i-1][j].roi == ROI && A[i-1][j].roi->color != playedpiece.color)){
                    return 0;
                }
            else {
                    return 1;
                }
        }
        else {
            return 0;
        } 
    }
}

