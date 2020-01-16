#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "moves.h"
#include "checks.h"

int played;

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
{ // verifie si le roi est toujours séparé d'une case par rapport à l'autre roi
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


int isLegalMove(piece **A,movement moves, piece playedpiece) 
{
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
                if(playedpiece.firstmove == 1)
                {
                    if((j == moves.initialmove.column)
                    && (i-moves.initialmove.line == 2 || i-moves.initialmove.line == 4))
                    {
                        for (int k = moves.initialmove.line+1;k<=i;k++) 
                        {
                            if (A[k][j].type != VIDE) return 0;
                        }
                        return 1;
                    }
                }
                if(moves.initialmove.column % 2 ==1)
                {// cas de pion horizontal
                    // cas 1 et 3
                    if((i - moves.initialmove.line) == 1
                        && fabs(j - moves.initialmove.column) == 1
                        && A[i][j].type == VIDE)
                    { //tester si les cases vides pour les occupées
                        return 1;
                    }
                    // cas 2
                    else if(j == moves.initialmove.column
                            && A[moves.initialmove.line+1][j].type == VIDE
                            && i == moves.initialmove.line+2
                            && A[i][j].type == VIDE)
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
                if(playedpiece.firstmove == 1)
                {
                    if((j == moves.initialmove.column)
                    && (i-moves.initialmove.line == -2 || i-moves.initialmove.line == -4))
                    { 
                        for (int k = moves.initialmove.line-1;k>=i;k--) 
                        {
                            if (A[k][j].type != VIDE) return 0;
                        }
                        
                        return 1;
                    }
                }
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
        else return 0;
    }
    else if (playedpiece.type == DAME) // cas d'une dame
    {
        if(isDefaultMove(playedpiece,moves) == 1)
        {   if (A[i][j].type != VIDE) return 0;
            if(moves.initialmove.column % 2 == 0 && j==moves.initialmove.column)//mouvement colonnes verticale
            {
                if(i > moves.initialmove.line) // cas mouvement descendant
                {
                    for(int k=moves.initialmove.line+2 ; k<=i ;k+=2)
                    {
                        if(A[k][j].type != VIDE)  return 0;//tester si toutes les case sont vides
                    }
                    return 1;
                }
                else if(i < moves.initialmove.line)// cas mouvement ascendant
                {
                    for(int k=moves.initialmove.line-2 ; k>=i ;k-=2) // on commence de la 1ere case et on parcourt jusqu'à la position finale
                    {
                        if(A[k][j].type != VIDE) return 0; //tester si toutes les case sont vides
                    }
                    return 1;
                }
                return 0;
            }
            else if(moves.initialmove.column % 2 == 1 && j==moves.initialmove.column)//mouvement rangée verticale
            {
                if(i > moves.initialmove.line) // cas mouvement descendant
                {
                    for(int k=moves.initialmove.line+1 ; k<i-1 ;k+=2)
                    {
                        if(A[k][j].type != VIDE) return 0; //tester si toutes les cases royales sont vides
                    }
                    return 1;
                }
                else if(i < moves.initialmove.line)// cas mouvement ascendant
                {
                    for(int k=moves.initialmove.line-1 ; k>i+1 ;k-=2)
                    {
                        if(A[k][j].type != VIDE) return 0; //tester si toutes les cases royales sont vides
                    }
                    return 1;
                }
                return 0;
            }
            else if(i == moves.initialmove.line && moves.initialmove.line % 2 == 0)// mouvement colonnes horizontale
            {
                if(j > moves.initialmove.column) // cas mouvement à droite
                {
                    for(int k=moves.initialmove.column+2 ; k<=j ; k+=2)// tester si tous les case sont vide
                    {
                        if(A[i][k].type != VIDE) return 0;
                    }
                    return 1;
                }
                else if(j < moves.initialmove.column)// cas mouvement à gauche
                {
                    for(int k=moves.initialmove.column-2 ; k>=j ; k-=2)// tester si tous les case sont vide
                    {
                        if(A[i][k].type != VIDE) return 0;
                    }
                    return 1;
                }
                return 0;
            }
            else if(i == moves.initialmove.line && moves.initialmove.line % 2 == 1)// mouvement rangée horizontale
            {
                if(j > moves.initialmove.column) // cas mouvement à droite
                {
                    for(int k=moves.initialmove.column+1 ; k<j-1 ; k+=2)// tester si toutes les cases royales sont vides
                    {
                        if(A[i][k].type != VIDE) return 0;
                    }
                    return 1;
                }
                else if(j < moves.initialmove.column)// cas mouvement à gauche
                {
                    for(int k=moves.initialmove.column-1 ; k>j+1 ; k-=2)// tester si toutes les cases royales sont vides
                    {
                        if(A[i][k].type != VIDE) return 0;
                    }
                    return 1;
                }
                return 0;
            }
            else // cas des petits mouvement de pivot. (colonne vers ligne ou ligne vers colonne)
            {
                if (A[i][j].type != VIDE) return 0;
                else return 1;
            }
        }
        return 0;
    }
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
        else if (playedpiece.color == BLANCHE)
        {
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
{ //si le mouvement est un mouvement de capture
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
                else if(i - moves.initialmove.line == 8)
                { // cas de double EatMove
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
                else if(i - moves.initialmove.line == 12)
                    { // cas de triple EatMove
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
                       && A[moves.initialmove.line+12][j].type == VIDE)
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
            if(moves.initialmove.column % 2 == 1 && j == moves.initialmove.column)
            { // cas de pion horizontal
                if(moves.initialmove.line - i == 4)
                { // cas simple EatMove
                    if(A[moves.initialmove.line-1][j].type == VIDE
                       && A[moves.initialmove.line-2][j].color == NOIRE
                       && A[moves.initialmove.line-3][j].type == VIDE
                       && A[i][j].type == VIDE
                       && (A[i-1][j].type != VIDE || A[i-2][j].type == VIDE) )
                    {
                        return 1;
                    }
                    return 0;
                }
                else if(moves.initialmove.line - i == 8)
                { // cas de double EatMove
                    if(A[moves.initialmove.line-1][j].type == VIDE
                       && A[moves.initialmove.line-2][j].color == NOIRE
                       && A[moves.initialmove.line-3][j].type == VIDE
                       && A[moves.initialmove.line-4][j].type == VIDE
                       && A[moves.initialmove.line-5][j].type == VIDE
                       && A[moves.initialmove.line-6][j].type == NOIRE
                       && A[moves.initialmove.line-7][j].type == VIDE
                       && A[i][j].type == VIDE
                       && (A[i-1][j].type != VIDE || A[i-2][j].type == VIDE ))
                    {
                        return 1;
                    }
                    return 0;
                }
                else if(i - moves.initialmove.line == 12)
                    { // cas de triple EatMove
                        if(A[moves.initialmove.line-1][j].type == VIDE
                            && A[moves.initialmove.line-2][j].color == NOIRE
                            && A[moves.initialmove.line-3][j].type == VIDE
                            && A[moves.initialmove.line-4][j].type == VIDE
                            && A[moves.initialmove.line-5][j].type == VIDE
                            && A[moves.initialmove.line-6][j].type == NOIRE
                            && A[moves.initialmove.line-7][j].type == VIDE
                            && A[moves.initialmove.line-8][j].type == VIDE
                            && A[moves.initialmove.line-9][j].type == VIDE
                            && A[moves.initialmove.line-10][j].type == NOIRE
                            && A[moves.initialmove.line-11][j].type == VIDE
                            && A[moves.initialmove.line-12][j].type == VIDE)
                        {
                            return 1;
                        }
                    }
                return 0;
            }
        }
        return 0;
    }
    else if(playedpiece.type == DAME) // cas d'une dame
    {
        if (isLegalMove(A, moves, playedpiece)==1)
        {

            if (playedpiece.color == NOIRE )
            {
                if (i==moves.initialmove.line && i%2==1) // mouvement sur les rangées en horizontal
                {
                    if (j > moves.initialmove.column) // on bouge vers la droite, indice croissant
                    {
                        for (int k=moves.initialmove.column+2; k<=j; k+=2)
                        {
                            if (A[i][k].color == NOIRE //on parcourt la ligne jusqu'à la position finale pour voir si
                                ||(A[i][k].color == BLANCHE && A[i][k+2].type != VIDE)) // on trouve pour chaque blanc, une case vide devant lui
                            {                                           // et pas de noir sur le chemin.
                                return 0;
                            }

                        }
                        for (int k=j;k<14;k+=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[i][k].color == NOIRE
                                ||(A[i][k].color == BLANCHE && A[i][k+2].type != VIDE)) break;
                            if (A[i][k].color == BLANCHE && A[i][k+2].type == VIDE) return 0;
                        }
                        return 1;

                    }
                    else if (j < moves.initialmove.column) // on va vers la gauche, indice décroissan
                    {
                        for (int k=moves.initialmove.column-2; k>=j; k-=2)
                        {
                            if (A[i][k].color == NOIRE //on parcourt la ligne jusqu'à la position finale pour voir si
                                ||(A[i][k].color == BLANCHE && A[i][k-2].type != VIDE)) // on trouve pour chaque blanc, une case vide devant lui
                            {                                           // et pas de noir sur le chemin.
                                return 0;
                            }

                        }
                        for (int k=j;k>0;k-=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[i][k].color == NOIRE
                                ||(A[i][k].color == BLANCHE && A[i][k-2].type != VIDE)) break;
                            if (A[i][k].color == BLANCHE && A[i][k-2].type == VIDE) return 0;
                        }
                        return 1;

                    }
                    else return 0;
                }
                else if (j==moves.initialmove.column && j%2==1) // mouvement sur les rangées verticales
                {
                    if (i > moves.initialmove.line) // on bouge vers le bas, indice croissant
                    {
                        for (int k=moves.initialmove.line+2; k<=i; k+=2)
                        {
                            if (A[k][j].color == NOIRE //on parcourt la colonne jusqu'à la position finale pour voir si
                                ||(A[k][j].color == BLANCHE && A[k+2][j].type != VIDE)) // on trouve pour chaque blanc, une case vide devant lui
                            {                                           // et pas de noir sur le chemin.
                                return 0;
                            }

                        }
                        for (int k=i;k<14;k+=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[k][j].color == NOIRE
                                ||(A[k][j].color == BLANCHE && A[k+2][j].type != VIDE)) break;
                            if (A[k][j].color == BLANCHE && A[k+2][j].type == VIDE) return 0;
                        }
                        return 1;

                    }
                    else if (i < moves.initialmove.line) // on va vers le haut, indice décroissant
                    {
                        for (int k=moves.initialmove.line-2; k>=i; k-=2)
                        {
                            if (A[k][j].color == NOIRE //on parcourt la colonne jusqu'à la position finale pour voir si
                                ||(A[k][j].color == BLANCHE && A[k-2][j].type != VIDE)) // on trouve pour chaque blanc, une case vide devant lui
                            {                                           // et pas de noir sur le chemin.
                                return 0;
                            }

                        }
                        for (int k=i;k>0;k-=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[k][j].color == NOIRE
                                ||(A[k][j].color == BLANCHE && A[k-2][j].type != VIDE)) break;
                            if (A[k][j].color == BLANCHE && A[k-2][j].type == VIDE) return 0;
                        }
                        return 1;

                    }
                    else return 0;
                }
                else return 1;
            }
            else if (playedpiece.color == BLANCHE)
            {
                if (i==moves.initialmove.line && i%2==1) // mouvement sur les rangées en horizontal avec la dame en position verticale
                {
                    if (j > moves.initialmove.column) // on bouge vers la droite, indice croissant
                    {
                        for (int k=moves.initialmove.column+2; k<=j; k+=2)
                        {
                            if (A[i][k].color == BLANCHE //on parcourt la ligne jusqu'à la position finale pour voir si
                                ||(A[i][k].color == NOIRE && A[i][k+2].type != VIDE)) // on trouve pour chaque blanc, une case vide devant lui
                            {                                           // et pas de noir sur le chemin.
                                return 0;
                            }

                        }
                        for (int k=j;k<14;k+=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[i][k].color == BLANCHE
                            ||(A[i][k].color == NOIRE && A[i][k+2].type != VIDE)) break;
                            if (A[i][k].color == NOIRE && A[i][k+2].type == VIDE) return 0;
                        }
                        return 1;

                    }
                    else if (j < moves.initialmove.column) // on va vers la gauche, indice décroissan
                    {
                        for (int k=moves.initialmove.column-2; k>=j; k-=2)
                        {
                            if (A[i][k].color == BLANCHE //on parcourt la ligne jusqu'à la position finale pour voir si
                                ||(A[i][k].color == NOIRE && A[i][k-2].type != VIDE)) // on trouve pour chaque blanc, une case vide devant lui
                            {                                           // et pas de noir sur le chemin.
                                return 0;
                            }

                        }
                        for (int k=j;k>0;k-=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[i][k].color == BLANCHE
                            ||(A[i][k].color == NOIRE && A[i][k-2].type != VIDE)) break;
                            if (A[i][k].color == NOIRE && A[i][k-2].type == VIDE) return 0;
                        }
                        return 1;

                    }
                    else return 0;
                }
                else if (j==moves.initialmove.column && j%2==1) // mouvement sur les rangées verticales
                {
                    if (i > moves.initialmove.line) // on bouge vers le bas, indice croissant
                    {
                        for (int k=moves.initialmove.line+2; k<=i; k+=2)
                        {
                            if (A[k][j].color == BLANCHE //on parcourt la colonne jusqu'à la position finale pour voir si
                                ||(A[k][j].color == NOIRE && A[k+2][j].type != VIDE)) // on trouve pour chaque blanc, une case vide devant lui
                            {                                           // et pas de noir sur le chemin.
                                return 0;
                            }

                        }
                        for (int k=i;k<14;k+=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[k][j].color == BLANCHE 
                                ||(A[k][j].color == NOIRE && A[k+2][j].type != VIDE) ) break;
                            if (A[k][j].color == NOIRE && A[k+2][j].type == VIDE) return 0;
                        }
                        return 1;

                    }
                    else if (i < moves.initialmove.line) // on va vers le haut, indice décroissant
                    {
                        for (int k=moves.initialmove.line-2; k>=i; k-=2)
                        {
                            if (A[k][j].color == BLANCHE //on parcourt la colonne jusqu'à la position finale pour voir si
                                ||(A[k][j].color == NOIRE && A[k-2][j].type != VIDE)) // on trouve pour chaque blanc, une case vide devant lui
                            {                                           // et pas de blanc sur le chemin.
                                return 0;
                            }

                        }
                        for (int k=i;k>=2;k-=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[k][j].color == BLANCHE
                                ||(A[k][j].color == NOIRE && A[k-2][j].type != VIDE)) break;
                            if (A[k][j].color == NOIRE && A[k-2][j].type == VIDE) return 0;
                        }
                        return 1;

                    }
                    else return 0;
                }
                else return 1;
            }
        }
        else return 0;
    }
}


