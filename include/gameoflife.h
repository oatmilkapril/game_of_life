#ifndef CAM_GOL_H 
#define CAM_GOL_H

typedef struct {
    int iteration;
    int board_width;
    int board_height;
    int *board;
} gameoflife;

gameoflife *gol_init();

void gol_update(gameoflife *gol);

int gol_get_cell(gameoflife *gol, int row, int col);

void *gol_free(gameoflife *gol);

void gol_print_board(gameoflife *gol);

#endif // CAM_GOL_H