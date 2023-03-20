#ifndef SOLVER_H
#define SOLVER_H
#include "structBoard.h"

int solveSudoku(int**);
int findZero(int**, int*, int* );
int valid(int** , int, int , int);
int createSudokuSolver(FILE*, int);
void createRandomSudoku(BOARD* );
void createRandomSudoku(BOARD* sudoku); 

#endif