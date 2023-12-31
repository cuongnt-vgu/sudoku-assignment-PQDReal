#include "hidden_pairs.h"
#include <stdlib.h>

int hidden_pairs(SudokuBoard *p_board)
{
    int hs_counter = 0;
    HiddenPair *pairs = malloc(0);

    // row iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every row
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every number 1-9
        {
            int candidate_count = 0;
            int index_1 = 0;
            int index_2 = 0;
            int value_1 = 0;
            int value_2 = 0;
            bool r_invalid = true;
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the row
            {
                if (p_board->p_rows[i][k]->num_candidates == 1) continue;
                if (p_board->p_rows[i][k]->candidates[j] == 1)
                {
                    candidate_count++;
                    if (index_1)
                    {
                        index_2 = k;
                    }
                    else
                    {
                        index_1 = k;
                    }
                    value_1 = j + 1;
                }
            }
            if (candidate_count == 2) // only 1 cell can be j
            {
                int candi = 0;
                for (int l = 0; l < BOARD_SIZE; l++)
                {
                    if (p_board->p_rows[i][index_1]->candidates[l] == 1 && p_board->p_rows[i][index_2]->candidates[l] == 1 && l != value_1 - 1)
                    {
                        value_2 = l + 1;
                        candi++;
                    }
                }
                if (candi == 1)
                {
                    int avail = 0;
                    for (int m = 0; m < BOARD_SIZE; m++)
                    {
                        if ((p_board->p_rows[i][m]->candidates[value_2 - 1] == 1) && (m != index_1 && m != index_2))
                        {
                            avail++;
                        }
                    }
                    if (avail == 0)
                    {
                        r_invalid = false;
                    }
                }
            }
            if (!r_invalid)
            {
                HiddenPair temp_pair;
                temp_pair.p_cell_1 = p_board->p_rows[i][index_1];
                temp_pair.p_cell_2 = p_board->p_rows[i][index_2];
                temp_pair.value1 = value_1;
                temp_pair.value2 = value_2;
                int already_checked = 0;
                for (int l = 0; l < hs_counter; l++)
                    if ((pairs[l].p_cell_1 == temp_pair.p_cell_1 && pairs[l].p_cell_2 == temp_pair.p_cell_2) ||
                        (pairs[l].p_cell_1 == temp_pair.p_cell_2 && pairs[l].p_cell_2 == temp_pair.p_cell_1))
                        already_checked = 1;
                if (!already_checked)
                {
                    hs_counter++;
                    pairs = realloc(pairs, hs_counter * sizeof(HiddenPair));
                    pairs[hs_counter - 1] = temp_pair;
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
            int index_1 = 0;
            int index_2 = 0;
            int value_1 = 0; 
            int value_2 = 0;
            bool c_invalid = true;
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the row
            {
                if (p_board->p_cols[i][k]->num_candidates == 1) continue;
                if (p_board->p_cols[i][k]->candidates[j] == 1)
                {
                    candidate_count++;
                    if (index_1)
                    {
                        index_2 = k;
                    }
                    else
                    {
                        index_1 = k;
                    }
                    value_1 = j + 1;
                }
            }
            if (candidate_count == 2)
            {
                int candi = 0;
                for (int l = 0; l < BOARD_SIZE; l++)
                {
                    if (p_board->p_cols[i][index_1]->candidates[l] == 1 && p_board->p_cols[i][index_2]->candidates[l] == 1 && l != value_1 - 1)
                    {
                        value_2 = l + 1;
                        candi++;
                    }
                }
                if (candi == 1)
                {
                    int avail = 0;
                    for (int m = 0; m < BOARD_SIZE; m++)
                    {
                        if ((p_board->p_cols[i][m]->candidates[value_2 - 1] == 1) && (m != index_1 && m != index_2))
                        {
                            avail++;
                        }
                    }
                    if (avail == 0)
                    {
                        c_invalid = false;
                    }
                }
            }
            if (!c_invalid)
            {
                HiddenPair temp_pair;
                temp_pair.p_cell_1 = p_board->p_cols[i][index_1];
                temp_pair.p_cell_2 = p_board->p_cols[i][index_2];
                temp_pair.value1 = value_1;
                temp_pair.value2 = value_2;
                int already_checked = 0;
                for (int l = 0; l < hs_counter; l++)
                    if ((pairs[l].p_cell_1 == temp_pair.p_cell_1 && pairs[l].p_cell_2 == temp_pair.p_cell_2) ||
                        (pairs[l].p_cell_1 == temp_pair.p_cell_2 && pairs[l].p_cell_2 == temp_pair.p_cell_1))
                        already_checked = 1;
                if (!already_checked)
                {
                    hs_counter++;
                    pairs = realloc(pairs, hs_counter * sizeof(HiddenPair));
                    pairs[hs_counter - 1] = temp_pair;
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
            int index_1 = 0;
            int index_2 = 0;
            int value_1 = 0;
            int value_2 = 0;
            bool b_invalid = true;
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the row
            {
                if (p_board->p_cols[i][k]->num_candidates == 1) continue;
                if (p_board->p_cols[i][k]->candidates[j] == 1)
                {
                    candidate_count++;
                    if (index_1)
                    {
                        index_2 = k;
                    }
                    else
                    {
                        index_1 = k;
                    }
                    value_1 = j + 1;
                }
            }
            if (candidate_count == 2)
            {
                int candi = 0;
                for (int l = 0; l < BOARD_SIZE; l++)
                {
                    if (p_board->p_boxes[i][index_1]->candidates[l] == 1 && p_board->p_boxes[i][index_2]->candidates[l] == 1 && l != value_1 - 1)
                    {
                        value_2 = l + 1;
                        candi++;
                    }
                }
                if (candi == 1)
                {
                    int avail = 0;
                    for (int m = 0; m < BOARD_SIZE; m++)
                    {
                        if ((p_board->p_boxes[i][m]->candidates[value_2 - 1] == 1) && (m != index_1 && m != index_2))
                        {
                            avail++;
                        }
                    }
                    if (avail == 0)
                    {
                        b_invalid = false;
                    }
                }
            }
            if (!b_invalid) // only 1 cell can be j
            {
                HiddenPair temp_pair;
                temp_pair.p_cell_1 = p_board->p_boxes[i][index_1];
                temp_pair.p_cell_2 = p_board->p_boxes[i][index_2];
                temp_pair.value1 = value_1;
                temp_pair.value2 = value_2;
                int already_checked = 0;
                for (int l = 0; l < hs_counter; l++)
                    if ((pairs[l].p_cell_1 == temp_pair.p_cell_1 && pairs[l].p_cell_2 == temp_pair.p_cell_2) ||
                        (pairs[l].p_cell_1 == temp_pair.p_cell_2 && pairs[l].p_cell_2 == temp_pair.p_cell_1))
                        already_checked = 1;
                if (!already_checked)
                {
                    hs_counter++;
                    pairs = realloc(pairs, hs_counter * sizeof(HiddenPair));
                    pairs[hs_counter - 1] = temp_pair;
                }
            }
        }
    }

    //int *candidates = malloc(4);
    int *candidates = malloc(2 * sizeof(int));
    for (int i = 0; i < hs_counter; i++)
    {
        candidates[0] = pairs[i].value1;
        candidates[1] = pairs[i].value2;
        
        set_candidates(pairs[i].p_cell_1, candidates, 2);
        set_candidates(pairs[i].p_cell_2, candidates, 2);

    }
    free(pairs);
    free(candidates);
    return hs_counter; // returns total cells solved by hidden singles
}

