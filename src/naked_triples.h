#pragma once

#include "sudoku.h"

// Declare functions related to naked pairs
int naked_triples(SudokuBoard *p_board);

typedef struct {
    Cell *p_cells[3];
    int values[3];
} NakedTriple;

