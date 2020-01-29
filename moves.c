#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "moves.h"
#include "checks.h"
#include "tools.h"

int played;

position ConvertirLocation(char positionstr[])
{
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




void MoveKing(piece **A,movement moves,piece king,position *Tab,Mix_Chunk * Hit)
{

    int i=moves.finalmove.line,j=moves.finalmove.column;
    if ((king.color == A[moves.initialmove.line][moves.initialmove.column].color)
        &&(king.type == A[moves.initialmove.line][moves.initialmove.column].type))
    {
        if (isDefaultMove(king,moves)
            && checkKing(moves,king,A)
            && checkPiece(moves,A)
            && CompulsoryCapture(A,Tab,moves))
        {
            A[i][j] = king;
            A[moves.initialmove.line][moves.initialmove.column].type = VIDE;
            A[moves.initialmove.line][moves.initialmove.column].color = VIDE;
            A[moves.initialmove.line][moves.initialmove.column].firstmove = VIDE;
            played = 1;
        }
    }
    else played = 0;
    if (played==1) Mix_PlayChannel(-1,Hit,0);
}


void MovePion(piece **A,movement moves, piece playedpiece, position *Tab,Mix_Chunk * eat,Mix_Chunk * Hit)
{
    int has_captured=0;
    int i=moves.initialmove.line,j=moves.initialmove.column;
    if (A[i][j].type == playedpiece.type && A[i][j].color == playedpiece.color)
    {
        if ((isOptionalCapture(A,moves,playedpiece) == 1 || isLegalMove(A, moves, playedpiece) == 1)
            && (CompulsoryCapture(A,Tab,moves)==1))
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
            played=1;
        }
        else if (isEatingMove(A,moves,playedpiece)==1
                && CompulsoryCapture(A,Tab,moves))
        {
            A[moves.finalmove.line][moves.finalmove.column] = playedpiece;
            A[moves.finalmove.line][moves.finalmove.column].firstmove = 0;
            A[i][j].color = VIDE;
            A[i][j].type = VIDE;
            A[i][j].firstmove = VIDE;
            if (moves.finalmove.line == 0 || moves.finalmove.line == 14)
            {
                A[moves.finalmove.line][moves.finalmove.column].type = DAME;
            }
            played=1;
            if (playedpiece.color==NOIRE) //indice croissant
            {
                for (int k=i;k<moves.finalmove.line;k+=2)
                {
                    if (A[k][j].type != VIDE)
                    {
                        has_captured=1;
                        A[k][j].color = VIDE;
                        A[k][j].type = VIDE;
                        A[k][j].firstmove = VIDE;
                    }
                }
            }
            else // piece blanche a capturé, indice décroissant
            {
                for (int k=i;k>moves.finalmove.line;k-=2)
                {
                    if (A[k][j].type != VIDE)
                    {
                        has_captured=1;
                        A[k][j].color = VIDE;
                        A[k][j].type = VIDE;
                        A[k][j].firstmove = VIDE;
                    }
                }
            }
        }
        else played=0;
    }
    if (has_captured==1) Mix_PlayChannel(-1,eat,0);
    else if(played==1) Mix_PlayChannel(-1,Hit,0);
}

void MoveDame(piece **A,movement moves, piece playedpiece,position *Tab,Mix_Chunk * eat,Mix_Chunk * Hit)
{
    int has_captured=0;
    int i=moves.initialmove.line,j=moves.initialmove.column;
    if (A[i][j].type == playedpiece.type && A[i][j].color == playedpiece.color)
    {
        if (isEatingMove(A,moves,playedpiece)==1
            && CompulsoryCapture(A,Tab,moves)==1)
        {
            A[moves.finalmove.line][moves.finalmove.column] = playedpiece;
            A[i][j].color = VIDE;
            A[i][j].type = VIDE;
            A[i][j].firstmove = VIDE;

            played=1;
            int fin=(i==moves.finalmove.line) ? moves.finalmove.column : moves.finalmove.line; // on prend la position final si elle est de colonne ou de ligne
            if (i<moves.finalmove.line || j<moves.finalmove.column) // mouvement ascendant ou vers la gauche
            {
                for (int k= (i==moves.finalmove.line) ? j : i , b=k;k<fin;k+=2)
                { // k sera la colonne finale si la ligne est constante ou la ligne finale sinon
                    if (b==i) // le mouvement a été fait sur rangée verticale, donc on a changement de ligne
                    {
                        if (A[k][j].type != VIDE)
                        {
                            has_captured=1;
                            A[k][j].color = VIDE;
                            A[k][j].type = VIDE;
                            A[k][j].firstmove = VIDE;
                        }
                    }
                    else // mouvement fait sur rangée horizontale, donc on a changement de colonne
                    {
                        if (A[i][k].type != VIDE)
                        {
                            has_captured=1;
                            A[i][k].color = VIDE;
                            A[i][k].type = VIDE;
                            A[i][k].firstmove = VIDE;
                        }
                    }
                }
            }
            if (i>moves.finalmove.line || j>moves.finalmove.column) // mouvement descendant ou vers la droite
            {
                for (int k= (i==moves.finalmove.line) ? j : i,b=k;k>fin;k-=2)
                {
                    if (b==i) // le mouvement a été fait sur rangée verticale, donc changement de ligne
                    {
                        if (A[k][j].type != VIDE)
                        {
                            has_captured=1;
                            A[k][j].color = VIDE;
                            A[k][j].type = VIDE;
                            A[k][j].firstmove = VIDE;
                        }
                    }
                    else // mouvement fait sur rangée horizontale, donc changement de colonne
                    {
                        if (A[i][k].type != VIDE)
                        {
                            has_captured=1;
                            A[i][k].color = VIDE;
                            A[i][k].type = VIDE;
                            A[i][k].firstmove = VIDE;
                        }
                    }
                }
            }
        }
        else if(isOptionalCapture(A,moves,playedpiece) == 1
                && CompulsoryCapture(A,Tab,moves)==1)
        {
            has_captured=1;
            played = 1;
            A[moves.finalmove.line][moves.finalmove.column] = playedpiece;
            A[moves.finalmove.line][moves.finalmove.column].firstmove = 0;
            A[i][j].color = VIDE;
            A[i][j].type = VIDE;
            A[i][j].firstmove = VIDE;
        }
        else played =0;
    }
    if (has_captured == 1) Mix_PlayChannel(-1,eat,0);
    else if(played==1) Mix_PlayChannel(-1,Hit,0);
}


