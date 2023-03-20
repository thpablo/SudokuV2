#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>  //toUpper

#include "solverFunctions.h"
#include "toAllocate.h"
#include "cleanfree.h"
#include "filesFunctions.h"
#include "formatText.h"

#define TAM_AREA 3
#define TAM_SUDOKU 9
#define MATRIZ_RAND_NAME "matrizRAND.txt"


/*Create 2D Array with sudoku solved to matriztemp.txt (arqtemp)*/

int createSudokuSolver(FILE* arqtemp, int showRes){
    /* Create sudokuTemp (2D Array 9x9) */
    int** sudokutemp = toAllocateAreas(9, 9); //it's easier to work with her

    /* Pass the temporary file with sudoku */
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fscanf(arqtemp, "%d", &sudokutemp[i][j]);
        }
    }

    int haveSolution = solveSudoku(sudokutemp);

    if(haveSolution == 0){   //Not Solution
        return 0;
    }

    //With Solution:

    if(showRes){
        printf(GREEN(BOLD("Uma solucão para o jogo seria:"))"\n\n");

        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                printf(" %d ", sudokutemp[i][j]);
                if( (j  + 1) % 3 == 0 ) printf("\t");
            }
            printf("\n");
            if( (i + 1) % 3 == 0 ) printf("\n");
        }
    }
          

    /* Free Sudoku Temp */
    for(int i = 0; i < TAM_AREA; i++)
        free(sudokutemp[i]);
    
    free(sudokutemp);

    return 1;
}

/*Recursive backtracking */

int solveSudoku(int** sudokutemp){

    int line, column;
    if(findZero(sudokutemp, &line, &column) == 0){  //Search cells with 0
        return 1;        
    }

    for(int num = 1; num <= 9; num++){              //Tests number 1 - 9
        if(valid(sudokutemp, line, column, num))    //If number is valid
        {
            sudokutemp[line][column] = num;         //Cell with number
            if(solveSudoku(sudokutemp)){            //Recursive confirmation
                return 1;
            }
            else                                    //If not solution, backtracking. Cell = 0
                sudokutemp[line][column] = 0;
        }
    }
    
    return 0;

}

/* Find zero in sudoku */

int findZero(int** sudokutemp, int* row, int* col){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(sudokutemp[i][j] == 0){
                *row = i;           // Pass row and col than with Zero
                *col = j;           // to test numbers
                return 1;
            }
        }
    }
 
    /* If dont have more cels with 0 */
    return 0;
}

/* Test number in line, column and subArea */

int valid(int** sudokutemp, int lin, int col, int num){

    /* Verify in same col */
    for(int i = 0; i < 9; i++){
        if(sudokutemp[i][col] == num){
            return 0;
        }
    }
    
    /* Verify in same line */
    for(int i = 0; i < 9; i++){
        if(sudokutemp[lin][i] == num){
            return 0;
        }
    }

    /* Verify in same subArea*/

    int linS = lin/3;   //If 0, 1, 2 -> linS = 0 |  If 3, 4, 5 -> linS = 1 | If 6, 7, 8 -> linS = 2;
    int colS = col/3;   //If 0, 1, 2 -> colS = 0 |  If 3, 4, 5 -> colS = 1 | If 6, 7, 8 -> colS = 2;

    for(int i = linS * 3; i < linS * 3 + 3; i++){
       for(int j = colS * 3; j < colS * 3 + 3; j++){
            if(sudokutemp[i][j] == num && (j != colS || i != linS)){
                return 0;
            }
        }
    }

    /* If Valid */
    return 1;

}


/* Create Random Sudoku board */

void createRandomSudoku(BOARD* sudoku){
    srand(time(NULL));
    char c;
    int isSolvable = 0, quantCells, isValid = 0;
    int num;
    int POSX, POSY;

    int** sudokuRAND = toAllocateAreas(TAM_SUDOKU, TAM_SUDOKU);

    FILE* arq = fopen(MATRIZ_RAND_NAME, "w+");  //File with randSudoku

    /* NOT WORKING
    printf("Escolha modo Fácil (F) ou difícil (D)\n");

    scanf("%c", &c);
    cleanBuffer();

    c = toupper(c);
    
    while( c != 'F' && c != 'D'){
        printf("Escolha uma opção válida\n");
        printf("Escolha modo Fácil (F) ou difícil (D)\n");
        scanf("%c", &c);
        cleanBuffer();
        c = toupper(c);
    }
    */
    quantCells = rand() % 6 + 1;     //Rand quantity of cells 

    /*
    if( c == 'F' ){
        quantCells = quantCells + 3; //(4, 5, 6)
    } */

    while(!isSolvable){     
        for(int i = 0; i < 9; i++){                          /* Start with null values*/
            for(int j = 0; j < 9; j++){
                sudokuRAND[i][j] = 0;
            }
        }
        for(int j = 0; j < quantCells; j++){                /* Random values for random cells */
            for(int i = 0; i < 9; i++){
                isValid = 0;
                while(!isValid){
                    POSX = ((i % 3) * 3) + (rand() % 2);
                    POSY = ((i / 3) * 3) + (rand() % 2);
                    num = rand() % 9 + 1;

                    if(valid(sudokuRAND, POSX, POSY, num)){     
                        isValid = 1;                        /* Valid Position */
                        sudokuRAND[POSX][POSY] = num;
                    }   
                    else                                    /* If not Valid */
                        isValid = 0;
                }
            }
        }

        rewind(arq);

        for(int l = 0; l < 9; l++){                 /* Pass 2D Sudoku Random for matrizRAND.txt */
            for (int m = 0; m < 9; m++){
                fprintf(arq, " %d ", sudokuRAND[l][m]); 
            }
            fprintf(arq, "\n");
        }
        rewind(arq);        
        isSolvable = createSudokuSolver(arq, 0);    /* Checks if is Solvable using matrizRAND.txt */
    }

    upload_2DArray(&sudoku, MATRIZ_RAND_NAME);      /* Pass the Random 2D Array to Board* sudoku */

    /* Free sudokuRand */
    for(int i = 0; i < TAM_AREA; i++)
        free(sudokuRAND[i]);
    
    free(sudokuRAND);

    fclose(arq);
    remove(MATRIZ_RAND_NAME);   //Delete file with rand sudoku
}