int isOptionalCapture(piece **A,movement moves, piece playedpiece)
{
    int i=moves.initialmove.line,j=moves.initialmove.column;
    if (playedpiece.type == PION)
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
    if (playedpiece.type == DAME)
    {
        if (playedpiece.color == NOIRE) //la piece jouée est NOIRE
        {
            if ( ((j%2==0 && (fabs(moves.finalmove.line - i)==2 && j==moves.finalmove.column))// dame verticale et capturer avant ou arriere
                    || (j%2==1 && fabs(moves.finalmove.column - j)==2 && i==moves.finalmove.line)) // dame horizontale et capture droite ou gauche
                && A[moves.finalmove.line][moves.finalmove.column].color == BLANCHE) // presence de piece de couleur opposée sur la petite case
            {
                return 1;
            }
            return 0;
        }
        else // la piece jouée est BLANCHE
        {
            if ( ((j%2==0 && (fabs(moves.finalmove.line - i)==2 && j==moves.finalmove.column))// dame verticale et capturer avant ou arriere
                || (j%2==1 && fabs(moves.finalmove.column - j)==2 && i==moves.finalmove.line)) // dame horizontale et capture droite ou gauche
                && A[moves.finalmove.line][moves.finalmove.column].color == NOIRE) // presence de piece de couleur opposée sur la petite case
            {
                return 1;
            }
        return 0;
        }

    }
    return 0;
}

