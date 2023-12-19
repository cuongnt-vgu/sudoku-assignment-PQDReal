#include "hidden_triples.h"
#include "sudoku.h"

#include <string.h>

static int find_hidden_triples_in_unit(Cell **p_cells, int unit_size);

// Implement hidden triples logic here
int hidden_triples(SudokuBoard *p_board)
{
    int hiddenTriplesCounter = 0;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hiddenTriplesCounter += find_hidden_triples_in_unit(p_board->p_rows[i], BOARD_SIZE);
    }

    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hiddenTriplesCounter += find_hidden_triples_in_unit(p_board->p_cols[i], BOARD_SIZE);
    }

    // Check boxes
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        hiddenTriplesCounter += find_hidden_triples_in_unit(p_board->p_boxes[i], BOARD_SIZE);
    }

    return hiddenTriplesCounter;
}


static int find_hidden_triples_in_unit(Cell **p_cells, int unit_size)
{
    int hiddenTriplesCounter = 0;

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
                        int candidateValue = p_cells[i]->candidates[c] - 1;
                        if (candidateValue >= 0 && candidateValue < BOARD_SIZE) {
                            combinedCandidates[candidateValue] = 1;
                        }
                    }

                    for (int c = 0; c < p_cells[j]->num_candidates; c++)
                    {
                        int candidateValue = p_cells[j]->candidates[c] - 1;
                        if (candidateValue >= 0 && candidateValue < BOARD_SIZE) {
                            combinedCandidates[candidateValue] = 1;
                        }
                    }

                    for (int c = 0; c < p_cells[k]->num_candidates; c++)
                    {
                        int candidateValue = p_cells[k]->candidates[c] - 1;
                        if (candidateValue >= 0 && candidateValue < BOARD_SIZE) {
                            combinedCandidates[candidateValue] = 1;
                        }
                    }

                    // Check if there are exactly 3 candidates in the combined set
                    int count = 0;
                    int uniqueCandidates[3] = {0};

                    for (int c = 0; c < BOARD_SIZE && count < 3; c++)
                    {
                        if (combinedCandidates[c])
                        {
                            uniqueCandidates[count++] = c + 1;
                        }
                    }

                    if (count == 3)
                    {
                        // Hidden triple found, remove other candidates from the unit
                        for (int m = 0; m < unit_size; m++)
                        {
                            if (m != i && m != j && m != k)
                            {
                                for (int c = 0; c < 3; c++)
                                {
                                    apply_constraint(&p_cells[m], uniqueCandidates[c]);
                                }
                            }
                        }
                        hiddenTriplesCounter++;
                    }
                }
            }
        }
    }

    return hiddenTriplesCounter;
}
