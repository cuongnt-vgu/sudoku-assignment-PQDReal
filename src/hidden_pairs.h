#pragma once

#include "sudoku.h"

int hidden_pairs(SudokuBoard *p_board);
int has_same_candidates(const int *candidates1, const int *candidates2);

typedef struct {
    Cell *p_cells[2];  // Pointer to the cell where the hidden single is found
    int value[2];           // The value of the hidden single
} HiddenPair;