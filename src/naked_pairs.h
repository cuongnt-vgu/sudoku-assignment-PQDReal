#pragma once

#include "sudoku.h"

// Declare functions related to naked pairs
int naked_pairs(SudokuBoard *p_board);

typedef struct {
    Cell *p_cells[2];
    int values[2];
} NakedPair;

