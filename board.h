#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED


#define PION 'p'
#define DAME 'd'
#define ROI 'R'
#define BLANCHE 'B'
#define NOIRE 'N'
#define N 7

typedef struct {
    char *type;
    char *color;
}piece;
typedef struct {
    piece *up;
    piece *down;
    piece *left;
    piece *right;
    piece *roi;
} carre;

void initiale(carre **);
void affichage(carre **);
#endif // BOARD_H_INCLUDED
