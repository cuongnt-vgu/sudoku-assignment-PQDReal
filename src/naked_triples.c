#include "naked_triples.h"
#include <stdlib.h>

int naked_triples(SudokuBoard *p_board)
{
    int nt_counter = 0;
    NakedTriple *triples = malloc(0);

    // row iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every row
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every cell in the row
        {
            if (p_board->p_rows[i][j]->num_candidates != 3) continue;
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                if (p_board->p_rows[i][k]->num_candidates != 2 || p_board->p_rows[i][k]->num_candidates != 3 || j == k) continue;
                for (int l = 0; l < BOARD_SIZE; l++)
                {
                    if (p_board->p_rows[i][l]->num_candidates != 2 || p_board->p_rows[i][l]->num_candidates != 3 || l == k || l == j) continue;
                    // check if cells j, k, and l have the same three candidates
                    int match = 1;
                    for (int m = 0; m < BOARD_SIZE; m++)
                    {
                        if ((p_board->p_rows[i][j]->candidates[m] != p_board->p_rows[i][k]->candidates[m])||
                            (p_board->p_rows[i][j]->candidates[m] != p_board->p_rows[i][l]->candidates[m]))
                        {
                            match = 0;
                            break;
                        }
                    }
                    if (match) // cells j, k, and l form a naked triple
                    {
                        NakedTriple temp_triple;
                        temp_triple.p_cells[0] = p_board->p_rows[i][j];
                        temp_triple.p_cells[1] = p_board->p_rows[i][k];
                        temp_triple.p_cells[2] = p_board->p_rows[i][l];
                        int v = 0;
                        for (int m = 0; m < BOARD_SIZE; m++)
                        {
                            if (p_board->p_rows[i][j]->candidates[m] == 1)
                            {
                                temp_triple.values[v] = m + 1;
                                v++;
                            }
                        }
                        nt_counter++;
                        triples = realloc(triples, nt_counter * sizeof(NakedTriple));
                        triples[nt_counter - 1] = temp_triple;
                    }
                }
            }
        }
    }

    // column iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every column
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every cell in the column
        {
            if (p_board->p_cols[i][j]->num_candidates != 3) continue;
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                if (p_board->p_cols[i][k]->num_candidates != 2 || p_board->p_cols[i][k]->num_candidates != 3 || j == k) continue;
                for (int l = 0; l < BOARD_SIZE; l++)
                {
                    if (p_board->p_cols[i][l]->num_candidates != 2 || p_board->p_cols[i][l]->num_candidates != 3 || l == k || l == j) continue;
                    // check if cells j, k, and l have the same three candidates
                    int match = 1;
                    for (int m = 0; m < BOARD_SIZE; m++)
                    {
                        if (p_board->p_cols[i][j]->candidates[m] != p_board->p_cols[i][k]->candidates[m] ||
                            p_board->p_cols[i][j]->candidates[m] != p_board->p_cols[i][l]->candidates[m])
                        {
                            match = 0;
                            break;
                        }
                    }
                    if (match) // cells j, k, and l form a naked triple
                    {
                        NakedTriple temp_triple;
                        temp_triple.p_cells[0] = p_board->p_cols[i][j];
                        temp_triple.p_cells[1] = p_board->p_cols[i][k];
                        temp_triple.p_cells[2] = p_board->p_cols[i][l];
                        int v = 0;
                        for (int m = 0; m < BOARD_SIZE; m++)
                        {
                            if (p_board->p_cols[i][j]->candidates[m] == 1)
                            {
                                temp_triple.values[v] = m + 1;
                                v++;
                            }
                        }
                        nt_counter++;
                        triples = realloc(triples, nt_counter * sizeof(NakedTriple));
                        triples[nt_counter - 1] = temp_triple;
                    }
                }
            }
        }
    }

    // box iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every box
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every cell in the box
        {
            if (p_board->p_boxes[i][j]->num_candidates != 3) continue;
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                if (p_board->p_boxes[i][k]->num_candidates != 2 || p_board->p_boxes[i][k]->num_candidates != 3 || j == k) continue;
                for (int l = 0; l < BOARD_SIZE; l++)
                {
                    if (p_board->p_boxes[i][l]->num_candidates != 2 || p_board->p_boxes[i][l]->num_candidates != 3 || l == k || l == j) continue;
                    // check if cells j, k, and l have the same three candidates
                    int match = 1;
                    for (int m = 0; m < BOARD_SIZE; m++)
                    {
                        if (p_board->p_boxes[i][j]->candidates[m] != p_board->p_boxes[i][k]->candidates[m] ||
                            p_board->p_boxes[i][j]->candidates[m] != p_board->p_boxes[i][l]->candidates[m])
                        {
                            match = 0;
                            break;
                        }
                    }
                    if (match) // cells j, k, and l form a naked triple
                    {
                        NakedTriple temp_triple;
                        temp_triple.p_cells[0] = p_board->p_boxes[i][j];
                        temp_triple.p_cells[1] = p_board->p_boxes[i][k];
                        temp_triple.p_cells[2] = p_board->p_boxes[i][l];
                        int v = 0;
                        for (int m = 0; m < BOARD_SIZE; m++)
                        {
                            if (p_board->p_boxes[i][j]->candidates[m] == 1)
                            {
                                temp_triple.values[v] = m + 1;
                                v++;
                            }
                        }
                        nt_counter++;
                        triples = realloc(triples, nt_counter * sizeof(NakedTriple));
                        triples[nt_counter - 1] = temp_triple;
                    }
                }
            }
        }
    }

    // remove the naked triple values from other cells in the same row, column, or box
    for (int i = 0; i < nt_counter; i++)
    {
        // find the row, column, and box that contain the naked triple
        int row = triples[i].p_cells[0]->row_index;
        int col = triples[i].p_cells[0]->col_index;
        int box = triples[i].p_cells[0]->box_index;

        // remove the naked triple values from other cells in the same row
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_board->p_rows[row][j] != triples[i].p_cells[0] && 
                p_board->p_rows[row][j] != triples[i].p_cells[1] &&
                p_board->p_rows[row][j] != triples[i].p_cells[2])
            {
                p_board->p_rows[row][j]->candidates[triples[i].values[0] - 1] = 0;
                p_board->p_rows[row][j]->candidates[triples[i].values[1] - 1] = 0;
                p_board->p_rows[row][j]->candidates[triples[i].values[2] - 1] = 0;
            }
        }

        // remove the naked triple values from other cells in the same column
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_board->p_cols[col][j] != triples[i].p_cells[0] && 
                p_board->p_cols[col][j] != triples[i].p_cells[1] &&
                p_board->p_cols[col][j] != triples[i].p_cells[2])
            {
                p_board->p_cols[col][j]->candidates[triples[i].values[0] - 1] = 0;
                p_board->p_cols[col][j]->candidates[triples[i].values[1] - 1] = 0;
                p_board->p_cols[col][j]->candidates[triples[i].values[2] - 1] = 0;
            }
        }

        // remove the naked triple values from other cells in the same box
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_board->p_boxes[box][j] != triples[i].p_cells[0] && 
                p_board->p_boxes[box][j] != triples[i].p_cells[1] &&
                p_board->p_boxes[box][j] != triples[i].p_cells[2])
            {
                p_board->p_boxes[box][j]->candidates[triples[i].values[0] - 1] = 0;
                p_board->p_boxes[col][j]->candidates[triples[i].values[1] - 1] = 0;
                p_board->p_boxes[col][j]->candidates[triples[i].values[2] - 1] = 0;
            }
        }
    }

    free(triples);
    return nt_counter;
}


