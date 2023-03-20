#include <stdio.h>
#include <stdlib.h>

#include "structBoard.h"
#include "filesFunctions.h"
#include "validateFunctions.h"
#include "showFunctions.h"
#include "toAllocate.h"
#include "solverFunctions.h"

#define TAM_AREA 3
#define TAM_SUDOKU 9
#define TAM_NAME_ARQ 30

#include "formatText.h"


int validateInputs(char *input, BOARD* sudoku, int *endGame)
{
    int numString = atoi(input); //Conversion string to int
    int numArea   = numString/1000;
    int numLin    = (numString/100) - (numArea * 10);
    int numCol    = (numString/10) - ((numString/100)*10);
    int num       = numString - ((numString/10) * 10);
    int isValid = 0;
    int soluble = 0;


    //Validate possibles numbers:
    if(numArea < 1 || numArea > 9){
        printf(BOLD(RED("Insira um valor válido para a área (1 à 9).\n")));
        return 0;
    }
    else if(numLin < 1 || numLin > 3){
        printf(BOLD(RED("Insira um valor válido para a linha (1 à 3).\n")));
        return 0;
    }

    else if(numCol < 1 || numCol > 3){
        printf(BOLD(RED("Insira um valor válido para a coluna (1 à 3).\n")));
        return 0;
    }

    else if(num < 1 || num > 9){
        printf(BOLD(RED("Insira um número válido para o Sudoku (1 à 9).\n")));
        return 0;
    }

    /*Subtract 1 to numArea, numLin and NumCol, to pass the position*/
    numArea -= 1; numLin -= 1; numCol -=1;

    isValid = validateNumInLinCol(num, numArea, numLin, numCol, sudoku);    //Validate of pos;

    //Insert Number in Sudoku
    if(isValid){
        sudoku[numArea].subArea[numLin][numCol] = num;
        saveSudoku(sudoku, "matriztemp.txt");           //File to solve verification
        FILE* arqTemp = fopen("matriztemp.txt", "r");   //
        soluble = createSudokuSolver(arqTemp, 0);

    /*Verify if Sudoku is impossible to solve */
        if(soluble == 0){
            printf(BOLD(BG_RED("\n\tO Sudoku não tem mais soluções! Infelizmente você perdeu!"))"\n");
            isValid = 2;
            fclose(arqTemp);
            remove("matriztemp.txt");   //Delete temporary File
        }
        fclose(arqTemp);
    }

    //Pass if win the game
    *endGame = isEndGame(sudoku);

    return isValid;
}



int validateNumInLinCol(int num, int numArea, int numLin, int numCol, BOARD* sudoku){
    int otherArea1Lin, otherArea2Lin;
    int otherArea1Col, otherArea2Col;

    if(sudoku[numArea].subArea[numLin][numCol] != 0){
        printf("Erro! A célula %d,%d da região %d já possui um valor\n", numLin + 1, numCol + 1, numArea + 1); 
        return 0;
    }

    //Areas for Horizontal verification
    if(numArea < 3){            //Areas 1, 2, 3. (POS: 0, 1, 2)
        otherArea1Col = numArea + 3;
        otherArea2Col = numArea + 6;
    } 
    else if(numArea < 6){       //Areas 4, 5, 6 (POS: 3, 4, 6) 
        otherArea1Col = numArea - 3;
        otherArea2Col = numArea + 3;
    }
    else{                       //Areas 7, 8, 9 (POS: 6, 7, 8) 
        otherArea1Col = numArea - 6;
        otherArea2Col = numArea - 3;
    }

    //Areas for Vertical verification
    if(numArea % 3 == 0){       //Areas 1, 4, 7 (POS: 0, 3, 6)
        otherArea1Lin = numArea + 1;
        otherArea2Lin = numArea + 2;
    }
    else if((numArea - 1) % 3 == 0){ //Areas 2, 5, 8 (POS: 1, 4, 7)
        otherArea1Lin = numArea - 1;
        otherArea2Lin = numArea + 1;
    }
    else{                           //Areas 3, 6, 9 (POS: 2, 5, 8)
        otherArea1Lin = numArea - 1;
        otherArea2Lin = numArea - 2;
    }

    for(int i = 0; i < 3; i++){ // Verify num in the different lines in the same Col
        if(num == sudoku[numArea].subArea[i][numCol] || num == sudoku[otherArea1Col].subArea[i][numCol] 
            || num == sudoku[otherArea2Col].subArea[i][numCol]){
            printf("Erro! A coluna %d já possui o valor %d\n", numCol + 1, num);  
            return 0; //Verificar se está correto
        }
    }

    for(int j = 0; j < 3; j++){ // Verify num in the different lines in the same Col
        if(num == sudoku[numArea].subArea[numLin][j] || num == sudoku[otherArea1Lin].subArea[numLin][j] 
            || num == sudoku[otherArea2Lin].subArea[numLin][j]){
            printf("Erro! A linha %d já possui o valor %d\n", numLin + 1, num); //Substituir por return 
            return 0;
        }
    }
    
    for(int i = 0; i < TAM_AREA; i++){ // Verify num in the subArea
        for (int j = 0; j < TAM_AREA; j++){
            if( num == sudoku[numArea].subArea[i][j] ){
                printf("Erro! A região %d já possui o valor %d\n", numArea + 1, num); 
                return 0;
            }
                
        }
        
    }


    return 1;
}

/* Verify if End Game*/
int isEndGame(BOARD* sudoku){
    int endOfSudoku = 1;
    int contArea;

    for(int contArea = 0; contArea < TAM_SUDOKU; contArea++){
        for(int i = 0; i < TAM_AREA; i++){
            for(int j = 0; j < TAM_AREA; j++)
            if(sudoku[contArea].subArea[i][j] == 0){
                endOfSudoku = 0;                        //Check if there is a null cell
            }
        }
    }

    /* If there are no null cells */
    if(endOfSudoku != 0){
        return 1;
    }

    return 0;
}