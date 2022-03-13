#include "chessviz.h"

void print_board(char chess_board[BOARD_SIZE][BOARD_SIZE])
{
    int i = 0, j = 0;
    cout << endl;
    for (i = 0; i < BOARD_SIZE; i++) {
        cout << BOARD_SIZE - i << "| ";
        for (j = 0; j < BOARD_SIZE; j++) {
            cout << chess_board[i][j] << " ";
        }
        cout << endl;
    }
    cout << " ------------------\n";
    cout << "   a b c d e f g h \n";
}
