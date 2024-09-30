#include "board.h"
// ask for notation for input, check if the move is valid, if valid, make the move on the board. Also check for captures or empty space
char chess_notation[BOARD_SIZE][BOARD_SIZE][2] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"

};


bool isPathClear(Board *board, int fromIndex[], int toIndex[]){
    int fromIndexRow = fromIndex[0];
    int toIndexRow = toIndex[0];
    int fromIndexCol = fromIndex[1];
    int toIndexCol = toIndex[1];


    //maybe change from nested loop to something else if the row or column doesn't change aka rook capture
    for(int c = fromIndexCol + 1; c < toIndexCol - 1; c++){
        for(int r = fromIndexRow + 1; r < fromIndexRow - 1; r++){
            if(board->squares[r][c] != EMPTY)
                return false;
            else
                return true;




        }
    }
    return true;

}

bool knight_check(Board *board, int fromIndex[], int toIndex[]){

    int fromRow = fromIndex[0];
    int fromCol = fromIndex[1];
    int toRow = toIndex[0];
    int toCol = toIndex[1];


if(((fromRow + 2 == toRow) && (fromCol + 1 == toCol))  || 
((fromRow - 2 == toRow) && (fromCol - 1  == toCol)) ||  
((fromRow + 1 == toRow) && (fromCol + 2 == toCol)) || 
((fromRow + 2 == toRow) && (fromCol - 1 == toCol)) || 
((fromRow - 2 == toRow) && (fromCol + 1 == toCol)) || 
((fromRow - 1 == toRow) && (fromCol - 2 == toCol)) || 
((fromRow + 1 == toRow) && (fromCol - 2 == toCol)) || 
((fromRow - 1 == toRow) && (fromCol + 2 == toCol))){

    return true;

}



    return false;
}
void setup_game(Board *board)
{
    board->player1[0] = 0;
    board->player1[1] = WHITE;
    board->player2[0] = 0;
    board->player2[1] = BLACK;

    // keep track of who's turn it is in the game loop
}
bool is_valid(Board *board, int fromIndex[], int toIndex[])
{
    int fromRow = fromIndex[0];
    int fromCol = fromIndex[1];
    int toRow = toIndex[0];
    int toCol = toIndex[1];

    //need to add a check for check and checkmate
    
    // pawn capture black then white check

    if ((board->squares[toRow][toCol] != EMPTY) && (((board->squares[fromRow][fromCol] == BLACK_PAWN) && (board->squares[toRow][toCol] > 0) && (fromRow + 1 == toRow && fromCol + 1 == toCol)) ||
                                                    ((board->squares[fromRow][fromCol] == WHITE_PAWN) && (board->squares[toRow][toCol] < 0) && (fromRow - 1 == toRow && fromCol - 1 == toCol))))
        return true;

    // pawn move to empty space on mid game
    // maybe also check if it's white or black's turn
    else if ((board->squares[toRow][toCol] == EMPTY) && (((board->squares[fromRow][fromCol] == BLACK_PAWN) && (fromRow + 1 == toRow && fromCol == toCol)) ||
                                                         ((board->squares[fromRow][fromCol] == WHITE_PAWN) && (fromRow - 1 == toRow && fromCol == toCol))))
    {
        return true;
    }
    // pawn move if round start
    else if (((fromRow == 1 || fromRow == 6) && (board->squares[toRow][toCol] == EMPTY)) && (((board->squares[fromRow][fromCol] == BLACK_PAWN) && (fromRow + 2 == toRow && fromCol == toCol)) ||
                                                                                             ((board->squares[fromRow][fromCol] == WHITE_PAWN) && (fromRow - 2 == toRow && fromCol == toCol))))
    {
        return true;
    }

    // bishop check

    // bishop capture
     //check if path is clear
    if ((board->squares[toRow][toCol] != EMPTY) && (((board->squares[fromRow][fromCol] == BLACK_BISHOP) && (board->squares[toRow][toCol] > 0) && (abs(fromRow - toRow) == abs(fromCol - toCol))) ||
                                                    ((board->squares[fromRow][fromCol] == WHITE_BISHOP) && (board->squares[toRow][toCol] < 0) && (abs(fromRow - toRow) == abs(fromCol - toCol)))))
        return true;

    // bishop move to empty space
    else if ((board->squares[toRow][toCol] == EMPTY) && (((board->squares[fromRow][fromCol] == BLACK_BISHOP) && (abs(fromRow - toRow) == abs(fromCol - toCol))) ||
                                                         ((board->squares[fromRow][fromCol] == WHITE_BISHOP) && (abs(fromRow - toRow) == abs(fromCol - toCol)))))
    {
        return true;
    }
    // pawn move if round start



    //Knight capture

    if ((board->squares[toRow][toCol] != EMPTY) && (((board->squares[fromRow][fromCol] == BLACK_KNIGHT) && (board->squares[toRow][toCol] > 0) && ( knight_check(board, fromIndex, toIndex) == true)) ||
                                                    ((board->squares[fromRow][fromCol] == WHITE_KNIGHT) && (board->squares[toRow][toCol] < 0) && (knight_check(board, fromIndex, toIndex) == true))))
        return true;

    // Knight move to an empty space
    else if ((board->squares[toRow][toCol] == EMPTY) && (((board->squares[fromRow][fromCol] == BLACK_KNIGHT) && (knight_check(board, fromIndex, toIndex) == true)) ||
                                                         ((board->squares[fromRow][fromCol] == WHITE_KNIGHT) && (knight_check(board, fromIndex, toIndex) == true))))
    {
        return true;
    }

    //Rook Capture
    //check if path is clear

    if (((board->squares[toRow][toCol] != EMPTY) && (((board->squares[fromRow][fromCol] == BLACK_ROOK) && (board->squares[toRow][toCol] > 0) && (fromRow == toRow || fromCol == toCol)) ||
                                                    ((board->squares[fromRow][fromCol] == WHITE_ROOK) && (board->squares[toRow][toCol] < 0) && (fromRow == toRow || fromCol == toCol)))) && isPathClear(board, fromIndex, toIndex) == true)
        return true;

    // bishop move to empty space
    else if (((board->squares[toRow][toCol] == EMPTY) && (((board->squares[fromRow][fromCol] == BLACK_ROOK || board->squares[fromRow][fromCol] == WHITE_ROOK) &&
    (fromRow == toRow || fromCol == toCol)))) && isPathClear(board, fromIndex, toIndex) == true)
    {
        return true;
    }





















    return false;
}

