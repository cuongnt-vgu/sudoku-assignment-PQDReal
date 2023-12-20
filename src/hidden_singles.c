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

static bool find_hidden_singles_in_unit(Cell **p_cells, int unit_size)
{
    for (int value = 1; value <= BOARD_SIZE; value++)
    {
        for (int i = 0; i < unit_size; i++)
        {
            if (!p_cells[i]->fixed)
            {
                for (int c = 0; c < p_cells[i]->num_candidates; c++)
                {
                    bool isHiddenSingle = true;

                    for (int j = 0; j < unit_size; j++)
                    {
                        if (i != j && !p_cells[j]->fixed)
                        {
                            for (int k = 0; k < p_cells[j]->num_candidates; k++)
                            {
                                // If a candidate in a non-fixed square matches the candidate in the current cell,
                                // it's not a hidden single
                                if (p_cells[j]->candidates[k] == p_cells[i]->candidates[c])
                                {
                                    isHiddenSingle = false;
                                    break;
                                }
                            }
                        }
                    }

                    if (isHiddenSingle)
                    {
                        p_cells[i]->value = p_cells[i]->candidates[c];
                        unset_candidate(p_cells[i], value);
                        hiddenSinglesCounter++;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

