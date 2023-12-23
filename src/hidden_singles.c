#include <stdlib.h>
#include "hidden_singles.h"
#include "sudoku.h"
#include <string.h>

static int find_hidden_singles_in_unit(SudokuBoard *p_board, int unit_size);

// Implement hidden singles logic here
int hidden_singles(SudokuBoard *p_board)
{
    int hiddenSinglesCounter = 0;

    hiddenSinglesCounter = find_hidden_singles_in_unit(p_board, BOARD_SIZE);

    return hiddenSinglesCounter;
}

static int find_hidden_singles_in_unit(SudokuBoard *p_board, int unit_size)
{
    int hs_counter = 0;
    int index = 0;
    HiddenSingle *singles = malloc(0);
    for (int i = 0; i < unit_size; i++)
    {
        for (int c = 0; c < unit_size; c++)
        {
            int r_count = 0;
            for (int j = 0; j < unit_size; j++)
            {
                if (p_board->p_rows[i][j]->candidates[c] == 1)
                {
                    index = j;
                    r_count++;    
                }
            }
            if (r_count == 1)
            {
                HiddenSingle temp_single;
                temp_single.p_cell = p_board->p_rows[i][index];
                temp_single.value = c + 1;
                int already_checked = 0;
                for (int l = 0; l < hs_counter; l++)
                    if (singles[l].p_cell == temp_single.p_cell)
                        already_checked = 1;
                if (!already_checked)
                {
                    hs_counter++;
                    singles = realloc(singles, hs_counter * sizeof(HiddenSingle));
                    singles[hs_counter - 1] = temp_single;
                }
            }
        }
    }
    for (int a = 0; a < unit_size; a++)
    {
        for (int d = 0; d < unit_size; d++)
        {
            int c_count = 0;
            for (int b = 0; b < unit_size; b++)
            {
                if (p_board->p_cols[a][b]->candidates[d] == 1)
                {
                    index = b;
                    c_count++;
                }
            }
            if (c_count == 1)
            {
                HiddenSingle temp_single;
                temp_single.p_cell = p_board->p_cols[a][index];
                temp_single.value = d + 1;
                int already_checked = 0;
                for (int l = 0; l < hs_counter; l++)
                    if (singles[l].p_cell == temp_single.p_cell)
                        already_checked = 1;
                if (!already_checked)
                {
                    hs_counter++;
                    singles = realloc(singles, hs_counter * sizeof(HiddenSingle));
                    singles[hs_counter - 1] = temp_single;
                }
            }
        }
    }
    for (int m = 0; m < unit_size; m++)
    {
        for (int q = 0; q < unit_size; q++)
        {
            int b_count = 0;
            for (int n = 0; n < unit_size; n++)
            {
                if (p_board->p_rows[m][n]->candidates[q] == 1)
                {
                    index = n;
                    b_count++;    
                }
            }
            if (b_count == 1)
            {
                HiddenSingle temp_single;
                temp_single.p_cell = p_board->p_boxes[m][index];
                temp_single.value = q + 1;
                int already_checked = 0;
                for (int l = 0; l < hs_counter; l++)
                    if (singles[l].p_cell == temp_single.p_cell)
                        already_checked = 1;
                if (!already_checked)
                {
                    hs_counter++;
                    singles = realloc(singles, hs_counter * sizeof(HiddenSingle));
                    singles[hs_counter - 1] = temp_single;
                }
            }
        }
    }
/*
                    for (int w = (i / 3) * 3; w < (i / 3) * 3 + 3; w++)
                    {
                        for (int y = (j / 3) * 3; y < (j / 3) * 3 + 3; y++)
                        {
                            for (int f = 0; f < unit_size; f++)
                            {
                                if (p_board->p_rows[w][y]->fixed == false && p_board->p_rows[w][y]->candidates[f] == 1 && f == c && i != w && j != y)
                                {
                                    found_b = true;
                                }
                            }
                        }
                    }
                    if (!found_b || !found_c || !found_r)
                    {
                        x_pos[hs_counter] = i;
                        y_pos[hs_counter] = j;
                        val[hs_counter] = c;
                        hs_counter++;
                    }
                }
            }
            }
        }
    }
*/
    int *candidates = malloc(4);
    for (int i = 0; i < hs_counter; i++)
    {
        candidates[0] = singles[i].value;
        set_candidates(singles[i].p_cell, candidates, 1);
    }
    free(singles);
    free(candidates);
    return hs_counter;
}
/*
for (int fd = 0; fd < unit_size; fd++)
                                        {
                                            if (p_board->p_rows[i][fd]->fixed && p_board->p_rows[i][fd]->candidates[c] != 1)
                                            {
                                                match_fixed = true;
                                                break;
                                            }
                                            else
                                            {
                                                continue;
                                            }
                                        }
*/