int KingImmoByPiece(piece **A,int i,int j,int couleur)
{
    if(i == 1 && j == 1) // tester si le roi existe dans la case A[1][1]
        {
            if(A[i][j+1].color == couleur && A[i+1][j].color == couleur) return 1;
            return 0;
        }
        else if(i<13 && i>1 && j == 1)// tester si le roi existe entre les cases A[1][1] et A[13][1]
        {
            if(A[i][j+1].color == couleur && A[i][j-1].color == couleur && A[i+1][j].color == couleur) return 1;
            return 0;
        }
        else if(i == 13 && j == 1)// tester si le roi existe dans la case A[13][1]
        {
            if(A[i][j-1].color == couleur && A[i+1][j].color == couleur) return 1;
            return 0;
        }
        else if(j<13 && j>1 && i == 1)// tester si le roi existe entre les cases A[1][1] et A[1][13]
        {
            if(A[i-1][j].color == couleur && A[i+1][j].color == couleur && A[i][j-1].color == couleur) return 1;
            return 0;
        }
        else if(i == 13 && j == 13)// tester si le roi existe dans la case A[13][13]
        {
            if(A[i-1][j].color == couleur && A[i][j-1].color == couleur) return 1;
            return 0;
        }
        else if(j<13 && j>1 && i == 13)// tester si le roi existe entre les cases A[13][1] et A[13][13]
        {
            if(A[i][j-1].color == couleur && A[i][j+1].color == couleur && A[i-1][j].color == couleur) return 1;
            return 0;
        }
        else if(j == 1 && i == 13)// tester si le roi existe dans la case A[13][1]
        {
            if(A[i-1][j].color == couleur && A[i][j+1].color == couleur) return 1;
            return 0;
        }
        else if(i<13 && i>1 && j == 1)// tester si le roi existe entre les cases A[1][1] et A[13][1]
        {
            if(A[i-1][j].color == couleur && A[i+1][j].color == couleur && A[i][j+1].color == couleur) return 1;
            return 0;
        }
}


