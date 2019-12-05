#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#define PION 'p'
#define DAME 'd'
#define N 7

typedef struct {
    char *up;
    char *down;
    char *left;
    char *right;
    int roi;
} carre;

void initiale(carre **);
void affichage(carre **);

#endif
