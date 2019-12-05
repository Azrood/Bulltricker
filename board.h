#include <stdio.h>
#include <stdlib.h>

#define ROI "k"
#define PION "p"
#define REINE "r"
#define N 7

typedef struct {
    char *up;
    char *down;
    char *left;
    char *right;
    int roi;
} carre;