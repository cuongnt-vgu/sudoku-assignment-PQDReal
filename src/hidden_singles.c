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
    int *x_pos = (int*)malloc(unit_size*unit_size*sizeof(int));
    int *y_pos = (int*)malloc(unit_size*unit_size*sizeof(int));
    int *val = (int*)malloc(unit_size*unit_size*sizeof(int));
    for (int i = 0; i < unit_size; i++)
    {
        for (int j = 0; j < unit_size; j++)
        {
            if (!p_board->p_rows[i][j]->fixed)
            {
                for (int c = 0; c < unit_size; c++)
                {
                    bool found_r = false;
                    bool found_c = false;
                    bool found_b = false;
                    if (p_board->p_rows[i][j]->candidates[c] == 1)
                    {
                        for (int u = 0; u < unit_size; u++)
                        {
                            for (int d = 0; d < unit_size; d++)
                            {
                                if (p_board->p_rows[i][u]->fixed == false && p_board->p_rows[i][u]->candidates[d] == 1 && d == c && j != u)
                                {
                                    found_r = true;
                                }
                                else if (p_board->p_rows[u][j]->fixed == false && p_board->p_rows[u][i]->candidates[d] == 1 && d == c && u != i)
                                {
                                    found_c = true;
                                }
                                else if (p_board->p_boxes[i][u]->fixed == false && p_board->p_boxes[i][u]->candidates[d] == 1 && d == c && j != u)
                                {
                                    found_b = true;
                                }
                            }
                        }
                        if (!found_r || !found_c || found_b)
                        {
                            x_pos[hs_counter] = i;
                            y_pos[hs_counter] = j;
                            val[hs_counter] = c;
                            hs_counter++;
                            break;
                        }
                        /*
                        if (!isHiddenSingle_r)
                        {
                            found_c = false;
                            isHiddenSingle_c = false;
                            for (int v = 0; v < unit_size; v++)
                            {
                                for (int e = 0; e < unit_size; e++)
                                {
                                    if (p_board->p_rows[v][j]->fixed == false && p_board->p_rows[v][j]->candidates[e] == 1 && e == c && i != v)
                                    {
                                        found_c = true;
                                    }
                                }
                            }
                            if (!found_c)
                            {
                                x_pos[hs_counter] = i;
                                y_pos[hs_counter] = j;
                                val[hs_counter] = c;
                                isHiddenSingle_c = true;
                                hs_counter++;
                            }
                        }
                        if (!isHiddenSingle_c)
                        {
                            found_b = false;
                            isHiddenSingle_b = false;
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
                            if (!found_b)
                            {
                                x_pos[hs_counter] = i;
                                y_pos[hs_counter] = j;
                                val[hs_counter] = c;
                                isHiddenSingle_b = true;
                                hs_counter++;
                            }
                        }
                        */
                    }
                }
            }
        }
    }
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