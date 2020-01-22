#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#define PION 'P'
#define DAME 'D'
#define ROI 'R'
#define BLANCHE 'b'
#define NOIRE 'n'
#define DIM_PLAT 15
#define INTERDIT '*'
#define VIDE 0

extern int played; // globale, qui permet de determiner si le tour d'un joueur est fini ou pas.

typedef struct piece {
    int type; //ROI DAME or PION
    int color; // BLANCHE or NOIRE
    int firstmove; /*initialisé à 1 pour les pions en horizontal
                0 pour les autres pièces 
                et devient 0 après le 1er move d'une pièce PION*/
}piece;

void initialplateau(piece **);
void affichage(piece **);
void save(piece **A);
void load(piece **A);

#endif // BOARD_H_INCLUDED
