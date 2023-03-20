#include "toAllocate.h"
#include <stdlib.h>

#define TAM_AREA 3
#define TAM_SUDOKU 9


BOARD *toAllocateSudoku()
{
    BOARD *boardAllocate;
    boardAllocate = malloc((TAM_SUDOKU) * sizeof(BOARD));

    return boardAllocate;
}

int **toAllocateAreas(int lin, int col)
{
    int **areaAllocate = malloc(lin * sizeof(int *));
    for (int i = 0; i < lin; i++)
        areaAllocate[i] = calloc(col, sizeof(int));

    return areaAllocate;
}