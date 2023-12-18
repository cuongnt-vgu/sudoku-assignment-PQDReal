#pragma once

#include "sudoku.h"

int hidden_pairs(SudokuBoard *p_board);
int has_same_candidates(const int *candidates1, const int *candidates2);
