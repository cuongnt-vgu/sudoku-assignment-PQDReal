#include "hidden_singles.h"
#include <stdlib.h>

int hidden_singles(SudokuBoard *p_board)
{
    int total_cells = 0;
    HiddenSingle *singles = malloc(0);

    // row iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every row
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every number 1-9
        {
            int candidate_count = 0; // in that row, how many can be j?
            int single_index = 0; // index of hidden single cell in the row
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the row
            {
                if (p_board->p_rows[i][k]->num_candidates == 1) continue;
                if (p_board->p_rows[i][k]->candidates[j] == 1)
                {
                    candidate_count++;
                    single_index = k;
                }
            }
            if (candidate_count == 1) // only 1 cell can be j
            {
                HiddenSingle temp_single;
                temp_single.p_cell = p_board->p_rows[i][single_index];
                temp_single.value = j + 1;
                int already_checked = 0;
                for (int l = 0; l < total_cells; l++)
                    if (singles[l].p_cell == temp_single.p_cell)
                        already_checked = 1;
                if (!already_checked)
                {
                    total_cells++;
                    singles = realloc(singles, total_cells * sizeof(HiddenSingle));
                    singles[total_cells - 1] = temp_single;
                }
            }
        }
    }

    // column iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every column
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every number 1-9
        {
            int candidate_count = 0;
            int single_index = 0;
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the column
            {
                if (p_board->p_cols[i][k]->num_candidates == 1) continue;
                if (p_board->p_cols[i][k]->candidates[j] == 1)
                {
                    candidate_count++;
                    single_index = k;
                }
            }
            if (candidate_count == 1)
            {
                HiddenSingle temp_single;
                temp_single.p_cell = p_board->p_cols[i][single_index];
                temp_single.value = j + 1;
                int already_checked = 0;
                for (int l = 0; l < total_cells; l++)
                    if (singles[l].p_cell == temp_single.p_cell)
                        already_checked = 1;
                if (!already_checked)
                {
                    total_cells++;
                    singles = realloc(singles, total_cells * sizeof(HiddenSingle));
                    singles[total_cells - 1] = temp_single;
                }
            }
        }
    }

    // box iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every box
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every number 1-9
        {
            int candidate_count = 0;
            int single_index = 0;
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the box
            {
                if (p_board->p_boxes[i][k]->num_candidates == 1) continue;
                if (p_board->p_boxes[i][k]->candidates[j] == 1)
                {
                    candidate_count++;
                    single_index = k;
                }
            }
            if (candidate_count == 1)
            {
                HiddenSingle temp_single;
                temp_single.p_cell = p_board->p_boxes[i][single_index];
                temp_single.value = j + 1;
                int already_checked = 0;
                for (int l = 0; l < total_cells; l++)
                    if (singles[l].p_cell == temp_single.p_cell)
                        already_checked = 1;
                if (!already_checked)
                {
                    total_cells++;
                    singles = realloc(singles, total_cells * sizeof(HiddenSingle));
                    singles[total_cells - 1] = temp_single;
                }
            }
        }
    }

    int *candidates = malloc(4);
    for (int i = 0; i < total_cells; i++)
    {
        candidates[0] = singles[i].value;
        set_candidates(singles[i].p_cell, candidates, 1);
    }
    free(singles);
    free(candidates);
    return total_cells; // returns total cells solved by hidden singles
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