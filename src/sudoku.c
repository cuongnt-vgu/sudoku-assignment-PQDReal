#include "sudoku.h"
#include "hidden_singles.h"
#include "hidden_pairs.h"
#include "hidden_triples.h"
#include "naked_pairs.h"
#include "naked_triples.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <sudoku string>\n", argv[0]);
        return 1;
    }

    SudokuBoard *board = malloc(sizeof(SudokuBoard));
    init_sudoku(board);
    load_sudoku(board, argv[1]);

    Cell **p_solved_cells = board->solved_cells;
    int solved_counter = board->solved_counter;

    while (board->solved_counter < BOARD_SIZE * BOARD_SIZE)
    {
        solved_counter = check_solved_cells(board, &p_solved_cells);

        if (show_possible(board, p_solved_cells, solved_counter))
        {
            continue;
        }

        // Loop over different solving techniques
        for (int technique = 0; technique < 5; technique++)
        {
            switch (technique)
            {
            case 0:
                hidden_singles(board);
                break;
            case 1:
                hidden_pairs(board);
                break;
            case 2:
                hidden_triples(board);
                break;
            case 3:
                naked_pairs(board);
                break;
            case 4:
                naked_triples(board);
                break;
            default:
                fprintf(stderr, "Invalid technique index.\n");
                return 1;
            }
        }
    }

    print_solution(board);

    // Clean up
    free_sudoku(board);
    free(board);
    return 0;
}