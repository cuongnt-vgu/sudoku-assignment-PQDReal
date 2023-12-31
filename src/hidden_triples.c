#include "hidden_triples.h"
#include <stdlib.h>
#include <stdio.h>

int check_cell_in_hidden_triples(int triples[3], Cell* p_cell)
{
    for (int i = 0; i < 3; i++)
    {   
        if (is_candidate(p_cell, triples[i])) return 1;
    }
    return 0;
}

int check_hidden_triples(Cell **p_cells, int hidden_triples_candidates[], int *indices)
{
    int cell_ht_np_nt_counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells[i]->num_candidates == 1) continue;
        else if (check_cell_in_hidden_triples(hidden_triples_candidates, p_cells[i])) indices[cell_ht_np_nt_counter++] = i;
    }
    if (cell_ht_np_nt_counter == 3) return 1;
    return 0;
}

void find_hidden_triples(Cell **p_cells, HiddenTriples *p_hidden_triples, int *p_ht_np_nt_counter, int unit)
{
    int candidate_ht_np_nt_counter[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        candidate_ht_np_nt_counter[i] = 0;
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        int* candidates = get_candidates(p_cells[i]);
        for (int j = 0; j < p_cells[i]->num_candidates; j++)
        {
            candidate_ht_np_nt_counter[candidates[j]-1] += 1;
        }
        free(candidates);
    }

    int hidden_triples_candidates[BOARD_SIZE];
    int hidden_triples_candidates_count = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (candidate_ht_np_nt_counter[i] == 2 || candidate_ht_np_nt_counter[i] == 3)
        {
            hidden_triples_candidates[hidden_triples_candidates_count++] = i+1;
        }
    }

    if (hidden_triples_candidates_count < 3) return;

    for (int i = 0; i < hidden_triples_candidates_count - 2; i++)
    {
        for (int j = i+1; j < hidden_triples_candidates_count - 1; j++)
        {
            for (int k = j+1; k < hidden_triples_candidates_count; k++)
            {
                int values[3] = {hidden_triples_candidates[i], hidden_triples_candidates[j], hidden_triples_candidates[k]};
                int indices[BOARD_SIZE];
                if (check_hidden_triples(p_cells, values, indices))
                {
                    if (unit == 1)
                    {
                        if ((indices[0] == 0 || indices[0] == 3 || indices[0] == 6) && indices[1] == indices[0]+1 && indices[2] == indices[0]+2) continue;
                        else if ((indices[0] >= 0 && indices[0] <= 2) && indices[1] == indices[0]+3 && indices[2] == indices[0]+6) continue;
                    }
                    p_hidden_triples[(*p_ht_np_nt_counter)++] = (HiddenTriples){p_cells, {indices[0], indices[1], indices[2]}, {hidden_triples_candidates[i], hidden_triples_candidates[j], hidden_triples_candidates[k]}};
                }
            }
        }
    }
}

int hidden_triples(SudokuBoard *p_board)
{
    int ht_np_nt_counter = 0;

    HiddenTriples p_hidden_triples[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_triples(p_board->p_rows[i], p_hidden_triples, &ht_np_nt_counter, 0);
        find_hidden_triples(p_board->p_cols[i], p_hidden_triples, &ht_np_nt_counter, 0);
        find_hidden_triples(p_board->p_boxes[i], p_hidden_triples, &ht_np_nt_counter, 1);
    }
    int offset = ht_np_nt_counter;
    for (int i = 0; i < ht_np_nt_counter; i++)
    {
        int change = 0;
        Cell** p_cells = p_hidden_triples[i].p_cells;
        int triples_values[3];
        for (int j = 0; j < 3; j++)
        {
            triples_values[j] = p_hidden_triples[i].values[j];
        }
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (check_cell_in_hidden_triples(triples_values, p_cells[j]))
            {
                for (int k = 1; k < BOARD_SIZE+1; k++)
                {
                    if (k != triples_values[0] && k != triples_values[1] && k != triples_values[2])
                    {

                        if (is_candidate(p_cells[j], k))
                        {
                            unset_candidate(p_cells[j], k);
                            change = 1;
                        }                     
                    }
                }
            }
        }
        if (change == 1) offset--;
    }
    return ht_np_nt_counter - offset;
}
