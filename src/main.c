#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"


int main()
{
    Board *board = (Board*)malloc(sizeof(Board));
    init_board(board);
    game_loop(board);
    return 0;
}