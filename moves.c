#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "moves.h"


position convertirlocation(char positionstr[]) { // Cette fonction marche correctement.
/* Elle retourne une structure Position avec les attributs line et colonne)*/
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

int isdefaultmove(piece playedpiece,movement moves){
   // vérifie si le mouvement est par défaut possible, sans prendre en compte la présence de pièce de la couleur opposée.
   // on ne prend pas le plateau en paramètre parce que la fonction ne prend pas en compte la présence des autres pièces.
   int i=moves.finalmove.line,j=moves.finalmove.column;
    if  (playedpiece.type == ROI) { //check if moves in a + pattern. (horizontal et vertical seulement)
        if (( (fabs(moves.initialmove.line - moves.finalmove.line)==2 && moves.initialmove.column == moves.finalmove.column) 
        || (fabs(moves.initialmove.column - moves.finalmove.column)==2 && moves.initialmove.line == moves.finalmove.line ))
        //bricolage 3la jehd.


            /*((A[i+2][j].type!=ROI || A[i+2][j].color == playedpiece.color)
            && (A[i-2][j].type!=ROI || A[i-2][j].color == playedpiece.color)
            && (A[i][j+2].type!=ROI || A[i][j+2].color == playedpiece.color)
            && (A[i][j-2].type!=ROI || A[i][j-2].color == playedpiece.color))*/

            // j'ai commenté ce bloc parce qu'il ne marche pas dans les cas où le roi joué est dans un coin.(indice négatif)
            //De toute façon il faut l'enlever, et faire une fonction legalmove plus tard.
            //je l'ai laissé pour que tu le voies. (Mais à supprimer)
        ){
            return 1; //1 : Le mouvement est par défaut possible
        }
        else return 0; //0 : mouvement pas possible.
       }
    else if (playedpiece.type == PION){
        //TO BE CONTINUED
    }
   }  