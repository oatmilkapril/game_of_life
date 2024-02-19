#include <stdlib.h>
#include <stdio.h>
#include "gameoflife.h"

void _reset_board(gameoflife *gol);
int _get_neighbor_count(gameoflife *gol, int row, int col);
void _set_cell(int *board, int width, int row, int col, int val);

gameoflife *gol_init(int board_width, int board_height) {
    gameoflife *gol = (gameoflife *) malloc(sizeof(gameoflife));

    gol->iteration = 1;
    gol->board_width = board_width;
    gol->board_height = board_height;
    gol->board = malloc(board_width * board_height * sizeof(int));

    _reset_board(gol);

    return gol;
}

void *gol_free(gameoflife *gol) {
    free(gol->board);
    free(gol);
}

void gol_update(gameoflife *gol) {
    int *new_board = malloc(gol->board_width * gol->board_height * sizeof(int));

    for (int row = 0; row < gol->board_height; row++) {
        for (int col = 0; col < gol->board_width; col++) {
            int value = gol->board[row * gol->board_width + col];

            int neighbor_count = _get_neighbor_count(gol, row, col);

            if (neighbor_count < 2) { // Underpopulation
                _set_cell(new_board, gol->board_width, row, col, 0);
            } else if (neighbor_count == 2) { // Steady
                _set_cell(new_board, gol->board_width, row, col, value);
            } else if (neighbor_count == 3) { // Reproduction
                _set_cell(new_board, gol->board_width, row, col, 1);
            } else if (neighbor_count > 3) { // Overpopulation
                _set_cell(new_board, gol->board_width, row, col, 0);
            } 
        }
    }

    free(gol->board);
    gol->board = new_board;
    gol->iteration++;
}

int gol_get_cell(gameoflife *gol, int row, int col) {
    return gol->board[row * gol->board_width + col];
}

void gol_print_board(gameoflife *gol) {
    char buffer[128];
    snprintf(buffer, 128, "/tmp/gol/%d.txt", gol->iteration);
    FILE *out_file = fopen(buffer, "w");

    for (int row = 0; row < gol->board_height; row++) {
        for (int col = 0; col < gol->board_width; col++) {
            int value = gol->board[row * gol->board_width + col];
            if (value == 0) {
                fprintf(out_file, "_");
            } else if (value == 1) {
                fprintf(out_file, "O");
            } else {
                fprintf(out_file, "?");
            }
        }
        fprintf(out_file, "\n");
    }

    fclose(out_file);
}

int _get_neighbor_count(gameoflife *gol, int row, int col) {
    int neighbor_count = 0;

    neighbor_count += gol_get_cell(gol, row - 1, col - 1);
    neighbor_count += gol_get_cell(gol, row - 1, col);
    neighbor_count += gol_get_cell(gol, row - 1, col + 1);

    neighbor_count += gol_get_cell(gol, row, col - 1);
    neighbor_count += gol_get_cell(gol, row, col + 1);

    neighbor_count += gol_get_cell(gol, row + 1, col - 1);
    neighbor_count += gol_get_cell(gol, row + 1, col);
    neighbor_count += gol_get_cell(gol, row + 1, col + 1);

    return neighbor_count;
}

void _reset_board(gameoflife *gol) {
    for (int row = 0; row < gol->board_height; row++) {
        for (int col = 0; col < gol->board_width; col++) {
            gol->board[row * gol->board_width + col] = 0;
        }
    }

    int row = gol->board_height / 2;
    int col = gol->board_width / 2;

    _set_cell(gol->board, gol->board_width, row, col, 1);
    _set_cell(gol->board, gol->board_width, row+1, col, 1);
    _set_cell(gol->board, gol->board_width, row+2, col, 1);
    _set_cell(gol->board, gol->board_width, row+2, col+1, 1);
    _set_cell(gol->board, gol->board_width, row+2, col+2, 1);
    _set_cell(gol->board, gol->board_width, row+1, col+2, 1);
    _set_cell(gol->board, gol->board_width, row, col+2, 1);
}

void _set_cell(int *board, int width, int row, int col, int val) {
    board[row * width + col] = val;
}

