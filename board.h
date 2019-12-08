#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED


#define PION 'p'
#define DAME 'd'
#define ROI 'R'
#define BLANCHE 'B'
#define NOIRE 'N'
#define DIM_PLAT 7

typedef struct piece{
    char *type;
    char *color;
}piece;

typedef struct carre{
    piece *up;
    piece *down;
    piece *left;
    piece *right;
    piece *roi;
} carre;

void initialplateau(carre **);
void affichage(carre **);
#endif // BOARD_H_INCLUDED