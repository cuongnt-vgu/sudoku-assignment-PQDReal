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
            int candidate_count = 0; // in that row, how many can be j?
            int index_1 = 0; // index of hidden single cell in the row
            int index_2 = 0;
            int value_1 = 0; // index of hidden single cell in the row
            int value_2 = 0;
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the row
            {
                if (p_board->p_rows[i][k]->num_candidates == 1) continue;
                if (p_board->p_rows[i][k]->candidates[j] == 1)
                {
                    candidate_count++;
                    if (index_1)
                    {
                        index_2 = k;
                        value_2 = j + 1;
                    }
                    index_1 = k;
                    value_1 = j + 1;
                }
            }
            if (candidate_count == 2) // only 1 cell can be j
            {
                HiddenPair temp_pair;
                temp_pair.p_cells[0] = p_board->p_rows[i][index_1];
                temp_pair.p_cells[1] = p_board->p_rows[i][index_2];
                temp_pair.value[0] = value_1;
                temp_pair.value[1] = value_2;
                int already_checked = 0;
                for (int l = 0; l < hs_counter; l++)
                    if ((pairs[l].p_cells[0] == temp_pair.p_cells[0] && pairs[l].p_cells[1] == temp_pair.p_cells[1]) ||
                        (pairs[l].p_cells[0] == temp_pair.p_cells[1] && pairs[l].p_cells[1] == temp_pair.p_cells[0]))
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
            int candidate_count = 0; // in that row, how many can be j?
            int index_1 = 0; // index of hidden single cell in the row
            int index_2 = 0;
            int value_1 = 0; // index of hidden single cell in the row
            int value_2 = 0;
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the row
            {
                if (p_board->p_rows[i][k]->num_candidates == 1) continue;
                if (p_board->p_rows[i][k]->candidates[j] == 1)
                {
                    candidate_count++;
                    if (index_1)
                    {
                        index_2 = k;
                        value_2 = j + 1;
                    }
                    index_1 = k;
                    value_1 = j + 1;
                }
            }
            if (candidate_count == 2) // only 1 cell can be j
            {
                HiddenPair temp_pair;
                temp_pair.p_cells[0] = p_board->p_rows[i][index_1];
                temp_pair.p_cells[1] = p_board->p_rows[i][index_2];
                temp_pair.value[0] = value_1;
                temp_pair.value[1] = value_2;
                int already_checked = 0;
                for (int l = 0; l < hs_counter; l++)
                    if ((pairs[l].p_cells[0] == temp_pair.p_cells[0] && pairs[l].p_cells[1] == temp_pair.p_cells[1]) ||
                        (pairs[l].p_cells[0] == temp_pair.p_cells[1] && pairs[l].p_cells[1] == temp_pair.p_cells[0]))
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
            int candidate_count = 0; // in that row, how many can be j?
            int index_1 = 0; // index of hidden single cell in the row
            int index_2 = 0;
            int value_1 = 0; // index of hidden single cell in the row
            int value_2 = 0;
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the row
            {
                if (p_board->p_rows[i][k]->num_candidates == 1) continue;
                if (p_board->p_rows[i][k]->candidates[j] == 1)
                {
                    candidate_count++;
                    if (index_1)
                    {
                        index_2 = k;
                        value_2 = j + 1;
                    }
                    index_1 = k;
                    value_1 = j + 1;
                }
            }
            if (candidate_count == 2) // only 1 cell can be j
            {
                HiddenPair temp_pair;
                temp_pair.p_cells[0] = p_board->p_rows[i][index_1];
                temp_pair.p_cells[1] = p_board->p_rows[i][index_2];
                temp_pair.value[0] = value_1;
                temp_pair.value[1] = value_2;
                int already_checked = 0;
                for (int l = 0; l < hs_counter; l++)
                    if ((pairs[l].p_cells[0] == temp_pair.p_cells[0] && pairs[l].p_cells[1] == temp_pair.p_cells[1]) ||
                        (pairs[l].p_cells[0] == temp_pair.p_cells[1] && pairs[l].p_cells[1] == temp_pair.p_cells[0]))
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
    for (int i = 0; i < hs_counter; i++)
    {
        // Make sure to allocate enough memory for the candidates array
        int *candidates = malloc(2 * sizeof(int));

        candidates[0] = pairs[i].value[0];
        candidates[1] = pairs[i].value[1];
        
        // Adjust the following line accordingly to match the actual number of candidates
        set_candidates(pairs[i].p_cells[0], candidates, 2);

        // Free the memory allocated for candidates
        free(candidates);
        //set_candidate(pairs[i].p_cells[1], candidates[1]);
    }
    free(pairs);
    return hs_counter; // returns total cells solved by hidden singles
}




