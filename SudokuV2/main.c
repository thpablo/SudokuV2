#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //toUpper

#include "structBoard.h"
#include "toAllocate.h"
#include "cleanfree.h"
#include "showFunctions.h"
#include "filesFunctions.h"
#include "validateFunctions.h"
#include "enterNumbersFunctions.h"
#include "formatText.h"

#define TAM_SUDOKU 9
#define TAM_AREA 3



int main(){
    int isCurrentGame = 1;

    showTitle();    //Shows Sudoku Title :)

    /* Allocate the Array Sudoku */
    BOARD *sudoku = toAllocateSudoku();
    
    /* Allocate the Array subArea */
    for (int i = 0; i < (TAM_SUDOKU); i++)
        sudoku[i].subArea = toAllocateAreas(TAM_AREA, TAM_AREA);
        
    /* Menu */
    isCurrentGame = showMenu(sudoku);
    
    while(isCurrentGame){   //2 -> "Voltar" option
        if(isCurrentGame == 2)
            isCurrentGame = showMenu(sudoku);
        else
            isCurrentGame = insertNumber(sudoku);
    }


    /* Free All */
    freeAll(&sudoku);

    return 0;
}



