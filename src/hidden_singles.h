#pragma once

#include "sudoku.h"

// find hidden single cells in a board, return the number of hidden single cells
int hidden_singles(SudokuBoard *p_board);

typedef struct {
    Cell *p_cell;  // Pointer to the cell where the hidden single is found
    int value;           // The value of the hidden single
} HiddenSingle;