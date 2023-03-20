#include <stdlib.h>
#include <stdio.h>
#include "filesFunctions.h"
#include "cleanfree.h"
#include "showFunctions.h"
#include "structBoard.h"
#include "formatText.h"


#define TAM_AREA 3
#define TAM_SUDOKU 9
#define TAM_NAME_ARQ 30


void upload_2DArray(BOARD **sudoku, char* arqName){ //retornar a matriz do arquivo
    char c;
    int indexArea = 0, sumIndexArea = 0, lin = 0, col = 0, contNumbersInThreeAreas = 1;

    FILE* arq = fopen(arqName, "r");
    while(arq == NULL){
        printf(BOLD(RED("Arquivo não encontrado ou nome incorreto.\n")));
        printf("Indique o arquivo texto contendo o jogo: ");
        scanf("%s", arqName);
        cleanBuffer();
        arq = fopen(arqName, "r");
    }
    FILE* arqTemp = fopen("matriztemp.txt", "w+");    
    while(!feof(arq)){
        c = fgetc(arq);

        /* Copy arq to arqtemp */
        if(c != EOF )
            fprintf(arqTemp, "%c", c);

        /* Pass numbers to sudoku*/
       if(c >= 48 && c <= 57){          //If c its a number
            int cInt;
            sscanf(&c, "%d", &cInt);    //Conversion char c to int lin
            (*sudoku)[indexArea].subArea[lin][col] =  cInt;
            if( (col + 1) == 3){        //If in the 3rd column -> col = -1. col++ at the end -> col = 0;
                col = -1;     
                indexArea++;
            }

            if(contNumbersInThreeAreas % 9 == 0){ //If at the end of line
                lin++;
                indexArea -= 3;
            }

            if(contNumbersInThreeAreas == 27){  //If at the end of the 3rd Area
                sumIndexArea++;
                indexArea = (2 * sumIndexArea) + (1 * sumIndexArea);
                lin = 0;
                contNumbersInThreeAreas = 0;
            }

            col++;
            contNumbersInThreeAreas++; //contNumbersInThreeAreas goes from 1 to 27 (9*3 -quantity of numbers in 3 sub Areas )
        }  
    }

    fclose(arq);
    fclose(arqTemp);
}


void saveSudoku(BOARD* sudoku, char* nameArq){

    FILE* arqSave;

    arqSave = fopen(nameArq, "w+");

    while(arqSave == NULL){
        printf("Não foi possível criar o arquivo para salvar o arquivo. Tente novamente.\n");
        printf("Digite o nome do arquivo: ");
        scanf("%s", nameArq);
        cleanBuffer();

        arqSave = fopen(nameArq, "w+");
    }

    for (int i = 0; i < TAM_AREA; i++)
    {
        for (int j = 0; j < TAM_AREA; j++)
        {
            for (int k = 0; k < TAM_AREA; k++)
            {
                fprintf(arqSave, " %d ", sudoku[j].subArea[i][k]);
            }
            fprintf(arqSave, " ");
        }
        fprintf(arqSave, "\n");
    }
    fprintf(arqSave, "\n");

    for (int i = 0; i < TAM_AREA; i++)
    {
        for (int j = 3; j < 6; j++)
        {
            for (int k = 0; k < TAM_AREA; k++)
            {
                fprintf(arqSave, " %d ", sudoku[j].subArea[i][k]);
            }
            fprintf(arqSave, " ");
        }
        fprintf(arqSave, "\n");
    }
    fprintf(arqSave, "\n");

    for (int i = 0; i < TAM_AREA; i++)
    {
        for (int j = 6; j < 9; j++)
        {
            for (int k = 0; k < TAM_AREA; k++)
            {
                fprintf(arqSave, " %d ", sudoku[j].subArea[i][k]);
            }
            fprintf(arqSave, " ");
        }
        fprintf(arqSave, "\n");
    }
    fprintf(arqSave, "\n");


    fclose(arqSave);
}
