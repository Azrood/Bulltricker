#include <stdio.h>
#include <stdlib.h>

#define ROI "k"
#define PION "p"
#define REINE "r"
#define N 7

typedef struct rect {
    char piece;
};

typedef struct case {
    rect *up;
    rect *down;
    rect *left;
    rect *right;
    int roi;
};