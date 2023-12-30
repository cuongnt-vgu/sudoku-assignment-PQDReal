#include "hidden_singles.h"
#include <stdlib.h>

typedef struct {
    SudokuCell *p_cells[3];
    int values[3];
} HiddenTriple;

int hidden_triples(SudokuBoard *p_board)
{
    int ht_counter = 0;
    HiddenTriple *triples = malloc(0);

    // row iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every row
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every number 1-9
        {
            int candidate_count = 0; // in that row, how many can be j?
            int indices[3] = {0, 0, 0}; // indices of hidden triple cells in the row
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the row
            {
                if (p_board->p_rows[i][k]->num_candidates == 1) continue;
                if (p_board->p_rows[i][k]->candidates[j] == 1)
                {
                    if (candidate_count < 3)
                        indices[candidate_count] = k;
                    candidate_count++;
                }
            }
            if (candidate_count == 3) // only 3 cells can be j
            {
                HiddenTriple temp_triple;
                temp_triple.p_cells[0] = p_board->p_rows[i][indices[0]];
                temp_triple.p_cells[1] = p_board->p_rows[i][indices[1]];
                temp_triple.p_cells[2] = p_board->p_rows[i][indices[2]];
                temp_triple.values[0] = j + 1;
                int already_checked = 0;
                for (int l = 0; l < ht_counter; l++)
                    if ((triples[l].p_cells[0] == temp_triple.p_cells[0] && triples[l].p_cells[1] == temp_triple.p_cells[1] && triples[l].p_cells[2] == temp_triple.p_cells[2]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[1] && triples[l].p_cells[1] == temp_triple.p_cells[2] && triples[l].p_cells[2] == temp_triple.p_cells[0]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[2] && triples[l].p_cells[1] == temp_triple.p_cells[0] && triples[l].p_cells[2] == temp_triple.p_cells[1]))
                        already_checked = 1;
                if (!already_checked)
                {
                    ht_counter++;
                    triples = realloc(triples, ht_counter * sizeof(HiddenTriple));
                    triples[ht_counter - 1] = temp_triple;
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
            int indices[3] = {0, 0, 0};
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the column
            {
                if (p_board->p_cols[i][k]->num_candidates == 1) continue;
                if (p_board->p_cols[i][k]->candidates[j] == 1)
                {
                    if (candidate_count < 3)
                        indices[candidate_count] = k;
                    candidate_count++;
                }
            }
            if (candidate_count == 3)
            {
                HiddenTriple temp_triple;
                temp_triple.p_cells[0] = p_board->p_cols[i][indices[0]];
                temp_triple.p_cells[1] = p_board->p_cols[i][indices[1]];
                temp_triple.p_cells[2] = p_board->p_cols[i][indices[2]];
                temp_triple.values[0] = j + 1;
                int already_checked = 0;
                for (int l = 0; l < ht_counter; l++)
                    if ((triples[l].p_cells[0] == temp_triple.p_cells[0] && triples[l].p_cells[1] == temp_triple.p_cells[1] && triples[l].p_cells[2] == temp_triple.p_cells[2]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[1] && triples[l].p_cells[1] == temp_triple.p_cells[2] && triples[l].p_cells[2] == temp_triple.p_cells[0]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[2] && triples[l].p_cells[1] == temp_triple.p_cells[0] && triples[l].p_cells[2] == temp_triple.p_cells[1]))
                        already_checked = 1;
                if (!already_checked)
                {
                    ht_counter++;
                    triples = realloc(triples, ht_counter * sizeof(HiddenTriple));
                    triples[ht_counter - 1] = temp_triple;
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
            int indices[3] = {0, 0, 0};
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the box
            {
                if (p_board->p_boxes[i][k]->num_candidates == 1) continue;
                if (p_board->p_boxes[i][k]->candidates[j] == 1)
                {
                    if (candidate_count < 3)
                        indices[candidate_count] = k;
                    candidate_count++;
                }
            }
            if (candidate_count == 3)
            {
                HiddenTriple temp_triple;
                temp_triple.p_cells[0] = p_board->p_boxes[i][indices[0]];
                temp_triple.p_cells[1] = p_board->p_boxes[i][indices[1]];
                temp_triple.p_cells[2] = p_board->p_boxes[i][indices[2]];
                temp_triple.values[0] = j + 1;
                int already_checked = 0;
                for (int l = 0; l < ht_counter; l++)
                    if ((triples[l].p_cells[0] == temp_triple.p_cells[0] && triples[l].p_cells[1] == temp_triple.p_cells[1] && triples[l].p_cells[2] == temp_triple.p_cells[2]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[1] && triples[l].p_cells[1] == temp_triple.p_cells[2] && triples[l].p_cells[2] == temp_triple.p_cells[0]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[2] && triples[l].p_cells[1] == temp_triple.p_cells[0] && triples[l].p_cells[2] == temp_triple.p_cells[1]))
                        already_checked = 1;
                if (!already_checked)
                {
                    ht_counter++;
                    triples = realloc(triples, ht_counter * sizeof(HiddenTriple));
                    triples[ht_counter - 1] = temp_triple;
                }
            }
        }
    }

    free(triples);
    return ht_counter;
}

