#include "naked_pairs.h"
#include <stdlib.h>

int naked_pairs(SudokuBoard *p_board)
{
    int np_counter = 0;
    NakedPair *pairs = malloc(0);

    // row iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every row
    {
        for (int j = i + 1; j < BOARD_SIZE - 1; j++) // iterate over every cell in the row
        {
            if (p_board->p_rows[i][j]->num_candidates != 2) continue;
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the row after cell j
            {
                if (p_board->p_rows[i][k]->num_candidates != 2) continue;
                // check if cells j and k have the same two candidates
                int match = 1;
                for (int l = 0; l < BOARD_SIZE; l++)
                {
                    if (p_board->p_rows[i][j]->candidates[l] != p_board->p_rows[i][k]->candidates[l])
                    {
                        match = 0;
                        break;
                    }
                }
                if (match) // cells j and k form a naked pair
                {
                    NakedPair temp_pair;
                    temp_pair.p_cells[0] = p_board->p_rows[i][j];
                    temp_pair.p_cells[1] = p_board->p_rows[i][k];
                    int v = 0;
                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (p_board->p_rows[i][j]->candidates[l] == 1)
                        {
                            temp_pair.values[v] = l + 1;
                            v++;
                        }
                    }
                    np_counter++;
                    pairs = realloc(pairs, np_counter * sizeof(NakedPair));
                    pairs[np_counter - 1] = temp_pair;
                }
            }
        }
    }

    // column iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every column
    {
        for (int j = 0; j < BOARD_SIZE - 1; j++) // iterate over every cell in the column
        {
            if (p_board->p_cols[i][j]->num_candidates != 2) continue;
            for (int k = j + 1; k < BOARD_SIZE; k++) // iterate over every cell in the column after cell j
            {
                if (p_board->p_cols[i][k]->num_candidates != 2) continue;
                // check if cells j and k have the same two candidates
                int match = 1;
                for (int l = 0; l < BOARD_SIZE; l++)
                {
                    if (p_board->p_cols[i][j]->candidates[l] == 1 && p_board->p_cols[i][k]->candidates[l] == 1)
                    {
                        match = 0;
                        break;
                    }
                }
                if (match) // cells j and k form a naked pair
                {
                    NakedPair temp_pair;
                    temp_pair.p_cells[0] = p_board->p_cols[i][j];
                    temp_pair.p_cells[1] = p_board->p_cols[i][k];
                    int v = 0;
                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (p_board->p_cols[i][j]->candidates[l] == 1)
                        {
                            temp_pair.values[v] = l + 1;
                            v++;
                        }
                    }
                    np_counter++;
                    pairs = realloc(pairs, np_counter * sizeof(NakedPair));
                    pairs[np_counter - 1] = temp_pair;
                }
            }
        }
    }

    // box iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every box
    {
        for (int j = 0; j < BOARD_SIZE - 1; j++) // iterate over every cell in the box
        {
            if (p_board->p_boxes[i][j]->num_candidates != 2) continue;
            for (int k = j + 1; k < BOARD_SIZE; k++) // iterate over every cell in the box after cell j
            {
                if (p_board->p_boxes[i][k]->num_candidates != 2) continue;
                // check if cells j and k have the same two candidates
                int match = 1;
                for (int l = 0; l < BOARD_SIZE; l++)
                {
                    if (p_board->p_boxes[i][j]->candidates[l] == 1 & p_board->p_boxes[i][k]->candidates[l] == 1)
                    {
                        match = 0;
                        break;
                    }
                }
                if (match) // cells j and k form a naked pair
                {
                    NakedPair temp_pair;
                    temp_pair.p_cells[0] = p_board->p_boxes[i][j];
                    temp_pair.p_cells[1] = p_board->p_boxes[i][k];
                    int v = 0;
                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (p_board->p_boxes[i][j]->candidates[l] == 1)
                        {
                            temp_pair.values[v] = l + 1;
                            v++;
                        }
                    }
                    np_counter++;
                    pairs = realloc(pairs, np_counter * sizeof(NakedPair));
                    pairs[np_counter - 1] = temp_pair;
                }
            }
        }
    }

    // remove the naked pair values from other cells in the same row, column, or box
    for (int i = 0; i < np_counter; i++)
    {
        // find the row, column, and box that contain the naked pair
        int row = pairs[i].p_cells[0]->row_index;
        int col = pairs[i].p_cells[0]->col_index;
        int box = pairs[i].p_cells[0]->box_index;

        // remove the naked pair values from other cells in the same row
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_board->p_rows[row][j] != pairs[i].p_cells[0] && 
                p_board->p_rows[row][j] != pairs[i].p_cells[1])
            {
                p_board->p_rows[row][j]->candidates[pairs[i].values[0] - 1] = 0;
                p_board->p_rows[row][j]->candidates[pairs[i].values[1] - 1] = 0;
            }
        }

        // remove the naked pair values from other cells in the same column
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_board->p_cols[col][j] != pairs[i].p_cells[0] && 
                p_board->p_cols[col][j] != pairs[i].p_cells[1])
            {
                p_board->p_cols[col][j]->candidates[pairs[i].values[0] - 1] = 0;
                p_board->p_cols[col][j]->candidates[pairs[i].values[1] - 1] = 0;
            }
        }

        // remove the naked pair values from other cells in the same box
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_board->p_boxes[box][j] != pairs[i].p_cells[0] && 
                p_board->p_boxes[box][j] != pairs[i].p_cells[1])
            {
                p_board->p_boxes[box][j]->candidates[pairs[i].values[0] - 1] = 0;
                p_board->p_boxes[box][j]->candidates[pairs[i].values[1] - 1] = 0;
            }
        }
    }

    free(pairs);
    return np_counter;
}


