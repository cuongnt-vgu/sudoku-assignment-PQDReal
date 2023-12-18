#include "naked_pairs.h"
#include "sudoku.h"

#include <string.h>

static void find_naked_pairs_in_unit(Cell **p_cells, int unit_size);

// Implement naked pairs logic here
int naked_pairs(SudokuBoard *p_board)
{
    int nakedPairsCounter = 0;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pairs_in_unit(p_board->p_rows[i], BOARD_SIZE);
    }

    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pairs_in_unit(p_board->p_cols[i], BOARD_SIZE);
    }

    // Check boxes
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pairs_in_unit(p_board->p_boxes[i], BOARD_SIZE);
    }

    return nakedPairsCounter;
}

static void find_naked_pairs_in_unit(Cell **p_cells, int unit_size)
{
    // Iterate through each pair of cells
    for (int i = 0; i < unit_size - 1; i++)
    {
        for (int j = i + 1; j < unit_size; j++)
        {
            // Check if both cells have exactly two candidates
            if (p_cells[i]->num_candidates == 2 && p_cells[j]->num_candidates == 2)
            {
                // Check if the candidates in both cells are the same
                if (memcmp(p_cells[i]->candidates, p_cells[j]->candidates, BOARD_SIZE * sizeof(int)) == 0)
                {
                    // Naked pair found, remove candidates from other cells in the unit
                    for (int k = 0; k < unit_size; k++)
                    {
                        if (k != i && k != j)
                        {
                            for (int value = 1; value <= BOARD_SIZE; value++)
                            {
                                if (p_cells[i]->candidates[value - 1])
                                {
                                    apply_constraint(&p_cells[k], value);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}