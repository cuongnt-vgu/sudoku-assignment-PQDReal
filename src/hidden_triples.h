#pragma once

#include "sudoku.h"

// Declare functions related to hidden singles
int hidden_triples(SudokuBoard *p_board);

typedef struct {
    Cell *p_cells[3];  // Pointer to the cell where the hidden single is found
    int values[3];           // The value of the hidden single
} HiddenTriple;

