#include <stdlib.h>
#include <stdio.h>

#define TAM_AREA 3
#define TAM_SUDOKU 9
#define TAM_NAME_ARQ 30

#include "structBoard.h"
#include "cleanfree.h"
#include "showFunctions.h"
#include "structBoard.h"
#include "filesFunctions.h"
#include "solverFunctions.h"
#include "validateFunctions.h" 
#include "formatText.h"

int showMenu(BOARD* sudoku)
{
    int op; //OP for switch of options
    char c; //c is converted for int
    char *trashSTDIN = " "; //for catch trash from stdin
    char arqName[TAM_NAME_ARQ];
    int resSolutionSudoku = 0;

    /* Remove trash from stdin */
    while(stdin == NULL)
            fscanf(stdin, "%s", trashSTDIN);
    
    printf(RED("0 Sair do jogo")"\n1 Gerar novo jogo\n2 Carregar jogo\n3 Resolver jogo\n\n"BG_WHITE(BOLD(BLUE("Digite sua opção:")))" ");

    scanf("%c", &c);
    cleanBuffer();  //Remove trash from Buffer;

    sscanf(&c, "%d", &op);

    while (op < 0 || op > 3)
    {
        printf(BOLD(RED("Opção inválida, escolha uma opção válida.\n")));

        printf(RED("0 Sair do jogo")"\n1 Gerar novo jogo\n2 Carregar jogo\n3 Resolver jogo\n\n"BG_WHITE(BOLD(BLUE("Digite sua opção:")))" ");
        scanf("%c", &c);
        cleanBuffer(); 

        sscanf(&c, "%d", &op);
    }
    switch(op){
        case 0:                 //Quit
            printf("Tchau!!!");
            remove("matriztemp.txt"); //Remove matriztemp.
            freeAll(&sudoku);
            exit(0);
        break;
        case 1:             //Random Sudoku
            createRandomSudoku(sudoku);
            printf("\n");
            printf(BOLD(BLUE("A Matriz aleatória foi gerada!")));
            showSudoku(sudoku);
            printf("\n");
            return 1;
        break;
        case 2:             //Upload sudoku
            printf("Indique o arquivo texto contendo o jogo: ");
            scanf("%s", arqName);
            cleanBuffer();
            upload_2DArray(&sudoku, arqName); 
            showSudoku(sudoku);
            return 1;
        break;
        case 3:             //Resolves sudoku
            FILE* arqTemp = fopen("matriztemp.txt", "r");   //MatrizTemp it's for save the current sudoku and use in solveSudoku
            if(arqTemp == NULL){
                printf(BOLD(RED("Não há nenhum Sudoku para solucionar"))"\n\n");
                return 2;
            }
            else{
                resSolutionSudoku = createSudokuSolver(arqTemp, 1); //Solve Sudoku

                if(!resSolutionSudoku)  //If unsolvable
                    printf(BOLD(BG_RED("\nO Sudoku não tem mais soluções! Infelizmente você perdeu!"))"\n");

                remove("matriztemp.txt"); //Remove matriztemp.
                fclose(arqTemp);
                return 2;
            }
        break;
    }
    return 0;
}

void showSudoku(BOARD *sudoku) {

    printf("\n");

    /* Show 1 - 3 Areas*/
    printf(TAB_TL);
    for(int i = 0; i < 27 + 7; i++)
        printf(TAB_HOR);
    printf(TAB_TR);
    printf("\n");
    for (int i = 0; i < TAM_AREA; i++)
    {
        printf(TAB_VER );
        for (int j = 0; j < TAM_AREA; j++)
        {
            for (int k = 0; k < TAM_AREA; k++)
            {
                printf(" %d ", sudoku[j].subArea[i][k]);
            }
            printf(" " TAB_VER " ");
        }
        printf("\n");
    }

    printf(TAB_ML);
    for(int i = 0; i < 27 + 7; i++)
        printf(TAB_HOR);
    printf(TAB_MR);
    printf("\n");

    /* Show 4 - 6 Areas*/
    for (int i = 0; i < TAM_AREA; i++)
    {
        printf(TAB_VER );
        for (int j = 3; j < 6; j++)
        {
            for (int k = 0; k < TAM_AREA; k++)
            {
                printf(" %d ", sudoku[j].subArea[i][k]);
            }
            printf(" " TAB_VER " ");
        }
        printf("\n");
    }
    
    printf(TAB_ML);
    for(int i = 0; i < 27 + 7; i++)
        printf(TAB_HOR);
    printf(TAB_MR);
    printf("\n");
   
    /* Show 7 - 9 Areas*/
    for (int i = 0; i < TAM_AREA; i++)
    {
        printf(TAB_VER );
        for (int j = 6; j < 9; j++)
        {
            for (int k = 0; k < TAM_AREA; k++)
            {
                printf(" %d ", sudoku[j].subArea[i][k]);
            }
            printf(" " TAB_VER " ");
        }
        printf("\n");
    }
    printf(TAB_BL);
    for(int i = 0; i < 27 + 7; i++)
        printf(TAB_HOR);
    printf(TAB_BR);
    printf("\n\n");
}

void showTitle(){
    printf(BOLD(CYAN("\n\t     Bem vindo ao\n"
   " _____ _    _ _____   ____  _  ___    _ \n" 
  "/ ____| |  | |  __ \\ / __ \\| |/ / |  | |\n"
 " (___ | |  | | |  | | |  | | ' /| |  | |\n"
  "\\___ \\| |  | | |  | | |  | |  < | |  | |\n"
  "____) | |__| | |__| | |__| | . \\| |__| |\n"
 "_____/ \\____/|_____/ \\____/|_|\\_\\______/\n\n")));

}