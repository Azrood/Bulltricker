#include <stdio.h>
#include <stdlib.h>

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