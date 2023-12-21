#include <stddef.h>
#include "hidden_singles.h"
#include "sudoku.h"
#include <string.h>

int hiddenSinglesCounter;
static int hiddenSinglesCounter_current = 0;

static bool find_hidden_singles_in_unit(SudokuBoard *p_board, char* text, int unit_size, int i);

// Implement hidden singles logic here
int hidden_singles(SudokuBoard *p_board)
{
    while (1)
    {
        hiddenSinglesCounter = 0;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (find_hidden_singles_in_unit(p_board, "row", BOARD_SIZE, i)) hiddenSinglesCounter++;
            if (find_hidden_singles_in_unit(p_board, "column", BOARD_SIZE, i)) hiddenSinglesCounter++;
            if (find_hidden_singles_in_unit(p_board, "box", BOARD_SIZE, i)) hiddenSinglesCounter++;
        }

        if (hiddenSinglesCounter == 0)
        {
            break;
        }
    }
    hiddenSinglesCounter_current += hiddenSinglesCounter;

    return hiddenSinglesCounter_current;
}

static bool find_hidden_singles_in_unit(SudokuBoard *p_board, char* text, int unit_size, int i)
{
    for (int j = 0; j < unit_size; j++)
    {
        if (strcmp(text, "row") == 0)
        {
            if (!p_board->p_rows[i][j]->fixed)
            {
                for (int c = 0; c < p_board->p_rows[i][j]->num_candidates; c++)
                {
                    bool isHiddenSingle = true;

                    for (int u = 0; u < unit_size; u++)
                    {
                        if (j != u && !p_board->p_rows[i][u]->fixed)
                        {
                            for (int k = 0; k < p_board->p_rows[i][u]->num_candidates; k++)
                            {
                                if (p_board->p_rows[i][u]->candidates[k] == p_board->p_rows[i][j]->candidates[c])
                                {
                                    isHiddenSingle = false;
                                    break;
                                }
                            }
                        }
                    }

                    if (isHiddenSingle)
                    {
                        int value = p_board->p_rows[i][j]->candidates[c];
                        p_board->p_rows[i][j]->value = p_board->p_rows[i][j]->candidates[c];
                        p_board->p_rows[i][j]->fixed = true;
                        p_board->p_rows[i][j]->num_candidates = 1;
                        /*
                        for (int s = 0; s < p_cells[i]->num_candidates; s++)
                        {
                            if (s != c)
                            {
                                p_cells[i]->candidates[s] = 0;
                            }
                        }
                        */

                        int r = i;//p_board->p_rows[i][j].row_index;
                        for (int a = 0; a < unit_size; a++)
                        {
                            int num_r = p_board->p_rows[r][a]->num_candidates;
                            for (int m = 0; m < num_r; m++)
                            {
                                if (p_board->p_rows[r][a]->candidates[m] == value)
                                {
                                    p_board->p_rows[r][a]->candidates[m] = 0;
                                    p_board->p_rows[r][a]->num_candidates -= 1;
                                }
                            }
                        }

                        int t = j;
                        for (int d = 0; d < unit_size; d++)
                        {
                            int num_c = p_board->p_rows[t][d]->num_candidates;
                            for (int n = 0; n < num_c; n++)
                            {
                                if (p_board->p_cols[d][t]->candidates[n] == value)
                                {
                                    p_board->p_cols[d][t]->candidates[n] = 0;
                                    p_board->p_cols[d][t]->num_candidates -= 1;
                                }
                            }
                        }

                        int b = (i / 3) * 3 + j / 3;
                        for (int f = 0; f < unit_size; f++)
                        {
                            int num_b = p_board->p_boxes[b][f]->num_candidates;
                            for (int p = 0; p < num_b; p++)
                            {
                                if (p_board->p_boxes[(b / 3) * 3 + f / 3][(b % 3) * 3 + f % 3]->candidates[p] == value)
                                {
                                    p_board->p_boxes[(b / 3) * 3 + f / 3][(b % 3) * 3 + f % 3]->candidates[p] = 0;
                                    p_board->p_boxes[(b / 3) * 3 + f / 3][(b % 3) * 3 + f % 3]->num_candidates -= 1;
                                }
                            }
                        }
                        return 1;
                    }
                }
            }
        }
        else if (strcmp(text, "column") == 0)
        {
            if (!p_board->p_cols[j][i]->fixed)
            {
                for (int c = 0; c < p_board->p_cols[j][i]->num_candidates; c++)
                {
                    bool isHiddenSingle = true;

                    for (int u = 0; u < unit_size; u++)
                    {
                        if (j != u && !p_board->p_cols[u][i]->fixed)
                        {
                            for (int k = 0; k < p_board->p_cols[u][i]->num_candidates; k++)
                            {
                                if (p_board->p_cols[u][i]->candidates[k] == p_board->p_cols[j][i]->candidates[c])
                                {
                                    isHiddenSingle = false;
                                    break;
                                }
                            }
                        }
                    }

                    if (isHiddenSingle)
                    {
                        int value = p_board->p_cols[j][i]->candidates[c];
                        p_board->p_cols[j][i]->value = p_board->p_cols[j][i]->candidates[c];
                        p_board->p_cols[j][i]->fixed = true;
                        p_board->p_cols[j][i]->num_candidates = 1;
                        /*
                        for (int s = 0; s < p_cells[i]->num_candidates; s++)
                        {
                            if (s != c)
                            {
                                p_cells[i]->candidates[s] = 0;
                            }
                        }
                        */

                        int v = i;
                        for (int a = 0; a < unit_size; a++)
                        {
                            int num_r = p_board->p_rows[v][a]->num_candidates;
                            for (int m = 0; m < num_r; m++)
                            {
                                if (p_board->p_rows[v][a]->candidates[m] == value)
                                {
                                    p_board->p_rows[v][a]->candidates[m] = 0;
                                    p_board->p_rows[v][a]->num_candidates -= 1;
                                }
                            }
                        }

                        int t = j;
                        for (int d = 0; d < unit_size; d++)
                        {
                            int num_c = p_board->p_rows[t][d]->num_candidates;
                            for (int n = 0; n < num_c; n++)
                            {
                                if (p_board->p_cols[d][t]->candidates[n] == value)
                                {
                                    p_board->p_cols[d][t]->candidates[n] = 0;
                                    p_board->p_cols[d][t]->num_candidates -= 1;
                                }
                            }
                        }

                        int b = (i / 3) * 3 + j / 3;
                        for (int f = 0; f < unit_size; f++)
                        {
                            int num_b = p_board->p_boxes[b][f]->num_candidates;
                            for (int p = 0; p < num_b; p++)
                            {
                                if (p_board->p_boxes[(b / 3) * 3 + f / 3][(b % 3) * 3 + f % 3]->candidates[p] == value)
                                {
                                    p_board->p_boxes[(b / 3) * 3 + f / 3][(b % 3) * 3 + f % 3]->candidates[p] = 0;
                                    p_board->p_boxes[(b / 3) * 3 + f / 3][(b % 3) * 3 + f % 3]->num_candidates -= 1;
                                }
                            }
                        }
                        return 1;
                    }
                }
            }
        }
        else if (strcmp(text, "box") == 0)
        {
            if (!p_board->p_boxes[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3]->fixed)
            {
                for (int c = 0; c < p_board->p_boxes[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3]->num_candidates; c++)
                {
                    bool isHiddenSingle = true;

                    for (int u = 0; u < unit_size; u++)
                    {
                        if (j != u && !p_board->p_boxes[(i / 3) * 3 + u / 3][(i % 3) * 3 + u % 3]->fixed)
                        {
                            for (int k = 0; k < p_board->p_boxes[(i / 3) * 3 + u / 3][(i % 3) * 3 + u % 3]->num_candidates; k++)
                            {
                                if (p_board->p_boxes[(i / 3) * 3 + u / 3][(i % 3) * 3 + u % 3]->candidates[k] == p_board->p_boxes[(i / 3) * 3 + u / 3][(i % 3) * 3 + j % 3]->candidates[c])
                                {
                                    isHiddenSingle = false;
                                    break;
                                }
                            }
                        }
                    }

                    if (isHiddenSingle)
                    {
                        int value = p_board->p_boxes[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3]->candidates[c];
                        p_board->p_boxes[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3]->value = value;
                        p_board->p_boxes[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3]->fixed = true;
                        p_board->p_boxes[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3]->num_candidates = 1;
                        /*
                        for (int s = 0; s < p_cells[i]->num_candidates; s++)
                        {
                            if (s != c)
                            {
                                p_cells[i]->candidates[s] = 0;
                            }
                        }
                        */

                        int v = i;
                        for (int a = 0; a < unit_size; a++)
                        {
                            int num_r = p_board->p_rows[v][a]->num_candidates;
                            for (int m = 0; m < num_r; m++)
                            {
                                if (p_board->p_rows[v][a]->candidates[m] == value)
                                {
                                    p_board->p_rows[v][a]->candidates[m] = 0;
                                    p_board->p_rows[v][a]->num_candidates -= 1;
                                }
                            }
                        }

                        int t = j;
                        for (int d = 0; d < unit_size; d++)
                        {
                            int num_c = p_board->p_rows[t][d]->num_candidates;
                            for (int n = 0; n < num_c; n++)
                            {
                                if (p_board->p_cols[d][t]->candidates[n] == value)
                                {
                                    p_board->p_cols[d][t]->candidates[n] = 0;
                                    p_board->p_cols[d][t]->num_candidates -= 1;
                                }
                            }
                        }

                        int b = (i / 3) * 3 + j / 3;
                        for (int f = 0; f < unit_size; f++)
                        {
                            int num_b = p_board->p_boxes[b][f]->num_candidates;
                            for (int p = 0; p < num_b; p++)
                            {
                                if (p_board->p_boxes[(b / 3) * 3 + f / 3][(b % 3) * 3 + f % 3]->candidates[p] == value)
                                {
                                    p_board->p_boxes[(b / 3) * 3 + f / 3][(b % 3) * 3 + f % 3]->candidates[p] = 0;
                                    p_board->p_boxes[(b / 3) * 3 + f / 3][(b % 3) * 3 + f % 3]->num_candidates -= 1;
                                }
                            }
                        }
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}