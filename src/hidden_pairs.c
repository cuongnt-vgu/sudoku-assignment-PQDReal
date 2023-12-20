#include "hidden_pairs.h"
#include "sudoku.h"
#include "utils.c" // Assuming utils.h contains apply_constraint

// Helper function declarations
static void find_hidden_pairs_in_unit(Cell **p_cells, int unit_size);

// Implement hidden pairs logic here
int hidden_pairs(SudokuBoard *p_board)
{
    int hiddenPairsCounter = 0;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pairs_in_unit(p_board->p_rows[i], BOARD_SIZE);
    }

    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pairs_in_unit(p_board->p_cols[i], BOARD_SIZE);
    }

    // Check boxes
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pairs_in_unit(p_board->p_boxes[i], BOARD_SIZE);
    }

    return hiddenPairsCounter;
}

static void find_hidden_pairs_in_unit(Cell **p_cells, int unit_size)
{
    // Iterate through each pair of cells
    for (int i = 0; i < unit_size - 1; i++)
    {
        for (int j = i + 1; j < unit_size; j++)
        {
            // Check if both cells are empty
            if (p_cells[i]->value == 0 && p_cells[j]->value == 0)
            {
                // Check if both cells have exactly two candidates
                if (p_cells[i]->num_candidates == 2 && p_cells[j]->num_candidates == 2 &&
                    has_same_candidates(p_cells[i]->candidates, p_cells[j]->candidates))
                {
                    // Hidden pair found, remove other candidates from the unit
                    for (int k = 0; k < unit_size; k++)
                    {
                        if (k != i && k != j)
                        {
                            for (int c = 0; c < p_cells[i]->num_candidates; c++)
                            {
                                apply_constraint(&p_cells[k], p_cells[i]->candidates[c]);
                            }
                        }
                    }
                }
            }
        }
    }
}

// Function to check if two arrays have the same candidates
int has_same_candidates(const int *arr1, const int *arr2)
{
    for (int c = 0; c < BOARD_SIZE; c++)
    {
        if (arr1[c] != arr2[c])
        {
            return 0;
        }
    }
    return 1;
}
