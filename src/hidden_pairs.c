#include "hidden_pairs.h"
#include <stdlib.h>

int hidden_pairs(SudokuBoard *p_board)
{
    int hp_counter = 0;
    HiddenPair *pairs = malloc(0);

    // row iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every row
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every number 1-9
        {
            int candidate_count = 0; // in that row, how many can be j?
            int indices[2] = {0, 0}; // indices of hidden pair cells in the row
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the row
            {
                if (p_board->p_rows[i][k]->num_candidates == 1) continue;
                if (p_board->p_rows[i][k]->candidates[j] == 1)
                {
                    if (candidate_count < 2)
                        indices[candidate_count] = k;
                    candidate_count++;
                }
            }
            if (candidate_count == 2) // only 2 cells can be j
            {
                HiddenPair temp_pair;
                temp_pair.p_cells[0] = p_board->p_rows[i][indices[0]];
                temp_pair.p_cells[1] = p_board->p_rows[i][indices[1]];
                temp_pair.value = j + 1;
                int already_checked = 0;
                for (int l = 0; l < hp_counter; l++)
                    if ((pairs[l].p_cells[0] == temp_pair.p_cells[0] && pairs[l].p_cells[1] == temp_pair.p_cells[1]) ||
                        (pairs[l].p_cells[0] == temp_pair.p_cells[1] && pairs[l].p_cells[1] == temp_pair.p_cells[0]))
                        already_checked = 1;
                if (!already_checked)
                {
                    hp_counter++;
                    pairs = realloc(pairs, hp_counter * sizeof(HiddenPair));
                    pairs[hp_counter - 1] = temp_pair;
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
            int indices[2] = {0, 0};
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the column
            {
                if (p_board->p_cols[i][k]->num_candidates == 1) continue;
                if (p_board->p_cols[i][k]->candidates[j] == 1)
                {
                    if (candidate_count < 2)
                        indices[candidate_count] = k;
                    candidate_count++;
                }
            }
            if (candidate_count == 2)
            {
                HiddenPair temp_pair;
                temp_pair.p_cells[0] = p_board->p_cols[i][indices[0]];
                temp_pair.p_cells[1] = p_board->p_cols[i][indices[1]];
                temp_pair.value = j + 1;
                int already_checked = 0;
                for (int l = 0; l < hp_counter; l++)
                    if ((pairs[l].p_cells[0] == temp_pair.p_cells[0] && pairs[l].p_cells[1] == temp_pair.p_cells[1]) ||
                        (pairs[l].p_cells[0] == temp_pair.p_cells[1] && pairs[l].p_cells[1] == temp_pair.p_cells[0]))
                        already_checked = 1;
                if (!already_checked)
                {
                    hp_counter++;
                    pairs = realloc(pairs, hp_counter * sizeof(HiddenPair));
                    pairs[hp_counter - 1] = temp_pair;
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
            int indices[2] = {0, 0};
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the box
            {
                if (p_board->p_boxes[i][k]->num_candidates == 1) continue;
                if (p_board->p_boxes[i][k]->candidates[j] == 1)
                {
                    if (candidate_count < 2)
                        indices[candidate_count] = k;
                    candidate_count++;
                }
            }
            if (candidate_count == 2)
            {
                HiddenPair temp_pair;
                temp_pair.p_cells[0] = p_board->p_boxes[i][indices[0]];
                temp_pair.p_cells[1] = p_board->p_boxes[i][indices[1]];
                temp_pair.value = j + 1;
                int already_checked = 0;
                for (int l = 0; l < hp_counter; l++)
                    if ((pairs[l].p_cells[0] == temp_pair.p_cells[0] && pairs[l].p_cells[1] == temp_pair.p_cells[1]) ||
                        (pairs[l].p_cells[0] == temp_pair.p_cells[1] && pairs[l].p_cells[1] == temp_pair.p_cells[0]))
                        already_checked = 1;
                if (!already_checked)
                {
                    hp_counter++;
                    pairs = realloc(pairs, hp_counter * sizeof(HiddenPair));
                    pairs[hp_counter - 1] = temp_pair;
                }
            }
        }
    }

    free(pairs);
    return hp_counter;
}
