#include "hidden_pairs.h"
#include "sudoku.h"

static void find_hidden_pairs_in_unit(Cell **p_cells, int unit_size);

// Implement hidden pairs logic here
int hidden_pairs(SudokuBoard *p_board)
{
    int hiddenPairsCounter = 0;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pairs_in_unit(p_board->p_rows[i], BOARD_SIZE);
    }

    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pairs_in_unit(p_board->p_cols[i], BOARD_SIZE);
    }

    // Check boxes
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pairs_in_unit(p_board->p_boxes[i], BOARD_SIZE);
    }

    return hiddenPairsCounter;
}

static void find_hidden_pairs_in_unit(Cell **p_cells, int unit_size)
{
    // Iterate through each pair of cells
    for (int i = 0; i < unit_size - 1; i++)
    {
        for (int j = i + 1; j < unit_size; j++)
        {
            // Check if both cells have the same two candidates
            if (p_cells[i]->num_candidates == 2 && p_cells[j]->num_candidates == 2 &&
                memcmp(p_cells[i]->candidates, p_cells[j]->candidates, BOARD_SIZE * sizeof(int)) == 0)
            {
                // Hidden pair found, remove other candidates from the unit
                for (int k = 0; k < unit_size; k++)
                {
                    if (k != i && k != j)
                    {
                        apply_constraint(&p_cells[k], p_cells[i]->candidates[0]);
                        apply_constraint(&p_cells[k], p_cells[i]->candidates[1]);
                    }
                }
            }
        }
    }
}
