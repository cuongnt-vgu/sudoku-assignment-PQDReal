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
                for (int c = 0; c < unit_size; c++)
                {
                    bool isHiddenSingle = true;
                    if (p_board->p_rows[i][j]->candidates[c] == 1)
                    {
                        for (int u = 0; u < unit_size; u++)
                        {
                            if (j != u && !p_board->p_rows[i][u]->fixed)
                            {
                                for (int k = 0; k < unit_size; k++)
                                {
                                    if (p_board->p_rows[i][u]->candidates[k] == 1 && k == c)
                                    {
                                        isHiddenSingle = false;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (isHiddenSingle)
                    {
                        //int value = c;
                        p_board->p_rows[i][j]->value = c;
                        p_board->p_rows[i][j]->fixed = true;
                        //p_board->p_rows[i][j]->num_candidates = 1;
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
                            for (int m = 0; m < unit_size; m++)
                            {
                                if (p_board->p_rows[r][a]->candidates[m] == 1 && m == c)
                                {
                                    p_board->p_rows[r][a]->candidates[m] = 0;
                                    p_board->p_rows[r][a]->num_candidates -= 1;
                                }
                            }
                        }

                        int t = j;
                        for (int d = 0; d < unit_size; d++)
                        {
                            for (int n = 0; n < unit_size; n++)
                            {
                                if (p_board->p_cols[t][d]->candidates[n] == 1 && n == c)
                                {
                                    p_board->p_cols[t][d]->candidates[n] = 0;
                                    p_board->p_cols[t][d]->num_candidates -= 1;
                                }
                            }
                        }

                        int b = (i / 3) * 3 + j / 3;
                        for (int f = 0; f < unit_size; f++)
                        {
                            for (int p = 0; p < unit_size; p++)
                            {
                                if (p_board->p_boxes[b][(i % 3) * 3 + f % 3]->candidates[p] == 1 && p == c)
                                {
                                    p_board->p_boxes[b][(i % 3) * 3 + f % 3]->candidates[p] = 0;
                                    p_board->p_boxes[b][(i % 3) * 3 + f % 3]->num_candidates -= 1;
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
                for (int c = 0; c < unit_size; c++)
                {
                    bool isHiddenSingle = true;
                    if (p_board->p_cols[j][i]->candidates[c] == 1)
                    {
                        for (int u = 0; u < unit_size; u++)
                        {
                            if (j != u && !p_board->p_cols[u][i]->fixed)
                            {
                                for (int k = 0; k < unit_size; k++)
                                {
                                    if (p_board->p_cols[u][i]->candidates[k] == 1 && k == c)
                                    {
                                        isHiddenSingle = false;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (isHiddenSingle)
                    {
                        p_board->p_cols[j][i]->value = c;
                        p_board->p_cols[j][i]->fixed = true;
                        //p_board->p_cols[j][i]->num_candidates = 1;
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
                            for (int m = 0; m < unit_size; m++)
                            {
                                if (p_board->p_rows[r][a]->candidates[m] == 1 && m == c)
                                {
                                    p_board->p_rows[r][a]->candidates[m] = 0;
                                    p_board->p_rows[r][a]->num_candidates -= 1;
                                }
                            }
                        }

                        int t = j;
                        for (int d = 0; d < unit_size; d++)
                        {
                            for (int n = 0; n < unit_size; n++)
                            {
                                if (p_board->p_cols[t][d]->candidates[n] == 1 && n == c)
                                {
                                    p_board->p_cols[t][d]->candidates[n] = 0;
                                    p_board->p_cols[t][d]->num_candidates -= 1;
                                }
                            }
                        }

                        int b = (i / 3) * 3 + j / 3;
                        for (int f = 0; f < unit_size; f++)
                        {
                            for (int p = 0; p < unit_size; p++)
                            {
                                if (p_board->p_boxes[b][(i % 3) * 3 + f % 3]->candidates[p] == 1 && p == c)
                                {
                                    p_board->p_boxes[b][(i % 3) * 3 + f % 3]->candidates[p] = 0;
                                    p_board->p_boxes[b][(i % 3) * 3 + f % 3]->num_candidates -= 1;
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
                for (int c = 0; c < unit_size; c++)
                {
                    bool isHiddenSingle = true;
                    if (p_board->p_boxes[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3]->candidates[c] == 1)
                    {
                        for (int u = 0; u < unit_size; u++)
                        {
                            if (j != u && !p_board->p_boxes[(i / 3) * 3 + u / 3][(i % 3) * 3 + u % 3]->fixed)
                            {
                                for (int k = 0; k < unit_size; k++)
                                {
                                    if (p_board->p_boxes[(i / 3) * 3 + u / 3][(i % 3) * 3 + u % 3]->candidates[k] == 1 && k == c)
                                    {
                                        isHiddenSingle = false;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (isHiddenSingle)
                    {
                        p_board->p_boxes[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3]->value = c;
                        p_board->p_boxes[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3]->fixed = true;
                        //p_board->p_boxes[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3]->num_candidates = 1;
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
                            for (int m = 0; m < unit_size; m++)
                            {
                                if (p_board->p_rows[r][a]->candidates[m] == 1 && m == c)
                                {
                                    p_board->p_rows[r][a]->candidates[m] = 0;
                                    p_board->p_rows[r][a]->num_candidates -= 1;
                                }
                            }
                        }

                        int t = j;
                        for (int d = 0; d < unit_size; d++)
                        {
                            for (int n = 0; n < unit_size; n++)
                            {
                                if (p_board->p_cols[t][d]->candidates[n] == 1 && n == c)
                                {
                                    p_board->p_cols[t][d]->candidates[n] = 0;
                                    p_board->p_cols[t][d]->num_candidates -= 1;
                                }
                            }
                        }

                        int b = (i / 3) * 3 + j / 3;
                        for (int f = 0; f < unit_size; f++)
                        {
                            for (int p = 0; p < unit_size; p++)
                            {
                                if (p_board->p_boxes[b][(i % 3) * 3 + f % 3]->candidates[p] == 1 && p == c)
                                {
                                    p_board->p_boxes[b][(i % 3) * 3 + f % 3]->candidates[p] = 0;
                                    p_board->p_boxes[b][(i % 3) * 3 + f % 3]->num_candidates -= 1;
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