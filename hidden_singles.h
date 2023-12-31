#pragma once

#include "sudoku.h"

// Declare functions related to hidden singles
int hidden_singles(SudokuBoard *p_board);

typedef struct {
    Cell *p_cell;  // Pointer to the cell where the hidden single is found
    int value;           // The value of the hidden single
} HiddenSingle;