int KingImmoByKing(piece **A,int i,int j,int couleur)
{
    if(A[i-1][j].color == couleur && A[i][j+1].color == couleur && A[i][j-1].color == couleur)
    {
        movement moves;
        moves.initialmove.line = i;
        moves.initialmove.column = j;
        moves.finalmove.line = i+2;
        moves.finalmove.column = j;

        piece playedpiece;
        playedpiece.color = A[i][j].color;
        playedpiece.type = A[i][j].type;
        playedpiece.firstmove = A[i][j].firstmove;

        if(checkKing(moves,playedpiece,A) == 0) return 1;
    }
    else if(A[i-1][j].color == couleur && A[i+1][j].color == couleur && A[i][j+1].color == couleur)
    {
        movement moves;
        moves.initialmove.line = i;
        moves.initialmove.column = j;
        moves.finalmove.line = i;
        moves.finalmove.column = j-2;

        piece playedpiece;
        playedpiece.color = A[i][j].color;
        playedpiece.type = A[i][j].type;
        playedpiece.firstmove = A[i][j].firstmove;

        if(checkKing(moves,playedpiece,A) == 0) return 1;
    }
    else if(A[i+1][j].color == couleur && A[i][j-1].color == couleur && A[i][j+1].color == couleur)
    {
        movement moves;
        moves.initialmove.line = i;
        moves.initialmove.column = j;
        moves.finalmove.line = i-2;
        moves.finalmove.column = j;

        piece playedpiece;
        playedpiece.color = A[i][j].color;
        playedpiece.type = A[i][j].type;
        playedpiece.firstmove = A[i][j].firstmove;

        if(checkKing(moves,playedpiece,A) == 0) return 1;
    }
    else if(A[i][j-1].color == couleur && A[i-1][j].color == couleur && A[i+1][j].color == couleur)
    {
        movement moves;
        moves.initialmove.line = i;
        moves.initialmove.column = j;
        moves.finalmove.line = i;
        moves.finalmove.column = j+2;

        piece playedpiece;
        playedpiece.color = A[i][j].color;
        playedpiece.type = A[i][j].type;
        playedpiece.firstmove = A[i][j].firstmove;

        if(checkKing(moves,playedpiece,A) == 0) return 1;
    }
    return 0;
}


