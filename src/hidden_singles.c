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
    int *x_pos = malloc(unit_size*unit_size*sizeof(int));
    int *y_pos = malloc(unit_size*unit_size*sizeof(int));
    int *val = malloc(unit_size*unit_size*sizeof(int));
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
                x_pos[hs_counter] = i;
                y_pos[hs_counter] = index;
                val[hs_counter] = c;
                hs_counter++;
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
                x_pos[hs_counter] = a;
                y_pos[hs_counter] = index;
                val[hs_counter] = d;
                hs_counter++;
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
                x_pos[hs_counter] = m;
                y_pos[hs_counter] = index;
                val[hs_counter] = q;
                hs_counter++;
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
    for (int z = 0; z < hs_counter; z++)
    {
        for (int ae = 0; ae < unit_size; ae++)
        {
            p_board->p_rows[x_pos[z]][y_pos[z]]->candidates[ae] = 0;
        }
        p_board->p_rows[x_pos[z]][y_pos[z]]->candidates[val[z]] = 1;
        p_board->p_rows[x_pos[z]][y_pos[z]]->num_candidates = 1;
        p_board->p_rows[x_pos[z]][y_pos[z]]->fixed = true;
    }
    free(x_pos);
    free(y_pos);
    free(val);
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