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

void translation(string step, motion& motion)
{
    motion.y1 = BOARD_SIZE - ((int)step[1] - (int)'0');
    motion.x1 = (int)step[0] - (int)'a';
    motion.y2 = BOARD_SIZE - ((int)step[4] - (int)'0');
    motion.x2 = (int)step[3] - (int)'a';
}

bool check_step(
        string step,
        motion motion,
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        bool move_white)
{
    switch (step.size()) {
    case 5:
        if (!((step[2] == '-') || (step[2] == 'x'))) {
            cout << "\nError: Unknown step type" << endl;
            return false;
        }
        if ((motion.x1 > 7) || (motion.x1 < 0) || (motion.x2 > 7)
            || (motion.x2 < 0) || (motion.y1 > 7) || (motion.y1 < 0)
            || (motion.y2 > 7) || (motion.y2 < 0)) {
            cout << "\nError: Going off the board" << endl;
            return false;
        }
        if (chess_board[motion.y1][motion.x1] == ' ') {
            cout << "\nError: The starting cell is empty" << endl;
            return false;
        }
        if (!((chess_board[motion.y1][motion.x1] == 'p')
              || (chess_board[motion.y1][motion.x1] == 'P'))) {
            cout << "\nError: The input must move pawns" << endl;
            return false;
        }
        if (step[2] == '-') {
            if (motion.x1 != motion.x2) {
                cout << "\nError: Pawns only move straight ahead" << endl;
                return false;
            }
            if (chess_board[motion.y2][motion.x2] != ' ') {
                cout << "\nError: You cannot make a silent move to another "
                        "piece"
                     << endl;
                return false;
            }
            if (chess_board[motion.y1][motion.x1] == 'P') {
                if (move_white == false) {
                    cout << "\nError: Black must go" << endl;
                    return false;
                }
                if (motion.y1 == 6) {
                    if ((motion.y1 - motion.y2 > 2)
                        || (motion.y1 - motion.y2 < 1)) {
                        cout << "\nError: From the first move, pawns can move "
                                "1-2 squares"
                             << endl;
                        return false;
                    }
                } else {
                    if (motion.y1 - motion.y2 != 1) {
                        cout << "\nError: After the first move, pawns can only "
                                "move 1 square forward"
                             << endl;
                        return false;
                    }
                }
            }
            if (chess_board[motion.y1][motion.x1] == 'p') {
                if (move_white == true) {
                    cout << "\nError: White must go" << endl;
                    return false;
                }
                if (motion.y1 == 1) {
                    if ((motion.y2 - motion.y1 > 2)
                        || (motion.y2 - motion.y1 < 1)) {
                        cout << "\nError: From the first move, pawns can "
                                "move 1-2 squares"
                             << endl;
                        return false;
                    }
                } else {
                    if (motion.y2 - motion.y1 != 1) {
                        cout << "\nError: After the first move, pawns can "
                                "only move 1 square forward"
                             << endl;
                        return false;
                    }
                }
            }
        }
        if (step[2] == 'x') {
            if (chess_board[motion.y2][motion.x2] == ' ') {
                cout << "\nError: You can't take an empty cage" << endl;
                return false;
            }
            if (abs(motion.x1 - motion.x2) != 1) {
                cout << "\nError: You can only take diagonally 1 cell to "
                        "the sides"
                     << endl;
                return false;
            }
            if ((chess_board[motion.y1][motion.x1] == 'P')
                && (motion.y1 - motion.y2 != 1)) {
                cout << "\nError: You can only take diagonally 1 cell to "
                        "the sides"
                     << endl;
                return false;
            }
            if ((chess_board[motion.y1][motion.x1] == 'p')
                && (motion.y2 - motion.y1 != 1)) {
                cout << "\nError: You can only take diagonally 1 cell to "
                        "the sides"
                     << endl;
                return false;
            }
            if ((move_white == true)
                && (chess_board[motion.y1][motion.x1] == 'p')) {
                cout << "\nError: White must go" << endl;
                return false;
            }
            if ((move_white == false)
                && (chess_board[motion.y1][motion.x1] == 'P')) {
                cout << "\nError: Black must go" << endl;
                return false;
            }
        }
        break;
    case 6:
        cout << "Фигура" << endl;
        break;
    default:
        return false;
        break;
    }
    return true;
}

int turn(
        string step,
        motion motion,
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        bool& move_white)
{
    char type;
    translation(step, motion);
    if (check_step(step, motion, chess_board, move_white) == true) {
        type = chess_board[motion.y1][motion.x1];
        chess_board[motion.y1][motion.x1] = ' ';
        chess_board[motion.y2][motion.x2] = type;
        if (move_white == true)
            move_white = false;
        else
            move_white = true;
        return 0;
    } else
        return 1;
}

