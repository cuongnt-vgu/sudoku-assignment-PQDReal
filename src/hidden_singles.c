#include <stddef.h>
#include "hidden_singles.h"
#include "sudoku.h"

int hiddenSinglesCounter;

static void find_hidden_singles_in_unit(Cell **p_cells, int unit_size);

// Implement hidden singles logic here
int hidden_singles(SudokuBoard *p_board)
{
    hiddenSinglesCounter = 0;
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_singles_in_unit(p_board->p_rows[i], BOARD_SIZE);
    }

    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_singles_in_unit(p_board->p_cols[i], BOARD_SIZE);
    }

    // Check boxes
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_singles_in_unit(p_board->p_boxes[i], BOARD_SIZE);
    }

    return hiddenSinglesCounter;
}

static void find_hidden_singles_in_unit(Cell **p_cells, int unit_size)
{
    for (int value = 1; value <= BOARD_SIZE; value++)
    {
        // Count occurrences of value in candidates
        int count = 0;
        Cell *candidateCell = NULL;

        for (int i = 0; i < unit_size; i++)
        {
            if (is_candidate(p_cells[i], value))
            {
                count++;
                candidateCell = p_cells[i];
            }
        }

        // If only one occurrence is found, it's a hidden single
        if (count == 1 && candidateCell != NULL)
        {
            hiddenSinglesCounter++;
        }
    }
}

