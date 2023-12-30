// hidden_triples.c
#include "hidden_triples.h"
#include <stdlib.h>

int hidden_triples(SudokuBoard *p_board)
{
    int ht_counter = 0;
    HiddenTriple *triples = malloc(0);

    // Row iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every row
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every number 1-9
        {
            int candidate_count = 0;
            int indices[3] = {0};
            int values[3] = {0};
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the row
            {
                if (p_board->p_rows[i][k]->num_candidates == 1 || p_board->p_rows[i][k]->candidates[j] == 0)
                    continue;

                indices[candidate_count] = k;
                values[candidate_count] = j + 1;
                candidate_count++;

                if (candidate_count > 2)
                    break;
            }

            if (candidate_count == 3)
            {
                HiddenTriple temp_triple;
                temp_triple.p_cells[0] = p_board->p_rows[i][indices[0]];
                temp_triple.p_cells[1] = p_board->p_rows[i][indices[1]];
                temp_triple.p_cells[2] = p_board->p_rows[i][indices[2]];
                temp_triple.values[0] = values[0];
                temp_triple.values[1] = values[1];
                temp_triple.values[2] = values[2];

                int already_checked = 0;
                for (int l = 0; l < ht_counter; l++)
                {
                    if ((triples[l].p_cells[0] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[2]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[1]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[2]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[0]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[1]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[0]))
                    {
                        already_checked = 1;
                        break;
                    }
                }

                if (!already_checked)
                {
                    ht_counter++;
                    triples = realloc(triples, ht_counter * sizeof(HiddenTriple));
                    triples[ht_counter - 1] = temp_triple;
                }
            }
        }
    }

    // Column iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every column
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every number 1-9
        {
            // Similar logic as row iteration with necessary modifications
            int candidate_count = 0;
            int indices[3] = {0};
            int values[3] = {0};
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the column
            {
                if (p_board->p_cols[i][k]->num_candidates == 1 || p_board->p_cols[i][k]->candidates[j] == 0)
                    continue;

                indices[candidate_count] = k;
                values[candidate_count] = j + 1;
                candidate_count++;

                if (candidate_count > 2)
                    break;
            }

            // Check for hidden triple condition
            if (candidate_count == 3)
            {
                // Create a HiddenTriple struct
                HiddenTriple temp_triple;
                temp_triple.p_cells[0] = p_board->p_cols[i][indices[0]];
                temp_triple.p_cells[1] = p_board->p_cols[i][indices[1]];
                temp_triple.p_cells[2] = p_board->p_cols[i][indices[2]];
                temp_triple.values[0] = values[0];
                temp_triple.values[1] = values[1];
                temp_triple.values[2] = values[2];

                // Check if the triple is already in the list
                int already_checked = 0;
                for (int l = 0; l < ht_counter; l++)
                {
                    if ((triples[l].p_cells[0] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[2]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[1]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[2]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[0]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[1]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[0]))
                    {
                        already_checked = 1;
                        break;
                    }
                }

                // If not, add it to the list
                if (!already_checked)
                {
                    ht_counter++;
                    triples = realloc(triples, ht_counter * sizeof(HiddenTriple));
                    triples[ht_counter - 1] = temp_triple;
                }
            }
        }
    }

    // Box iteration
    for (int i = 0; i < BOARD_SIZE; i++) // iterate over every box
    {
        for (int j = 0; j < BOARD_SIZE; j++) // iterate over every number 1-9
        {
            // Similar logic as row and column iteration with necessary modifications
            int candidate_count = 0;
            int indices[3] = {0};
            int values[3] = {0};
            for (int k = 0; k < BOARD_SIZE; k++) // iterate over every cell in the box
            {
                int row = 3 * (i / 3) + k / 3;
                int col = 3 * (i % 3) + k % 3;

                if (p_board->p_boxes[i][k]->num_candidates == 1 || p_board->p_boxes[i][k]->candidates[j] == 0)
                    continue;

                indices[candidate_count] = k;
                values[candidate_count] = j + 1;
                candidate_count++;

                if (candidate_count > 2)
                    break;
            }

            // Check for hidden triple condition
            if (candidate_count == 3)
            {
                // Create a HiddenTriple struct
                HiddenTriple temp_triple;
                temp_triple.p_cells[0] = p_board->p_boxes[i][indices[0]];
                temp_triple.p_cells[1] = p_board->p_boxes[i][indices[1]];
                temp_triple.p_cells[2] = p_board->p_boxes[i][indices[2]];
                temp_triple.values[0] = values[0];
                temp_triple.values[1] = values[1];
                temp_triple.values[2] = values[2];

                // Check if the triple is already in the list
                int already_checked = 0;
                for (int l = 0; l < ht_counter; l++)
                {
                    if ((triples[l].p_cells[0] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[2]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[1]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[2]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[0]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[0] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[1]) ||
                        (triples[l].p_cells[0] == temp_triple.p_cells[2] &&
                         triples[l].p_cells[1] == temp_triple.p_cells[1] &&
                         triples[l].p_cells[2] == temp_triple.p_cells[0]))
                    {
                        already_checked = 1;
                        break;
                    }
                }

                // If not, add it to the list
                if (!already_checked)
                {
                    ht_counter++;
                    triples = realloc(triples, ht_counter * sizeof(HiddenTriple));
                    triples[ht_counter - 1] = temp_triple;
                }
            }
        }
    }

    // Process the identified hidden triples
    int *candidates = malloc(9 * sizeof(int));
    for (int i = 0; i < ht_counter; i++)
    {
        candidates[0] = triples[i].values[0];
        candidates[1] = triples[i].values[1];
        candidates[2] = triples[i].values[2];
        set_candidates(triples[i].p_cells[0], candidates, 3);
        set_candidates(triples[i].p_cells[1], candidates, 3);
        set_candidates(triples[i].p_cells[2], candidates, 3);
    }

    // Free allocated memory
    free(triples);
    free(candidates);

    // Return the total number of cells solved by hidden triples
    return ht_counter;
}


