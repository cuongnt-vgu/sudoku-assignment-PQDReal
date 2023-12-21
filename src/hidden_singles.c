#include <stddef.h>
#include "hidden_singles.h"
#include "sudoku.h"

int hiddenSinglesCounter;
static int hiddenSinglesCounter_current = 0;

static bool find_hidden_singles_in_unit(SudokuBoard *p_board, Cell **p_cells, int unit_size);

// Implement hidden singles logic here
int hidden_singles(SudokuBoard *p_board)
{
    while (1)
    {
        hiddenSinglesCounter = 0;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (find_hidden_singles_in_unit(p_board, p_board->p_rows[i], BOARD_SIZE)) hiddenSinglesCounter++;
            if (find_hidden_singles_in_unit(p_board, p_board->p_cols[i], BOARD_SIZE)) hiddenSinglesCounter++;
            if (find_hidden_singles_in_unit(p_board, p_board->p_boxes[i], BOARD_SIZE)) hiddenSinglesCounter++;
        }

        if (hiddenSinglesCounter == 0)
        {
            break;
        }
    }
    hiddenSinglesCounter_current += hiddenSinglesCounter;

    return hiddenSinglesCounter_current;
}

static bool find_hidden_singles_in_unit(SudokuBoard *p_board, Cell **p_cells, int unit_size)
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
                    p_cells[i]->fixed = true;
                    int value = p_cells[i]->candidates[c];
                    for (int s = 0; s < p_cells[i]->num_candidates; s++)
                    {
                        if (s != c)
                        {
                            p_cells[i]->candidates[s] = 0;
                        }
                    }

                    int r = p_cells[i]->row_index;
                    for (int a = 0; a < unit_size; a++)
                    {
                        for (int m = 0; m < p_board->p_rows[r][a]->num_candidates; m++)
                        {
                            if (p_board->p_rows[r][a]->candidates[m] == value)
                                p_board->p_rows[r][a]->candidates[m] = 0;
                        }
                    }

                    int t = p_cells[i]->col_index;
                    for (int d = 0; d < unit_size; d++)
                    {
                        for (int n = 0; n < p_board->p_cols[r][d]->num_candidates; n++)
                        {
                            if (p_board->p_cols[t][d]->candidates[n] == value)
                                p_board->p_cols[t][d]->candidates[n] = 0;
                        }
                    }

                    int b = p_cells[i]->box_index;
                    for (int f = 0; f < unit_size; f++)
                    {
                        for (int p = 0; p < p_board->p_boxes[b][f]->num_candidates; p++)
                        {
                            if (p_board->p_boxes[b][f]->candidates[p] == value)
                                p_board->p_boxes[b][f]->candidates[p] = 0;
                        }
                    }
                    return true;
                }
            }
        }
    }

    return false;
}