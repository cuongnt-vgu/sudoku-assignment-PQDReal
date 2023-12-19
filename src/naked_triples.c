#include "naked_triples.h"
#include "sudoku.h"

int nakedTriplesCounter = 0;

// Helper function declarations
static void find_naked_triples_in_unit(Cell **p_cells, int unit_size);

// Implement naked triples logic here
int naked_triples(SudokuBoard *p_board)
{
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_triples_in_unit(p_board->p_rows[i], BOARD_SIZE);
    }

    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_triples_in_unit(p_board->p_cols[i], BOARD_SIZE);
    }

    // Check boxes
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_triples_in_unit(p_board->p_boxes[i], BOARD_SIZE);
    }

    return nakedTriplesCounter;
}

static void find_naked_triples_in_unit(Cell **p_cells, int unit_size)
{
    // Iterate through each triple of cells
    for (int i = 0; i < unit_size - 2; i++)
    {
        for (int j = i + 1; j < unit_size - 1; j++)
        {
            for (int k = j + 1; k < unit_size; k++)
            {
                // Check if all three cells are empty
                if (p_cells[i]->value == 0 && p_cells[j]->value == 0 && p_cells[k]->value == 0)
                {
                    // Check if these three cells have the same three possibilities
                    if (has_same_candidates_t(p_cells[i]->candidates, p_cells[j]->candidates, p_cells[k]->candidates))
                    {
                        // Naked triple found, remove candidates from other cells in the unit
                        nakedTriplesCounter++;
                    }
                }
            }
        }
    }
}

// Function to check if three arrays have the same candidates
int has_same_candidates_t(const int *arr1, const int *arr2, const int *arr3)
{
    for (int c = 0; c < BOARD_SIZE; c++)
    {
        if (arr1[c] != arr2[c] || arr1[c] != arr3[c])
        {
            return 0;
        }
    }
    return 1;
}