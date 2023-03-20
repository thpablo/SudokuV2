#include "cleanfree.h"
#include <stdlib.h>
#include <stdio.h>

#define TAM_AREA 3
#define TAM_SUDOKU 9

void freeAll(BOARD **arrayToFree)
{ 
    /* Free columns in 2D subArea */
    for (int i = 0; i < TAM_SUDOKU; i++)
    {
        for (int j = 0; j < TAM_AREA; j++)
        {
            free((*arrayToFree)[i].subArea[j]);
        }
    }

    /*Free array subArea */
    for (int i = 0; i < TAM_SUDOKU; i++)
        free((*arrayToFree)[i].subArea);

    /* Free struct Board */
    free(*arrayToFree);
}

void cleanBuffer(){
    char buffer;
    do{
        buffer = fgetc(stdin); //Clean characters in the buffer.
    } while(buffer != '\n');
}
