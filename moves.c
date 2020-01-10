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
{ //verifie si une piece est sur le chemin du roi
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
    if ((king.color == A[moves.initialmove.line][moves.initialmove.column].color)
        &&(king.type == A[moves.initialmove.line][moves.initialmove.column].type)
        &&(king.firstmove == A[moves.initialmove.line][moves.initialmove.column].firstmove))
    {
        if (isDefaultMove(king,moves) && checkKing(moves,king,A) && checkPiece(moves,A))
        {
            A[i][j] = king;
            A[moves.initialmove.line][moves.initialmove.column].type = VIDE;
            A[moves.initialmove.line][moves.initialmove.column].color = VIDE;
            A[moves.initialmove.line][moves.initialmove.column].firstmove = VIDE;
        }
    }
}

int isOptionalCapture(piece **A,movement moves, piece playedpiece) 
{
    int i=moves.initialmove.line,j=moves.initialmove.column;
    if (playedpiece.type == PION || playedpiece.type == DAME) 
    {
        if (j%2==0) { //si la colonne est paire, la piece est verticale, elle peut donc faire la capture verticale qui est optionnelle
            if (playedpiece.color == NOIRE) 
            {
                if (moves.finalmove.line - i == 2 && j==moves.finalmove.column
                    && A[moves.finalmove.line][moves.finalmove.column].color == BLANCHE)
                {
                    return 1;
                }
                return 0;
            }
            else 
            {
                if (moves.finalmove.line - i == -2 && j==moves.finalmove.column
                    && A[moves.finalmove.line][moves.finalmove.column].color == NOIRE)
                {
                    return 1;
                }
            return 0;
            }
        }
        return 0;
    }
    return 0;
}

void MovePion(piece **A,movement moves, piece playedpiece) 
{
    int i=moves.initialmove.line,j=moves.initialmove.column;
    if (A[i][j].type == playedpiece.type && A[i][j].color == playedpiece.color && A[i][j].firstmove == playedpiece.firstmove)
    {
            if (isOptionalCapture(A,moves,playedpiece) == 1 || isLegalMove(A, moves, playedpiece) == 1 ) 
            {
                A[moves.finalmove.line][moves.finalmove.column] = playedpiece;
                A[i][j].color = VIDE;
                A[i][j].type = VIDE;
                A[i][j].firstmove = VIDE;
            }
        }
}

