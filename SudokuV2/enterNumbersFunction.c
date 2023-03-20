#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "filesFunctions.h"
#include "structBoard.h"
#include "validateFunctions.h"
#include "cleanfree.h"
#include "enterNumbersFunctions.h"
#include "showFunctions.h"
#include "formatText.h"

#define TAM_NAME_ARQ 30

/* Insert a number in sudoku */
int insertNumber(BOARD* sudoku)
{
    char input[6];
    int validInput = 0;
    int isEndGame;
    while (!validInput)
    {
        printf("Digite um comando ou indique a celula a alterar: ");
        scanf("%s", input);
        cleanBuffer();

        int i = 0;
        while (i < 6)   // 6 -> tam String
        {
            input[i] = toupper(input[i]);   //Anti case sensitive
            i++;
        }
        if (!(strcmp(input, "SALVAR"))){    //To save option
            char nameArq[TAM_NAME_ARQ];
            printf(YELLOW("Digite o nome do arquivo: "));
            scanf("%s", nameArq);
            cleanBuffer();

            saveSudoku(sudoku, nameArq);
            printf(YELLOW("Jogo foi salvo em %s\n"), nameArq);
            return 1;
        }

        else if (!(strcmp(input, "VOLTAR")))
        {
            return 2;
        }
        else
        {
            validInput = validateInputs(input, sudoku, &isEndGame);

            /* Verify if End of Game */
            if(isEndGame){
                printf(BOLD(BG_GREEN("\nPARABÉNS! VOCÊ VENCEU O SUDOKU"))"\n");
                printf(YELLOW("Digite \"voltar\" para iniciar novo jogo ou sair do Sudoku."));
            }

        }
    }

    showSudoku(sudoku);

    return validInput;
}

