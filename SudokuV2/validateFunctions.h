#ifndef VALIDATE_FUNCTIONS_H
#define VALIDATE_FUNCTIONS_H

#include "structBoard.h"

int validateInputs( char*, BOARD*, int* );
int validateNumInLinCol(int , int , int , int , BOARD* );
int isEndGame(BOARD* );

#endif