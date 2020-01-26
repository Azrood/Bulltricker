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
        return 0;
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

    } // traitement des cas spéciaux qui causent un débordement d'indice
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
    else if (j==1)
    {
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
                    { // tester s'il n ya pas de roi et la case vide
                            return 1;
                    }
                    return 0;
                }
                else if(moves.initialmove.column % 2 == 0)
                { // cas de pion verticale
                // cas 4 et 6
                    if((i - moves.initialmove.line) == 1
                        && fabs(j - moves.initialmove.column) == 1
                        && A[i][j].type == VIDE)
                    { // tester si les cas sont vides pour les occuper
                        return 1;
                    }
                        // cas 5
                        //tester si la case est vide pour l'occuper
                    else if(j == moves.initialmove.column
                            && i == moves.initialmove.line+2
                            && A[i][j].type == VIDE)
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
                    if((i - moves.initialmove.line) == -1
                        && fabs(j - moves.initialmove.column) == 1
                        && A[i][j].type == VIDE)
                    {
                            return 1;
                    }
                        // cas 2
                    else if(j == moves.initialmove.column
                            && A[moves.initialmove.line-1][j].type == VIDE
                            && i == moves.initialmove.line-2
                            && A[i][j].type == VIDE)
                    {
                        return 1;
                    }
                    return 0;
                }
                else if(moves.initialmove.column % 2 == 0)
                { // cas de pion verticale
                    // cas 4 et 6
                    if((i - moves.initialmove.line) == -1
                        && fabs(j - moves.initialmove.column) == 1
                        && A[i][j].type == VIDE)
                    {
                        return 1;
                    }
                    // cas 5
                    else if(j == moves.initialmove.column
                        && i == moves.initialmove.line-2
                        && A[i][j].type == VIDE)
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
        {
            if (A[i][j].type != VIDE) return 0;
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
                    for(int k=moves.initialmove.line+1 ; k<=i-1 ;k+=2)
                    {
                        if(A[k][j].type != VIDE) return 0; //tester si toutes les cases royales sont vides
                    }
                    return 1;
                }
                else if(i < moves.initialmove.line)// cas mouvement ascendant
                {
                    for(int k=moves.initialmove.line-1 ; k>=i+1 ;k-=2)
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
                    for(int k=moves.initialmove.column+1 ; k<=j-1 ; k+=2)// tester si toutes les cases royales sont vides
                    {
                        if(A[i][k].type != VIDE) return 0;
                    }
                    return 1;
                }
                else if(j < moves.initialmove.column)// cas mouvement à gauche
                {
                    for(int k=moves.initialmove.column-1 ; k>=j+1 ; k-=2)// tester si toutes les cases royales sont vides
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
    int delta_pion = i - moves.initialmove.line;
    int opponent_piece_count=0;
    if(playedpiece.type == PION)
    {
        //if (A[i][j].type != VIDE ) return 0;
        if(playedpiece.color == NOIRE)
        { // cas de joueure noir
            if(moves.initialmove.column % 2 ==1 && j == moves.initialmove.column)
            { // cas de pion horizontal
                if(delta_pion == 4 || delta_pion == 8 || delta_pion == 12)
                {

                    for (int k = moves.initialmove.line+2; k<i; k+=2) //boucle qui vérifie qu'on a bien fait un mouvement de capture
                    {
                        if (A[k-1][j].type != VIDE || A[k+1][j].type != VIDE) return 0;

                        if ((A[k][j].color == BLANCHE && A[k+2][j].type != VIDE)
                            || A[k][j].color == NOIRE) return 0;

                        if (A[k][j].color == BLANCHE) opponent_piece_count++; //on compte le nombre de piece adversaire
                    }

                    if (fabs(delta_pion/4) != opponent_piece_count) return 0; //si le mouvement donné ne correspond pas au nombre de pièces capturés
                    //par exemple pour un delta de 4, on doit avoir 1 pièce capturé, pour 8 on trouve 2 et ainsi de suite

                    if (i<12) // éviter débordement d'indice, si i=12, il n'y a par défaut pas de capture possible
                    {
                        //vérifier s'il reste un mouvement de capture ou non
                        if(A[i+1][j].type == VIDE
                            && A[i+2][j].color == BLANCHE
                            && A[i+3][j].type == VIDE
                            && A[i+4][j].type == VIDE)
                        {
                            return 0;
                        }
                    }
                    return 1;
                }
                else return 0;
            }
            else return 0;
        }
        else if(playedpiece.color == BLANCHE)
        {
            if(moves.initialmove.column % 2 == 1 && j == moves.initialmove.column)
            { // cas de pion horizontal
                if(delta_pion == -4 || delta_pion == -8 || delta_pion == -12) // mouvement de capture simple, double ou triple
                {
                    for (int k = moves.initialmove.line-2; k>i; k-=2) //boucle qui vérifie qu'on a bien fait un mouvement de capture
                    {
                        if (A[k+1][j].type != VIDE || A[k-1][j].type != VIDE) return 0;

                        if ((A[k][j].color == NOIRE && A[k-2][j].type != VIDE)
                            || A[k][j].color == BLANCHE) return 0;

                        if (A[k][j].color == NOIRE) opponent_piece_count++; //on compte le nombre de piece adversaire
                    }

                    if (fabs(delta_pion/4) != opponent_piece_count) return 0; //si le mouvement donné ne correspond pas au nombre de pièces capturés
                    //par exemple pour un delta de 4, on doit avoir 1 pièce capturé, pour 8 on trouve 2 et ainsi de suite
                    if (i>2) // éviter débordement d'indice, si i=2, il n'y a par défaut pas de capture possible
                    {
                        //vérifier s'il reste un mouvement de capture ou non
                        if(A[i-1][j].type == VIDE
                            && A[i-2][j].color == NOIRE
                            && A[i-3][j].type == VIDE
                            && A[i-4][j].type == VIDE)
                            return 0;
                    }
                    return 1;
                }
                else return 0;
            }
            return 0;
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
                        for (int k=j+1;k<12;k+=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[i][k+1].color == NOIRE
                                || A[i][k].type != VIDE
                                ||(A[i][k+1].color == BLANCHE //on trouve une pièce de couleur opposée
                                    && (A[i][k+2].type != VIDE //et la case royale qui la suit est occupé
                                        || A[i][k+3].type != VIDE))) break;// ou le rectangle suivant est occupé

                            if (A[i][k].type ==VIDE
                                && A[i][k+1].color== BLANCHE
                                && A[i][k+2].type == VIDE
                                && A[i][k+3].type == VIDE) return 0;
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
                        for (int k=j-1;k>2;k-=2)
                        {
                            //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[i][k-1].color == NOIRE
                                || A[i][k].type != VIDE
                                ||(A[i][k-1].color == BLANCHE //on trouve une pièce de couleur opposée
                                    && (A[i][k-2].type != VIDE //et la case royale qui la suit est occupé
                                        || A[i][k-3].type != VIDE))) break;// ou le rectangle suivant est occupé

                            if (A[i][k].type ==VIDE
                                && A[i][k-1].color== BLANCHE
                                && A[i][k-2].type == VIDE
                                && A[i][k-3].type == VIDE) return 0;
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
                        for (int k=i+1;k<12;k+=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[k+1][j].color == NOIRE
                                || A[k][j].type != VIDE
                                ||(A[k+1][j].color == BLANCHE //on trouve une pièce de couleur opposée
                                    && (A[k+2][j].type != VIDE //et la case royale qui la suit est occupé
                                        || A[k+3][j].type != VIDE))) break;// ou le rectangle suivant est occupé

                            if (A[k][j].type ==VIDE
                                && A[k+1][j].color== BLANCHE
                                && A[k+2][j].type == VIDE
                                && A[k+3][j].type == VIDE) return 0;
                        }
                        return 1;
                    }
                    else if (i < moves.initialmove.line) // on va vers le haut, indice décroissant
                    {
                        for (int k=moves.initialmove.line-2; k>=i; k-=2)
                        {
                            if (A[k][j].color == NOIRE //on parcourt la colonne jusqu'à la position finale pour voir si
                                || (A[k][j].color == BLANCHE && A[k-2][j].type != VIDE)) // on trouve pour chaque blanc, une case vide devant lui
                            {                                           // et pas de noir sur le chemin.
                                return 0;
                            }
                        }
                        for (int k=i-1;k>2;k-=2)
                        {
                            //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[k-1][j].color == NOIRE
                                || A[k][j].type != VIDE
                                ||(A[k-1][j].color == BLANCHE //on trouve une pièce de couleur opposée
                                    && (A[k-2][j].type != VIDE //et la case royale qui la suit est occupé
                                        || A[k-3][j].type != VIDE))) break;// ou le rectangle suivant est occupé

                            if (A[k][j].type ==VIDE
                                && A[k-1][j].color== BLANCHE
                                && A[k-2][j].type == VIDE
                                && A[k-3][j].type == VIDE) return 0;
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
                        for (int k=j+1;k<12;k+=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[i][k+1].color == BLANCHE
                                || A[i][k].type != VIDE
                                ||(A[i][k+1].color == NOIRE //on trouve une pièce de couleur opposée
                                    && (A[i][k+2].type != VIDE //et la case royale qui la suit est occupé
                                        || A[i][k+3].type != VIDE))) break;// ou le rectangle suivant est occupé

                            if (A[i][k].type ==VIDE
                                && A[i][k+1].color== NOIRE
                                && A[i][k+2].type == VIDE
                                && A[i][k+3].type == VIDE) return 0;
                        }
                        return 1;
                    }
                    else if (j < moves.initialmove.column) // on va vers la gauche, indice décroissant
                    {
                        for (int k=moves.initialmove.column-2; k>=j; k-=2)
                        {
                            if (A[i][k].color == BLANCHE //on parcourt la ligne jusqu'à la position finale pour voir si
                                ||(A[i][k].color == NOIRE && A[i][k-2].type != VIDE)) // on trouve pour chaque blanc, une case vide devant lui
                            {                                           // et pas de noir sur le chemin.
                                return 0;
                            }
                        }
                        for (int k=j-1;k>2;k-=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[i][k-1].color == BLANCHE
                                || A[i][k].type != VIDE
                                ||(A[i][k-1].color == NOIRE //on trouve une pièce de couleur opposée
                                    && (A[i][k-2].type != VIDE //et la case royale qui la suit est occupé
                                        || A[i][k-3].type != VIDE))) break;// ou le rectangle suivant est occupé

                            if (A[i][k].type ==VIDE
                                && A[i][k-1].color== NOIRE
                                && A[i][k-2].type == VIDE
                                && A[i][k-3].type == VIDE) return 0;
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
                        for (int k=i+1;k<12;k+=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[k+1][j].color == BLANCHE
                                || A[k][j].type != VIDE
                                ||(A[k+1][j].color == NOIRE //on trouve une pièce de couleur opposée
                                    && (A[k+2][j].type != VIDE //et la case royale qui la suit est occupé
                                        || A[k+3][j].type != VIDE))) break;// ou le rectangle suivant est occupé

                            if (A[k][j].type ==VIDE
                                && A[k+1][j].color== NOIRE
                                && A[k+2][j].type == VIDE
                                && A[k+3][j].type == VIDE) return 0;
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
                        for (int k=i-1;k>2;k-=2)
                        {   //on continue de parcourir jusqu'au bord du plateau pour voir s'il nous reste des pieces restantes à capturer
                            if (A[k-1][j].color == BLANCHE
                                || A[k][j].type != VIDE
                                ||(A[k-1][j].color == NOIRE //on trouve une pièce de couleur opposée
                                    && (A[k-2][j].type != VIDE //et la case royale qui la suit est occupé
                                        || A[k-3][j].type != VIDE))) break;// ou le rectangle suivant est occupé

                            if (A[k][j].type ==VIDE
                                && A[k-1][j].color== NOIRE
                                && A[k-2][j].type == VIDE
                                && A[k-3][j].type == VIDE) return 0;
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

int AbleToEat(piece **A,position pos)
{
    int i=pos.line,j=pos.column;
    piece playedpiece = A[i][j];
    movement moves;
    moves.initialmove = pos;
    moves.finalmove = pos; // la ligne sera changée suivant la couleur de la pièce donnée
    if (playedpiece.type == PION)
    {
        // si la piece est noire, la position finale qu'on va verifier sera initial+4,+8 ou +12
        //sinon ligne initial -4, -8 ou -12
        //on regarde si le mouvement est un mouvement de capture, si oui, alors la piece peut capturer et on retourne 1, s'il n'y a pas de capture possible, on retourne 0.
        for (int k=4;k<=12;k+=4)
        {
            moves.finalmove.line = (playedpiece.color == NOIRE) ? pos.line+k : pos.line-k;
            if (moves.finalmove.line <0
               || moves.finalmove.line >14 ) break;
            if (isEatingMove(A,moves,playedpiece)==1) return 1;
        }
        //sinon la piece ne peut pas capturer
        return 0;
    }
    else //la piece à la position i,j est une dame
    {   // on va pas verifier la couleur, on va seulement verifier si la dame est en position verticale (donc parcours horizontal) ou horizontal (parcours vertical)
        // ici on va parcourir pour chaque sens  si on trouve une piece de couleur differente
        int color = (playedpiece.color == NOIRE) ? BLANCHE : NOIRE; // si la pièce donnée est noire, on va chercher si on peut capturer une blanche et vice versa
        if (j%2==0) // la piece est verticale, donc on va faire un parcours horizontal
        {
            for (int p=0;p<DIM_PLAT;p+=2) // on va parcourir toute la ligne horizontale, jusqu'à trouver une position où on peut capturer, ou finir la boucle.
            {
                moves.finalmove.column = p;
                if (isEatingMove(A,moves,playedpiece)==1)
                {
                    if (moves.finalmove.column > j) // on a trouvé un mouvement possible à droite, vérifions si on a fait une capture
                    {
                        for (int k=j;k<moves.finalmove.column;k+=2)
                        {
                            if (A[i][k].color == color) return 1;
                        }
                    }
                    else // même chose mais pour la gauche
                    {
                        for (int k=j;k>moves.finalmove.column;k-=2)
                        {
                            if (A[i][k].color==color) return 1;
                        }
                    }
                }
            }
            return 0; // on est sortis de la boucle sans faire de capture, il n'y a donc pas de capture possible
        }
        else // la dame est horizontal, le parcours sera fait en vertical.
        {
            for (int p=0;p<DIM_PLAT;p+=2) // on va parcourir toute la rangee verticale, jusqu'à trouver une position où on peut capturer, ou finir la boucle.
            {
                moves.finalmove.line = p;
                if (isEatingMove(A,moves,playedpiece)==1)
                {
                    if (moves.finalmove.line > i) // on a trouvé un mouvement possible en bas, vérifions si on a fait une capture
                    {
                        for (int k=i;k<moves.finalmove.line;k+=2)
                        {
                            if (A[k][j].color == color) return 1;
                        }
                    }
                    else // même chose mais pour le haut
                    {
                        for (int k=i;k>moves.finalmove.line;k-=2)
                        {
                            if (A[k][j].color==color) return 1;
                        }
                    }
                }
            }
            return 0; //on a pas fait de capture.
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
        playedpiece = A[i][j];

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
        playedpiece = A[i][j];
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
        playedpiece = A[i][j];

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
        playedpiece = A[i][j];
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
                if(A[i][j].type == ROI && A[i][j].color == BLANCHE) // charcher le roi blanc
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
                    if(A[i][j].color != A[i][j+1].color
                       || A[i][j].color != A[i+1][j].color
                       || A[i][j].color != A[i-1][j].color
                       || A[i][j].color != A[i][j-1].color) //tester si une ou plusieurs pieces a des couleurs différents
                    {
                        *lost_player=A[i][j].color; // on récupère la couleur du joueur qui a été MAT.
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
