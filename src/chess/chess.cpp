#include "libchessviz/chessviz.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

    system("clear");
    motion motion;
    cout << "Добро пожаловть в шахматы! Пока что реализовано движение только пешек" << endl;
    cout << "Для выхода из программы ведите в терминал что-нибудь не относящееся к движению пешек\n" << endl;
    print_board(chess_board);
    string step;
    float number_of_turn = 1;
    bool move_white = true; 
    while (true) {
	cout << (int)number_of_turn << ". ";
	number_of_turn += 0.5;
    	cin >> step;
    	if (turn (step, motion, chess_board, move_white) != 0) return 1;
	print_board(chess_board);
	cout << endl;
    }
    return 0;
}

