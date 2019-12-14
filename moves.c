#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "moves.h"


position ConvertirLocation(char positionstr[]) 
{ // Cette fonction marche correctement.
/* Elle retourne une structure Position avec les attributs line et colonne)*/
    //convertis la position string "A2" ou "GV2" en position int i,j
    int param1,param2,param3;
    position location;
    if (strlen(positionstr)==2) 
    { //cases royales
        param1 = positionstr[0];
        param2 = positionstr[1];
        location.line = 2*(param1-'A')+1;
        location.column = 2*(param2-'1')+1;
    }
    else 
    { //des cases rectangulaires
        param1 = positionstr[0];
        param2 = positionstr[1];
        param3 = positionstr[2];
        if (param1=='H') 
        {
                    location.line = 2*(param2 - '1');
                    location.column = 2*(param3 - '1')+1;
        }
        else 
        {
            location.line = 2*(param1 - 'A')+1;
            location.column = 2*(param3 - '1');
        }
    }
    return location;
}

int checkPiece(movement moves,piece ** A)
{
    int movedline = moves.finalmove.line - moves.initialmove.line;
    int movedcol = moves.finalmove.column - moves.initialmove.column;
    int i=moves.initialmove.line,j=moves.initialmove.column;
    if (movedline == 0)
    {
        if (movedcol < 0)
        {
            if (A[i][j-1].type == VIDE) return 1;
            else return 0;
        }
        else if (movedcol > 0) {

            if (A[i][j+1].type == VIDE) return 1;
            else return 0;
        }
    }
    else if (movedcol == 0)
    {
        if (movedline < 0)
        {
            if(A[i-1][j].type == VIDE) return 1;
            else return 0;
        }
        if (movedline > 0)
        {
            if(A[i+1][j].type == VIDE) return 1;
            else return 0;
        }
    }
    else return 0;
}

int checkKing(movement moves,piece playedpiece,piece **A)
{
    int i=moves.finalmove.line,j=moves.finalmove.column;
    if ((i>1 && i<13) && (j>1 && j<13)) 
        {
            if ((A[i][j+2].type != ROI || A[i][j+2].color == playedpiece.color)
                && (A[i][j-2].type != ROI || A[i][j-2].color == playedpiece.color)
                && (A[i+2][j].type != ROI || A[i+2][j].color == playedpiece.color)
                && (A[i-2][j].type != ROI || A[i-2][j].color == playedpiece.color)
                && (A[i-2][j+2].type != ROI || A[i-2][j+2].color == playedpiece.color)
                && (A[i-2][j-2].type != ROI || A[i-2][j-2].color == playedpiece.color)
                && (A[i+2][j+2].type != ROI || A[i+2][j+2].color == playedpiece.color)
                && (A[i+2][j-2].type != ROI || A[i+2][j-2].color == playedpiece.color)) 
                {
                    return 1;
                }
            else return 0;

        }
    else if (i==1)
        {
            if (j==13) 
            {
                if ((A[i][j-2].type != ROI || A[i][j-2].color == playedpiece.color)
                    && (A[i+2][j].type != ROI || A[i+2][j].color == playedpiece.color)
                    && (A[i+2][j-2].type != ROI || A[i][j-2].color == playedpiece.color))
                {
                    return 1;
                }
                else return 0;
            }
            else if (j==1) 
            {
                if ((A[i][j+2].type != ROI || A[i][j+2].color == playedpiece.color)
                    && (A[i+2][j].type != ROI || A[i+2][j].color == playedpiece.color)
                    && (A[i+2][j+2].type != ROI || A[i+2][j+2].color == playedpiece.color))
                    {
                        return 1;
                    }
                else return 0;
            }
            else 
            {
                if ((A[i][j+2].type != ROI || A[i][j+2].color == playedpiece.color)
                    && (A[i][j-2].type != ROI || A[i][j-2].color == playedpiece.color)
                    && (A[i+2][j].type != ROI || A[i+2][j].color == playedpiece.color)
                    && (A[i+2][j+2].type != ROI || A[i+2][j+2].color == playedpiece.color)
                    && (A[i+2][j-2].type != ROI || A[i+2][j-2].color == playedpiece.color)) 
                    {
                        return 1;
                    }
                else return 0;
            }
        }
    else if(i==13 )
    { 
        if (j==1) 
        {
            if ((A[i-2][j].type != ROI || A[i-2][j].color == playedpiece.color)
                &&(A[i][j+2].type != ROI || A[i][j+2].color == playedpiece.color)
                && (A[i-2][j+2].type != ROI || A[i-2][j+2].color == playedpiece.color)  )
            {
                return 1;
            }
            else return 0;
        }
        else if (j==13)
        {
            if ((A[i-2][j].type != ROI || A[i-2][j].color == playedpiece.color)
                && (A[i][j-2].type != ROI || A[i][j-2].color == playedpiece.color)
                && (A[i-2][j-2].type != ROI || A[i-2][j-2].color == playedpiece.color))
                {
                    return 1;
                }
            else return 0;
        }
        else 
        {
            if ((A[i][j+2].type != ROI || A[i][j+2].color == playedpiece.color)
                && (A[i][j-2].type != ROI || A[i][j-2].color == playedpiece.color)
                && (A[i-2][j].type != ROI || A[i-2][j].color == playedpiece.color)
                && (A[i-2][j+2].type != ROI || A[i-2][j+2].color == playedpiece.color)
                && (A[i-2][j-2].type != ROI || A[i-2][j-2].color == playedpiece.color))
                {
                    return 1;
                }
            else return 0;
        }
    }
    else if (j==1){
        if (i==1)
        {
            if ((A[i][j+2].type != ROI || A[i][j+2].color == playedpiece.color)
                && (A[i+2][j].type != ROI || A[i+2][j].color == playedpiece.color)
                && (A[i+2][j+2].type != ROI || A[i+2][j+2].color == playedpiece.color))
                {
                    return 1;
                }
            else return 0;
        }
        else if (i==13)
        {
            if ((A[i][j+2].type != ROI || A[i][j+2].color == playedpiece.color)
                && (A[i-2][j].type != ROI || A[i-2][j].color == playedpiece.color)
                && (A[i-2][j+2].type != ROI || A[i-2][j+2].color == playedpiece.color))
            {
                return 1;
            }
            else return 0;
        }
        else 
        {
            if ((A[i][j+2].type != ROI || A[i][j+2].color == playedpiece.color)
                && (A[i+2][j].type != ROI || A[i+2][j].color == playedpiece.color)
                && (A[i-2][j].type != ROI || A[i-2][j].color == playedpiece.color)
                && (A[i-2][j+2].type != ROI || A[i-2][j+2].color == playedpiece.color)
                && (A[i+2][j+2].type != ROI || A[i+2][j+2].color == playedpiece.color))
                {
                    return 1;
                }
            else return 0;
        }
    }
    else if (j==13)
    {
        if (i==1)
        {
            if ((A[i][j-2].type != ROI || A[i][j-2].color == playedpiece.color)
                && (A[i+2][j].type != ROI || A[i+2][j].color == playedpiece.color)
                && (A[i+2][j-2].type != ROI || A[i+2][j-2].color == playedpiece.color))
                {
                    return 1;
                }
            else return 0;
        }
        else if (i==13)
        {
            if ((A[i][j-2].type != ROI || A[i][j-2].color == playedpiece.color)
                && (A[i-2][j].type != ROI || A[i-2][j].color == playedpiece.color)
                && (A[i-2][j-2].type != ROI || A[i-2][j-2].color == playedpiece.color))
            {
                return 1;
            }
            else return 0;
        }
        else 
        {
            if ((A[i][j-2].type != ROI || A[i][j-2].color == playedpiece.color)
                && (A[i+2][j].type != ROI || A[i+2][j].color == playedpiece.color)
                && (A[i-2][j].type != ROI || A[i-2][j].color == playedpiece.color)
                && (A[i-2][j-2].type != ROI || A[i-2][j-2].color == playedpiece.color)
                && (A[i+2][j-2].type != ROI || A[i+2][j-2].color == playedpiece.color))
                {
                    return 1;
                }
            else return 0;
        }
    }
    else return 1;
}