int isLegalMove(piece **A,movement moves, piece playedpiece) {
    int i=moves.finalmove.line,j=moves.finalmove.column;
    if(playedpiece.type == PION)
    {
            /*
             pion est horizontal cas 1,2,3  | pion est: vertical cas 4,5,6
            cas 1 sens trigo inverse     cas 3 sens trigo       cas 2 up and jump case king
            cas 4 sens trigo inverse     cas 6 sens trigo       cas 6 up jump butee
            */
        if(isDefaultMove(playedpiece,moves) == 1)
        {
            if(playedpiece.color == NOIRE)
            {
                if(moves.initialmove.column % 2 ==1)
                {// cas de pion horizontal
                    // cas 1 et 3
                    if((i - moves.initialmove.line) == 1 && fabs(j - moves.initialmove.column) == 1
                        && A[i][j].type == VIDE)
                    { //tester si les cases vides pour les occupées
                        return 1;
                    }
                    // cas 2
                    else if(j == moves.initialmove.column && A[moves.initialmove.line+1][j].type == VIDE
                            && i == moves.initialmove.line+2 && A[i][j].type == VIDE)
                            { // tester s'il n ya pas de roi et la cas vide
                                return 1;
                            }
                        return 0;
                }
                else if(moves.initialmove.column % 2 == 0)
                    { // cas de pion verticale
                    // cas 4 et 6
                    if((i - moves.initialmove.line) == 1 && fabs(j - moves.initialmove.column) == 1
                    && A[i][j].type == VIDE)
                    { // tester si les cas sont vides pour les occuper
                        return 1;
                    }
                        // cas 5
                        //tester si la case est vide pour l'occuper
                    else if(j == moves.initialmove.column && i == moves.initialmove.line+2 && A[i][j].type == VIDE)
                    {
                        return 1;
                    }
                    return 0;
                    }
                return 0;
            }
            else if(playedpiece.color == BLANCHE)
                {
                    if(moves.initialmove.column % 2 ==1)
                        {// cas de pion horizontal
                    // cas 1 et 3
                        if((i - moves.initialmove.line) == -1 && fabs(j - moves.initialmove.column) == 1
                        && A[i][j].type == VIDE)
                        {
                                return 1;
                        }
                            // cas 2
                        else if(j == moves.initialmove.column && A[moves.initialmove.line-1][j].type == VIDE
                                && i == moves.initialmove.line-2 && A[i][j].type == VIDE)
                            {
                            return 1;
                            }
                        return 0;
                    }
                    else if(moves.initialmove.column % 2 == 0)
                    { // cas de pion verticale
                        // cas 4 et 6
                        if((i - moves.initialmove.line) == -1 && fabs(j - moves.initialmove.column) == 1
                            && A[i][j].type == VIDE)
                        {
                            return 1;
                        }
                        // cas 5
                        else if(j == moves.initialmove.column && i == moves.initialmove.line-2 && A[i][j].type == VIDE)
                                {
                                    return 1;
                                }
                        return 0;
                    }
                    return 0;
                }
        }
        else if(isEatingMove(A,moves,playedpiece) == 1)
        {
            return 1;
        }
        return 0;
    }
    /*else if (playedpiece.type == DAME)
    {
        //TODO

    }*/


}
int isDefaultMove(piece playedpiece,movement moves){
   // vérifie si le mouvement est par défaut possible, sans prendre en compte la présence de pièce de la couleur opposée.
    int i=moves.finalmove.line,j=moves.finalmove.column;
    if  (playedpiece.type == ROI) 
    { //check if moves in a + pattern. (horizontal et vertical seulement)
        if (( (fabs(moves.initialmove.line - moves.finalmove.line)==2 && moves.initialmove.column == moves.finalmove.column)
            ||(fabs(moves.initialmove.column - moves.finalmove.column)==2 && moves.initialmove.line == moves.finalmove.line )))
        {
            return 1; //1 : Le mouvement est par défaut possible
        }
        else return 0; //0 : mouvement pas possible.
    }
    else if (playedpiece.type == PION)
    {
        if (playedpiece.color == NOIRE) 
        
        {
            if (playedpiece.firstmove == 1) 
            {
                if ( ((j == moves.initialmove.column)
                    && (i-moves.initialmove.line == 2 || i-moves.initialmove.line == 4))
                    || (fabs(j-moves.initialmove.column)==1 && i-moves.initialmove.line==1))
                {
                        return 1;
                }
                else return 0;
            }
            else 
            {
                if ((j == moves.initialmove.column && i-moves.initialmove.line == 2)
                || (fabs(j-moves.initialmove.column) == 1 && i-moves.initialmove.line == 1))
                {
                    return 1;
                }
                else return 0;
            }

        }
        else if (playedpiece.color == BLANCHE) {
            if (playedpiece.firstmove == 1) {
                if ( ((j == moves.initialmove.column)
                    && (i-moves.initialmove.line == -2 || i-moves.initialmove.line == -4))
                    || (fabs(j-moves.initialmove.column)== 1 && i-moves.initialmove.line== -1))
                {
                    return 1;
                }
                else return 0;
            }
            else 
            {
                if ((j == moves.initialmove.column && i-moves.initialmove.line == -2)
                || (fabs(j-moves.initialmove.column) == 1 && i-moves.initialmove.line == -1))
                {
                    return 1;
                }
                else return 0;
            }
        }
        else return 0;
    }
    else if (playedpiece.type == DAME)
    {
        if(moves.initialmove.line == i && (j-moves.initialmove.column)%2 == 0)
        {
            return 1;
        }
        else if(moves.initialmove.column == j && (i-moves.initialmove.line)%2 == 0)
        {
            return 1;
        }
            else if(moves.initialmove.column % 2 == 0 || moves.initialmove.line % 2 == 0)
            {
                if(fabs(i-moves.initialmove.line) == 1 && fabs(j-moves.initialmove.column) == 1)
                {
                    return 1;
                }
            }
        return 0;
    }
}