int check_turn(Board *board)
{

    if (board->move_turn % 2 == 0)
        return BLACK;
    else
        return WHITE;

    printf("%i", board->move_turn);
}

int make_move(Board *board, int fromIndex[], int toIndex[])
{
    // change fromIndex and toIndex into one array

    if (check_turn(board) == BLACK && board->squares[fromIndex[0]][fromIndex[1]] > 0)
    {
        printf("it's Black's turn. Try again with black.\n");
        return -1;
    }
    else if (check_turn(board) == WHITE && board->squares[fromIndex[0]][fromIndex[1]] < 0)
    {
        printf("it's White's turn. Try again with black.\n");
        return -1;
    }

    if (board->squares[fromIndex[0]][fromIndex[1]] != EMPTY &&
        (board->squares[toIndex[0]][toIndex[1]] == EMPTY ||                                                 // Destination is empty
         (board->squares[toIndex[0]][toIndex[1]] < 0 && board->squares[fromIndex[0]][fromIndex[1]] > 0) ||  // White capturing Black
         (board->squares[toIndex[0]][toIndex[1]] > 0 && board->squares[fromIndex[0]][fromIndex[1]] < 0)) && // Black capturing White
        is_valid(board, fromIndex, toIndex))
    {

        printf("You have moved your piece to the square. \n");
        board->squares[toIndex[0]][toIndex[1]] = board->squares[fromIndex[0]][fromIndex[1]];
        board->squares[fromIndex[0]][fromIndex[1]] = EMPTY;
    }
    else if (!is_valid(board, fromIndex, toIndex))
    {
        printf("This move is not valid");
        return -1;
    }
    // finish the rest of the conditions

    
    return 0;
}

