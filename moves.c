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



void MoveKing(piece **A,movement moves,piece king)
{

    int i=moves.finalmove.line,j=moves.finalmove.column;
    if ((king.color == A[moves.initialmove.line][moves.initialmove.column].color)
        &&(king.type == A[moves.initialmove.line][moves.initialmove.column].type))
    {
        if (isDefaultMove(king,moves)
            && checkKing(moves,king,A)
            && checkPiece(moves,A)
            /* TODO CompulsoryCapture(parametre)*/)
        {
            A[i][j] = king;
            A[moves.initialmove.line][moves.initialmove.column].type = VIDE;
            A[moves.initialmove.line][moves.initialmove.column].color = VIDE;
            A[moves.initialmove.line][moves.initialmove.column].firstmove = VIDE;
        }
    }
}



void MovePion(piece **A,movement moves, piece playedpiece)
{
    int i=moves.initialmove.line,j=moves.initialmove.column;
    if (A[i][j].type == playedpiece.type && A[i][j].color == playedpiece.color)
    {
        if (isOptionalCapture(A,moves,playedpiece) == 1 || isLegalMove(A, moves, playedpiece) == 1 /* TODO CompulsoryCapture(parametre)*/)
        {
            A[moves.finalmove.line][moves.finalmove.column] = playedpiece;
            A[moves.finalmove.line][moves.finalmove.column].firstmove = 0;
            if (moves.finalmove.line == 0 || moves.finalmove.line == 14)
            {
                A[moves.finalmove.line][moves.finalmove.column].type = DAME;
            }
            A[i][j].color = VIDE;
            A[i][j].type = VIDE;
            A[i][j].firstmove = VIDE;
        }
    }
}

void MoveDame(piece **A,movement moves, piece playedpiece)
{
    int i=moves.initialmove.line,j=moves.initialmove.column;
    if (A[i][j].type == playedpiece.type && A[i][j].color == playedpiece.color)
    {
        if (isEatingMove(A,moves,playedpiece)==1)
        { 
            A[moves.finalmove.line][moves.finalmove.column] = playedpiece;
            A[i][j].color = VIDE;
            A[i][j].type = VIDE;
            A[i][j].firstmove = VIDE;
            int fin=(i==moves.finalmove.line) ? moves.finalmove.column : moves.finalmove.line; // on prend la position final si elle est de colonne ou d eligne
            if (i<moves.finalmove.line || j<moves.finalmove.column){
                for (int k= (i==moves.finalmove.line) ? j : i,b=k;k<fin;k+=2)
                {
                    if (b==i) // le mouvement a été fait sur rangée verticale, donc changement de ligne
                    {
                        if (A[k][j].type != VIDE) 
                        {
                            A[k][j].color = VIDE;
                            A[k][j].type = VIDE;
                            A[k][j].firstmove = VIDE;
                        }
                    }
                    else // mouvement fait sur rangée horizontale, donc changement de colonne
                    {
                        if (A[i][k].type != VIDE) 
                        {
                            A[i][k].color = VIDE;
                            A[i][k].type = VIDE;
                            A[i][k].firstmove = VIDE;
                        }
                    }
                }
            }
            if (i>moves.finalmove.line || j>moves.finalmove.column)
            {
                for (int k= (i==moves.finalmove.line) ? j : i,b=k;k>fin;k-=2)
                {
                    if (b==i) // le mouvement a été fait sur rangée verticale, donc changement de ligne
                    {
                        if (A[k][j].type != VIDE) 
                        {
                            A[k][j].color = VIDE;
                            A[k][j].type = VIDE;
                            A[k][j].firstmove = VIDE;
                        }
                    }
                    else // mouvement fait sur rangée horizontale, donc changement de colonne
                    {
                        if (A[i][k].type != VIDE) 
                        {
                            A[i][k].color = VIDE;
                            A[i][k].type = VIDE;
                            A[i][k].firstmove = VIDE;
                        }
                    }
                }
            }
        }
        else if(isOptionalCapture(A,moves,playedpiece) == 1 /*|| CompulsoryCapture(parametre)*/)
        { 
            A[moves.finalmove.line][moves.finalmove.column] = playedpiece;
            A[moves.finalmove.line][moves.finalmove.column].firstmove = 0;
            A[i][j].color = VIDE;
            A[i][j].type = VIDE;
            A[i][j].firstmove = VIDE;
        }
    }
}

