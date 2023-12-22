#include <stddef.h>
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
    for (int i = 0; i < unit_size; i++)
    {
        for (int j = 0; j < unit_size; j++)
        {
            if (!p_board->p_rows[i][j]->fixed)
            {
                for (int c = 0; c < unit_size; c++)
                {
                    bool match_fixed = true;
                    bool isHiddenSingle_r = false;
                    bool isHiddenSingle_c = false;
                    bool isHiddenSingle_b = false;
                    if (p_board->p_rows[i][j]->candidates[c] == 1)
                    {
                        for (int u = 0; u < unit_size; u++)
                        {
                            int count_r = 0;
                            for (int d = 0; d < unit_size; d++)
                            {
                                if (p_board->p_rows[i][u]->candidates[d] == 1 && d == c)
                                {
                                    count_r++;
                                }
                            if (count_r == 1)
                            {
                                isHiddenSingle_b = true;
                                hs_counter++;
                                break;
                            }
                            else
                            {
                                int count_c = 0;
                                for (int e = 0; e < unit_size; e++)
                                {
                                    if (p_board->p_cols[i][u]->candidates[e] == 1 && e == c) count_c++;
                                }
                                if (count_c == 1)
                                {
                                    isHiddenSingle_b = true;
                                    hs_counter++;
                                    break;
                                }
                                else
                                {
                                    int count_b = 0;
                                    for (int f = 0; f < unit_size; f++)
                                    {
                                        if (p_board->p_boxes[i][u]->candidates[f] == 1 && f == c) count_b++;
                                    }
                                    if (count_b == 1)
                                    {
                                        isHiddenSingle_b = true;
                                        hs_counter++;
                                        break;
                                    }
                                }
                                }
                            }
                        }
                        Cell *r_pos = p_board->p_rows[0][0];
                        if (isHiddenSingle_r)
                        {
                            r_pos = p_board->p_rows[i][j];
                            for (int q = 0; q < unit_size; q++)
                            {
                                if (q != c)
                                {
                                    p_board->p_rows[i][j]->candidates[q] = 0;
                                }
                            }
                            //p_board->p_rows[i][j]->num_candidates = 1;
                            p_board->p_rows[i][j]->fixed = true;
                        }
                        else if (isHiddenSingle_c)
                        {
                            r_pos = p_board->p_cols[i][j];
                            for (int q = 0; q < unit_size; q++)
                            {
                                if (q != c)
                                {
                                    p_board->p_cols[i][j]->candidates[q] = 0;
                                }
                            }
                            //p_board->p_rows[i][j]->num_candidates = 1;
                            p_board->p_cols[i][j]->fixed = true;
                        }
                        else if (isHiddenSingle_b)
                        {
                            r_pos = p_board->p_boxes[i][j];
                            for (int q = 0; q < unit_size; q++)
                            {
                                if (q != c)
                                {
                                    p_board->p_boxes[i][j]->candidates[q] = 0;
                                }
                            }
                            //p_board->p_rows[i][j]->num_candidates = 1;
                            p_board->p_rows[i][j]->fixed = true;
                        }

                        if (isHiddenSingle_r || isHiddenSingle_c || isHiddenSingle_b)
                        {
                            for (int a = 0; a < unit_size; a++)
                            {
                                for (int m = 0; m < unit_size; m++)
                                {
                                    if (p_board->p_rows[i][a]->candidates[m] == 1 && m == c && !p_board->p_rows[i][a]->fixed
                                     && p_board->p_rows[i][a]->row_index != r_pos->row_index &&  p_board->p_rows[i][a]->col_index != r_pos->col_index)
                                    {
                                        p_board->p_rows[i][a]->candidates[m] = 0;
                                        p_board->p_rows[i][a]->num_candidates -= 1;
                                    }
                                }
                            }
                            for (int b = 0; b < unit_size; b++)
                            {
                                for (int n = 0; n < unit_size; n++)
                                {
                                    if (p_board->p_cols[i][b]->candidates[n] == 1 && n == c && !p_board->p_cols[i][b]->fixed
                                     && p_board->p_cols[i][b]->row_index != r_pos->row_index &&  p_board->p_cols[i][b]->col_index != r_pos->col_index)
                                    {
                                        p_board->p_cols[i][b]->candidates[n] = 0;
                                        p_board->p_cols[i][b]->num_candidates -= 1;
                                    }
                                }
                            }
                            for (int e = 0; e < unit_size; e++)
                            {
                                for (int r = 0; r < unit_size; r++)
                                {
                                    if (p_board->p_boxes[i][e]->candidates[r] == 1 && r == c && !p_board->p_boxes[i][e]->fixed
                                     && p_board->p_boxes[i][e]->row_index != r_pos->row_index &&  p_board->p_boxes[i][e]->col_index != r_pos->col_index)
                                    {
                                        p_board->p_boxes[i][e]->candidates[r] = 0;
                                        p_board->p_boxes[i][e]->num_candidates -= 1;
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
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