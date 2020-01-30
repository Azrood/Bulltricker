#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "moves.h"
#include "checks.h"
#include "tools.h"

#define ind_DAMEBV 0
#define ind_DAMEBH 1
#define ind_PIONBV 2
#define ind_PIONBH 3
#define ind_ROIB   4
#define ind_DAMENV 5
#define ind_DAMENH 6
#define ind_PIONNV 7
#define ind_PIONNH 8
#define ind_ROIN   9

#define BOARD "images/Board.bmp"
#define DAMEBV "images/DameB.bmp"
#define DAMEBH "images/Dame2B.bmp"
#define PIONBV "images/PionB.bmp"
#define PIONBH "images/Pion2B.bmp"
#define ROIB   "images/RoiB.bmp"
#define DAMENV "images/Dame.bmp"
#define DAMENH "images/Dame2.bmp"
#define PIONNV "images/Pion.bmp"
#define PIONNH "images/Pion2.bmp"
#define ROIN "images/Roi.bmp"
#define MENU   "images/bulltricker_menu.bmp"
#define CREDITS "images/Credits.bmp"
#define BLACK_WIN "images/Black_win.bmp"
#define WHITE_WIN "images/White_win.bmp"
#define ICON "images/icon.bmp"
#define TN "images/tour_noire.bmp"
#define TB "images/tour_blanche.bmp"
#define SAVE "images/save.bmp"
#define LARG_FENETRE 648
#define HAUT_FENETRE 648

typedef struct Point
{
    int x;
    int y;
} Point;

SDL_Texture * CreateTexture(const char * ,SDL_Renderer *);
void SDL_DestroywindowEtrender(SDL_Window *,SDL_Renderer *);
void SDL_ExitErreur(char * );
void SDL_ChargementTexture(SDL_Window * ,SDL_Renderer*  ,SDL_Texture * ,SDL_Rect *);
void SDL_AfficherTexture(SDL_Window * ,SDL_Renderer*  ,SDL_Texture * ,SDL_Rect *,int ,int ); // fonction qui affiche la texture chargée

void DisplayCompulsoryPieces(SDL_Renderer*,position *,Point **,piece **); // fonction qui va colorier les pièces qui ont une capture obligatoire.
void display(piece **,SDL_Renderer* ,SDL_Rect *,Point **,SDL_Window *,SDL_Texture **,position *); // fonction qui gère l'affichage du plateau
#endif
