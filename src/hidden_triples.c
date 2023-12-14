#include "hidden_triples.h"
#include "sudoku.h"

static void find_hidden_triples_in_unit(Cell **p_cells, int unit_size);

// Implement hidden triples logic here
int hidden_triples(SudokuBoard *p_board)
{
    int hiddenTriplesCounter = 0;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_triples_in_unit(p_board->p_rows[i], BOARD_SIZE);
    }

    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_triples_in_unit(p_board->p_cols[i], BOARD_SIZE);
    }

    // Check boxes
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_triples_in_unit(p_board->p_boxes[i], BOARD_SIZE);
    }

    return hiddenTriplesCounter;
}

static void find_hidden_triples_in_unit(Cell **p_cells, int unit_size)
{
    // Iterate through each triple of cells
    for (int i = 0; i < unit_size - 2; i++)
    {
        for (int j = i + 1; j < unit_size - 1; j++)
        {
            for (int k = j + 1; k < unit_size; k++)
            {
                // Check if all three cells have 2 or 3 candidates
                if ((p_cells[i]->num_candidates == 2 || p_cells[i]->num_candidates == 3) &&
                    (p_cells[j]->num_candidates == 2 || p_cells[j]->num_candidates == 3) &&
                    (p_cells[k]->num_candidates == 2 || p_cells[k]->num_candidates == 3))
                {
                    // Combine candidates from the three cells
                    int combinedCandidates[BOARD_SIZE] = {0};

                    for (int c = 0; c < p_cells[i]->num_candidates; c++)
                    {
                        combinedCandidates[p_cells[i]->candidates[c] - 1] = 1;
                    }

                    for (int c = 0; c < p_cells[j]->num_candidates; c++)
                    {
                        combinedCandidates[p_cells[j]->candidates[c] - 1] = 1;
                    }

                    for (int c = 0; c < p_cells[k]->num_candidates; c++)
                    {
                        combinedCandidates[p_cells[k]->candidates[c] - 1] = 1;
                    }

                    // Check if there are exactly 3 candidates in the combined set
                    int count = 0;
                    for (int c = 0; c < BOARD_SIZE; c++)
                    {
                        if (combinedCandidates[c])
                        {
                            count++;
                        }
                    }

                    if (count == 3)
                    {
                        // Hidden triple found, remove other candidates from the unit
                        for (int m = 0; m < unit_size; m++)
                        {
                            if (m != i && m != j && m != k)
                            {
                                for (int value = 1; value <= BOARD_SIZE; value++)
                                {
                                    if (combinedCandidates[value - 1])
                                    {
                                        apply_constraint(&p_cells[m], value);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}