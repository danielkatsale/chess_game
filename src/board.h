#ifndef BOARD_H_
#define BOARD_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BOARD_SIZE 8
enum
{
    EMPTY,
    WHITE = 7,
    BLACK = -7,
    WHITE_PAWN = 1,
    WHITE_KNIGHT = 2,
    WHITE_BISHOP = 3,
    WHITE_ROOK = 4,
    WHITE_QUEEN = 5,
    WHITE_KING = 6,
    BLACK_PAWN = -1,
    BLACK_KNIGHT = -2,
    BLACK_BISHOP = -3,
    BLACK_ROOK = -4,
    BLACK_QUEEN = -5,
    BLACK_KING = -6
};





typedef struct {
    int squares[BOARD_SIZE][BOARD_SIZE];
    int non_pawn_white_pieces[8];
    int non_pawn_black_pieces[8];
    int color;
    int castle;
    int white_material;
    int black_material;
    int white_position;
    int black_position;
    //int ep[64];
    /*int all[64];
    int white[64];
    int black[64];
    int white_pawns[64];
    int black_pawns[64];
    int white_knights[64];
    int black_knights[64];
    int white_bishops[64];
    int black_bishops[64];
    int white_rooks[64];
    int black_rooks[64];
    int white_queens[64];
    int black_queens[64];
    int white_kings[64];
    int black_kings[64];*/
    int player1[18]; //keeps it's own score in the 0th index, the 1st index is the side its on, and then the rest of the array is the pieces it has captured.
    int player2[18];
    int move[2];
    int move_turn;
    
} Board;

void init_board(Board *board);
void start_game();
void game_loop(Board *board);
bool is_valid(Board *board, int fromIndex[], int toIndex[]);
void print_board(Board *board);
void convert_notation(char *letterNotation, int *indexNotation);
int make_move(Board *board, int fromIndex[], int toIndex[]);
void printArray(int arr[], int size);
bool knight_check(Board *board, int fromIndex[], int toIndex[]);
bool isPathClear(Board *board, int fromIndex[], int toIndex[]);












#endif