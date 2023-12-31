#pragma once

#include "sudoku.h"

// Declare functions related to hidden singles
int hidden_pairs(SudokuBoard *p_board);

typedef struct {
    Cell *p_cell_1;  // Pointer to the cell where the hidden single is found
    Cell *p_cell_2; 
    int value1;           // The value of the hidden single
    int value2;
} HiddenPair;