void MoveKing(piece **A,movement moves,piece king)
{

    int i=moves.finalmove.line,j=moves.finalmove.column;
    if ((king.color = A[moves.initialmove.line][moves.initialmove.column].color) 
        &&(king.type = A[moves.initialmove.line][moves.initialmove.column].type) 
        &&(king.firstmove = A[moves.initialmove.line][moves.initialmove.column].firstmove))
    {
        if (isDefaultMove(king,moves) && checkKing(moves,king,A) && checkPiece(moves,A))
        {
            A[i][j].type = A[moves.initialmove.line][moves.initialmove.column].type;
            A[i][j].color = A[moves.initialmove.line][moves.initialmove.column].color;
            A[i][j].firstmove = A[moves.initialmove.line][moves.initialmove.column].firstmove;
            A[moves.initialmove.line][moves.initialmove.column].type = VIDE;
            A[moves.initialmove.line][moves.initialmove.column].color = VIDE;
            A[moves.initialmove.line][moves.initialmove.column].firstmove = VIDE;
        }
    }
}

int isDefaultMove(piece playedpiece,movement moves){
   // vérifie si le mouvement est par défaut possible, sans prendre en compte la présence de pièce de la couleur opposée.
    int i=moves.finalmove.line,j=moves.finalmove.column;
    if  (playedpiece.type == ROI) { //check if moves in a + pattern. (horizontal et vertical seulement)
        if (( (fabs(moves.initialmove.line - moves.finalmove.line)==2 && moves.initialmove.column == moves.finalmove.column) 
            ||(fabs(moves.initialmove.column - moves.finalmove.column)==2 && moves.initialmove.line == moves.finalmove.line ))
        ){
            return 1; //1 : Le mouvement est par défaut possible
        }
        else return 0; //0 : mouvement pas possible.
       }
    /*else if (playedpiece.type == PION){
        if (playedpiece.color == BLANCHE) {

        }
        else if (playedpiece.color == NOIRE) {

        }
    }*/
}  
