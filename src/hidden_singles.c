#include <stddef.h>
#include "hidden_singles.h"
#include "sudoku.h"

int hiddenSinglesCounter;

static void find_hidden_singles_in_unit(Cell **p_cells, int unit_size);

// Implement hidden singles logic here
int hidden_singles(SudokuBoard *p_board)
{
    hiddenSinglesCounter = 0;
    find_hidden_singles_in_unit(p_board->data, BOARD_SIZE);
    // Check rows
    /*
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
    */
    return hiddenSinglesCounter;
}

static void find_hidden_singles_in_unit(Cell **p_cells, int unit_size)
{
    for (int value = 1; value <= BOARD_SIZE; value++)
    {
        // Count occurrences of value in candidates
        int count = 0;
        Cell *candidateCell = NULL;

        for (int i = 0; i < unit_size - 1; i++) {
            for (int c = 0; c < p_cells[i]->num_candidates; c++) {
                for (int j = i + 1; j < unit_size; j++) {
                    if ((is_candidate(p_cells[i], p_cells[i]->candidates[c]) == 0) && 
                        ((j - i < 9 && is_candidate(p_cells[j], p_cells[i]->candidates[c]) == 0) || 
                        ((j - i) % 9 == 0 && is_candidate(p_cells[j], p_cells[i]->candidates[c]) == 0) || 
                        (j - i < 9 && (j - i) % 9 == 0 && is_candidate(p_cells[j], p_cells[i]->candidates[c]) == 0))) {
                        count++;
                        candidateCell = p_cells[i];
            }
        }
    }
}

        // If only one occurrence is found, it's a hidden single
        if (count == 1 && candidateCell != NULL)
        {
            hiddenSinglesCounter++;
        }
    }
}