int isDraw(piece ** A)
{
    int i,j,k=0;
    for(i=0 ;i<DIM_PLAT ;i++)
    {
        for(j=0 ; j<DIM_PLAT ; j++)
        {
            if(A[i][j].color == NOIRE)
            {
                k++;
            }
        }
    }
    if(k == 1)
    {
        for(i=0 ;i<DIM_PLAT ;i++)
        {
            for(j=0 ; j<DIM_PLAT ; j++)
            {
                if(A[i][j].type == ROI && A[i][j].color == NOIRE) // charcher le roi noire
                {
                    break;
                }
            }
        }
        if(KingImmoByPiece(A,i,j,BLANCHE) == 1) return 1;
        if(KingImmoByKing(A,i,j,BLANCHE) == 1) return 1;
    }
    k=0;
    for(i=0 ;i<DIM_PLAT ;i++)
    {
        for(j=0 ; j<DIM_PLAT ; j++)
        {
            if(A[i][j].color == BLANCHE)
            {
                k++;
            }
        }
    }
    if(k == 1)
    {
        for(i=0 ;i<DIM_PLAT ;i++)
        {
            for(j=0 ; j<DIM_PLAT ; j++)
            {
                if(A[i][j].type == ROI && A[i][j].color == BLANCHE) // charcher le roi blanche
                {
                    break;
                }
            }
        }
        if(KingImmoByPiece(A,i,j,NOIRE) == 1) return 1;
        if(KingImmoByKing(A,i,j,NOIRE) == 1) return 1;
    }
    return 0;
}


int CheckMat(piece ** A,int *lost_player)
{
    for(int i = 1 ; i<DIM_PLAT ; i+=2)
    {
        for(int j = 1 ; j<DIM_PLAT ; j+=2)
        {
            if(A[i][j].type == ROI) // teste si la piece est roi
            {
                if(A[i][j+1].type != VIDE && A[i][j-1].type != VIDE
                   && A[i+1][j].type != VIDE && A[i-1][j].type != VIDE)// tester si il ya 4 piece autour du roi
                {
                    if((A[i][j+1].color != A[i][j-1].color) || (A[i][j+1].color != A[i+1][j].color)
                       || (A[i][j+1].color != A[i-1][j].color)) //teser si une des pieces a des couleurs différents
                    {
                        return 0;
                        *lost_player=A[i][j].color; // on récupère la couleur du joueur qui a été MAT.
                    }
                }
            }
        }
    }
    return 1;
}