void convert_notation(char *letterNotation, int *indexNotation)
{

    char letter = letterNotation[0];
    int index;
    switch (letter)
    {

    case 'a':
        index = 0;
        break;
    case 'b':
        index = 1;
        break;
    case 'c':
        index = 2;
        break;
    case 'd':
        index = 3;
        break;
    case 'e':
        index = 4;
        break;
    case 'f':
        index = 5;
        break;
    case 'g':
        index = 6;
        break;
    case 'h':
        index = 7;
        break;

    default:
        index = -1;
        break;
    }

    if (index == -1)
    {
        printf("Invalid column in notation: %s\n", letterNotation);
        return;
    }

    int row = letterNotation[1] - '0';
    if (row < 1 || row > 8)
    {
        printf("Invalid row in notation: %s\n", letterNotation);
        return;
    }

    indexNotation[0] = 8 - row; // Convert 1-based row to 0-based
    indexNotation[1] = index;   // Column already calculated

    if (indexNotation[0] < 0 || indexNotation[0] >= 8 || indexNotation[1] < 0 || indexNotation[1] >= 8)
    {
        printf("Invalid move: out of bounds.\n");
        return;
    }
}
void game_loop(Board *board)
{
    int move[2];
    char fromSquare[2], toSquare[2];
    int fromIndex[2], toIndex[2];

    char letter = fromSquare[0];
    int index;
    int fromIndex_size = sizeof(fromIndex) / sizeof(fromIndex[0]);
    
    printf("Welcome to chess.\n Here is the starting board.\n");
    do
    {
        print_board(board);
        printf("Enter your move with From and To separated by a comma, \n");
        scanf("%2s,%2s", fromSquare, toSquare);

        convert_notation(fromSquare, fromIndex);
        convert_notation(toSquare, toIndex);

        if (make_move(board, fromIndex, toIndex) == -1)
        {
            printf("Your move was not valid try again.\n");
            continue;
        }
        else
        {
            printf("valid move");
        }

        // fromIndex[1] = (int)fromSquare[1];
        // toIndex[1] = (int)toSquare[1];

        printf("Here is the converted notation\n");
        printArray(fromIndex, fromIndex_size);
        printArray(toIndex, fromIndex_size);
        board->move_turn++;

    } while (strcmp(fromSquare, "quit") != 0);

    /*setup game pieces with sides, score, default.
    take input for move (chess notation)
    check if move is valid
    if space is not empty, capture and increase score.

    */
}

void init_board(Board *board)
{

    memset(board->squares, 0, sizeof(int) * BOARD_SIZE * BOARD_SIZE);
    int non_pawn_white_pieces[8] = {4, 2, 3, 5, 6, 3, 2, 4};
    int non_pawn_black_pieces[8] = {-4, -2, -3, -6, -5, -3, -2, -4};

    memcpy(board->non_pawn_white_pieces, non_pawn_white_pieces, sizeof(int) * BOARD_SIZE);
    memcpy(board->non_pawn_black_pieces, non_pawn_black_pieces, sizeof(int) * BOARD_SIZE);
    board->move_turn = 1;
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {

            if (r == 0)
                board->squares[r][c] = board->non_pawn_black_pieces[c];

            else if (r == 1)
                board->squares[r][c] = BLACK_PAWN;
            else if (r == 6)
                board->squares[r][c] = WHITE_PAWN;

            else if (r == 7)
                board->squares[r][c] = board->non_pawn_white_pieces[c];
        }
    }
}

void print_board(Board *board)
{
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (r < 2)
                printf("%i %s", board->squares[r][c], " ");
            else
                printf("%i %s", board->squares[r][c], "  ");
        }
        printf("\n");
    }
}

void printArray(int arr[], int size)
{

    for (int i = 0; i < size; i++)
    {
        printf("%i\n", arr[i]);
    }
}
