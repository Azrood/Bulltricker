#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED


#define PION 'P'
#define DAME 'D'
#define ROI 'R'
#define BLANCHE 'b'
#define NOIRE 'n'
#define DIM_PLAT 15
#define INTERDIT 3
#define VIDE 0

typedef struct piece {
    int type;
    int color;
}piece;

void initialplateau(piece **);
void affichage(piece **);
#endif // BOARD_H_INCLUDED