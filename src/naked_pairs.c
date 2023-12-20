#include "naked_pairs.h"
#include "sudoku.h"

// Helper function declarations
static void find_naked_pairs_in_unit(Cell **p_cells, int unit_size);

int nakedPairsCounter;

// Implement naked pairs logic here
int naked_pairs(SudokuBoard *p_board)
{
    nakedPairsCounter = 0;
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pairs_in_unit(p_board->p_rows[i], BOARD_SIZE);
    }

    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pairs_in_unit(p_board->p_cols[i], BOARD_SIZE);
    }

    // Check boxes
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pairs_in_unit(p_board->p_boxes[i], BOARD_SIZE);
    }

    return nakedPairsCounter;
}

static void find_naked_pairs_in_unit(Cell **p_cells, int unit_size)
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
                if (p_cells[i]->num_candidates == 2 && p_cells[j]->num_candidates == 2)
                {
                    // Check if the candidates in both cells are the same
                    if (has_same_candidates_p(p_cells[i]->candidates, p_cells[j]->candidates))
                    {
                        // Naked pair found, remove candidates from other cells in the unit
                        nakedPairsCounter++;
                    }
                }
            }
        }
    }
}

// Function to check if two arrays have the same candidates
int has_same_candidates_p(const int *arr1, const int *arr2)
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