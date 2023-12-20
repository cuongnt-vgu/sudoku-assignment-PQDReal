#include <stddef.h>
#include "hidden_singles.h"
#include "sudoku.h"

int hiddenSinglesCounter;

static bool find_hidden_singles_in_unit(Cell **p_cells, int unit_size);

// Implement hidden singles logic here
int hidden_singles(SudokuBoard *p_board)
{
    hiddenSinglesCounter = 0;

    while (1)
    {
        int counter = 0;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (find_hidden_singles_in_unit(p_board->p_rows[i], BOARD_SIZE)) counter++;
            if (find_hidden_singles_in_unit(p_board->p_cols[i], BOARD_SIZE)) counter++;
            if (find_hidden_singles_in_unit(p_board->p_boxes[i], BOARD_SIZE)) counter++;
        }

        if (counter == 0)
        {
            break;
        }
    }

    return hiddenSinglesCounter;
}

static bool find_hidden_single_in_unit(Cell **p_cells, int unit_size)
{
    for (int value = 1; value <= BOARD_SIZE; value++)
    {
        // Count occurrences of value in candidates
        int count = 0;
        Cell *candidateCell = NULL;

        for (int i = 0; i < unit_size; i++)
        {
            if (!p_cells[i]->fixed && is_candidate(p_cells[i], value))
            {
                count++;
                candidateCell = p_cells[i];
            }
        }

        // If only one occurrence is found, it's a hidden single
        if (count == 1 && candidateCell != NULL)
        {
            // Apply the constraint to the hidden single
            apply_constraint(candidateCell, value);
            return true;
        }
    }

    return false;
}

