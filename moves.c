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