int isEatingMove(piece **A,movement moves, piece playedpiece)
{
    int i=moves.finalmove.line, j=moves.finalmove.column;
    if(playedpiece.type == PION)
    {
        if(playedpiece.color == NOIRE)
        { // cas de joueure noir
            if(moves.initialmove.column % 2 ==1 && j == moves.initialmove.column)
            { // cas de pion horizontal
                if(i - moves.initialmove.line == 4)
                { // cas simple EatMove
                    // tester les différent cases royales et l'existance d'une pience d'adversaice pour faire une simple eatmove
                    if(A[moves.initialmove.line+1][j].type == VIDE
                       && A[moves.initialmove.line+2][j].color == BLANCHE
                       && A[moves.initialmove.line+3][j].type == VIDE
                       && A[i][j].type == VIDE && (A[i+1][j].type != VIDE || A[i+2][j].type == VIDE || i+1>=15 || i+2>=15) )
                    {
                        return 1;
                    }
                    return 0;
                }
                else if(i - moves.initialmove.line == 8){ // cas de double EatMove
                // tester les différent cases royales et l'existance de 2 piences d'adversaice pour faire une double eatmove
                    if(A[moves.initialmove.line+1][j].type == VIDE
                       && A[moves.initialmove.line+2][j].color == BLANCHE
                       && A[moves.initialmove.line+3][j].type == VIDE
                       && A[moves.initialmove.line+4][j].type == VIDE
                       && A[moves.initialmove.line+5][j].type == VIDE
                       && A[moves.initialmove.line+6][j].type == BLANCHE
                       && A[moves.initialmove.line+7][j].type == VIDE
                       && A[i][j].type == VIDE && i<15 && (A[i+1][j].type != VIDE || A[i+2][j].type == VIDE || i+1>=15 || i+2>=15))
                    {
                       return 1;
                    }
                    return 0;
                }
                else if(i - moves.initialmove.line == 12){ // cas de triple EatMove
                    // tester les différent cases royales et l'existance de 3 piences d'adversaice pour faire une triple eatmove
                    if(A[moves.initialmove.line+1][j].type == VIDE
                       && A[moves.initialmove.line+2][j].color == BLANCHE
                       && A[moves.initialmove.line+3][j].type == VIDE
                       && A[moves.initialmove.line+4][j].type == VIDE
                       && A[moves.initialmove.line+5][j].type == VIDE
                       && A[moves.initialmove.line+6][j].type == BLANCHE
                       && A[moves.initialmove.line+7][j].type == VIDE
                       && A[moves.initialmove.line+8][j].type == VIDE
                       && A[moves.initialmove.line+9][j].type == VIDE
                       && A[moves.initialmove.line+10][j].type == BLANCHE
                       && A[moves.initialmove.line+11][j].type == VIDE
                       && A[moves.initialmove.line+12][j].type == VIDE && i<15)
                    {
                       return 1;
                    }
                }
                return 0;
            }
            return 0;
        }
        else if(playedpiece.color == BLANCHE)
        {
            if(moves.initialmove.column % 2 ==1 && j == moves.initialmove.column)
            { // cas de pion horizontal
                if(moves.initialmove.line - i == 4)
                { // cas simple EatMove
                    if(A[moves.initialmove.line-1][j].type == VIDE
                       && A[moves.initialmove.line-2][j].color == BLANCHE
                       && A[moves.initialmove.line-3][j].type == VIDE
                       && A[i][j].type == VIDE && i>=0 && (A[i-1][j].type != VIDE || A[i-2][j].type == VIDE || i-1>=0 || i-2>=0) )
                    {
                        return 1;
                    }
                    return 0;
                }
                else if(moves.initialmove.line - i == 8){ // cas de double EatMove
                    if(A[moves.initialmove.line-1][j].type == VIDE
                       && A[moves.initialmove.line-2][j].color == BLANCHE
                       && A[moves.initialmove.line-3][j].type == VIDE
                       && A[moves.initialmove.line-4][j].type == VIDE
                       && A[moves.initialmove.line+5][j].type == VIDE
                       && A[moves.initialmove.line-6][j].type == BLANCHE
                       && A[moves.initialmove.line-7][j].type == VIDE
                       && A[i][j].type == VIDE && i>=0 && (A[i-1][j].type != VIDE || A[i-2][j].type == VIDE || i-1>=0 || i-2>=0))
                    {
                        return 1;
                    }
                    return 0;
                }
                else if(i - moves.initialmove.line == 12){ // cas de triple EatMove
                        if(A[moves.initialmove.line-1][j].type == VIDE
                            && A[moves.initialmove.line-2][j].color == BLANCHE
                            && A[moves.initialmove.line-3][j].type == VIDE
                            && A[moves.initialmove.line-4][j].type == VIDE
                            && A[moves.initialmove.line-5][j].type == VIDE
                            && A[moves.initialmove.line-6][j].type == BLANCHE
                            && A[moves.initialmove.line-7][j].type == VIDE
                            && A[moves.initialmove.line-8][j].type == VIDE
                            && A[moves.initialmove.line-9][j].type == VIDE
                            && A[moves.initialmove.line-10][j].type == BLANCHE
                            && A[moves.initialmove.line-11][j].type == VIDE
                            && A[moves.initialmove.line-12][j].type == VIDE && i>=0)
                        {
                            return 1;
                        }
                    }   
                return 0;
            }
        }
        return 0;
    }
}