int CompulsoryCapture(piece **A,position *Tab,movement moves)
{
    piece playedpiece = A[moves.initialmove.line][moves.initialmove.column];
    int start = (moves.initialmove.line == moves.finalmove.line) ? moves.initialmove.column : moves.initialmove.line;
    int finish = (moves.initialmove.line == moves.finalmove.line) ? moves.finalmove.column : moves.finalmove.line;
    int delta = finish - start;
    int opponent_color = (playedpiece.color == BLANCHE) ? NOIRE : BLANCHE;

    if (isEmpty(Tab)==1) return 1; // si le tableau est vide, la pièce peut bouger.
    //on va vérifier le 1er element du tableau des pièces à capture obligatoire, s'il y a une dame, on vérifie que le joueur a aussi sélectionné une dame
    //pour respecter la règle des priorités.

    if (A[Tab[0].line][Tab[0].column].type == DAME) // on a au moins une dame qui a une prise obligatoire
    {
        if (inTab(Tab,moves.initialmove)==1)
        {
            if (playedpiece.type == DAME
                && isEatingMove(A,moves,A[moves.initialmove.line][moves.initialmove.column])==1
                && ((moves.initialmove.line == moves.finalmove.line && moves.initialmove.line % 2==1)
                    || ((moves.finalmove.column == moves.initialmove.column) && moves.initialmove.column % 2==1)))
            {
                if (delta > 0) //indice croissant
                {
                    if (start == moves.initialmove.line) //mouvement sur rangée verticales
                    {
                        for (int k = start;k<finish;k+=2)
                        {
                            if (A[k][moves.initialmove.column].color == opponent_color) return 1;
                        }
                        return 0;
                    }
                    else // mouvement sur rangées horiztonales
                    {
                        for (int k = start;k<finish;k+=2)
                        {
                            if (A[moves.initialmove.line][k].color == opponent_color) return 1;
                        }
                        return 0;
                    }
                }
                else // indice decroissant
                {
                    if (start == moves.initialmove.line) //mouvement sur rangée verticales
                    {
                        for (int k = start;k>finish;k-=2)
                        {
                            if (A[k][moves.initialmove.column].color == opponent_color) return 1;
                        }
                        return 0;
                    }
                    else // mouvement sur rangées horizontales
                    {
                        for (int k = start;k>finish;k-=2)
                        {
                            if (A[moves.initialmove.line][k].color == opponent_color) return 1;
                        }
                        return 0;
                    }
                }
            }
            else return 0;
        }
        else return 0;
    }
    else if ((inTab(Tab,moves.initialmove)==1) )
    {
        if (isEatingMove(A,moves,A[moves.initialmove.line][moves.initialmove.column])) return 1;
        else return 0;
    }
    return 0;
}

void play(piece **A,position *Tab,movement *moves,piece *playedpiece,
            SDL_MouseButtonEvent button,int *move_initialized, int couleur, Mix_Chunk *eat,Mix_Chunk * Hit )
{
    char positionstr[10];
    //conversion des positions x et y en position A4, BV1 etc
    strcpy(positionstr , SavoirLocationY(button.y));
    strcat(positionstr , SavoirLocationX(button.x));

    if (*move_initialized == 0)
    {
        moves->initialmove = ConvertirLocation(positionstr);
        *playedpiece = A[moves->initialmove.line][moves->initialmove.column];
        playedpiece->color = couleur;
        *move_initialized = 1;
    }
    else
    {
        *move_initialized = 0;
        moves->finalmove = ConvertirLocation(positionstr);
        if (playedpiece->type == PION) MovePion(A,*moves,*playedpiece,Tab,eat,Hit);
        if (playedpiece->type == DAME) MoveDame(A,*moves,*playedpiece,Tab,eat,Hit);
        if (playedpiece->type == ROI) MoveKing(A,*moves,*playedpiece,Tab,Hit);
    }
}
