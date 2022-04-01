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
    switch (step.size()) {
    case 5:
        motion.y1 = BOARD_SIZE - ((int)step[1] - (int)'0');
        motion.x1 = (int)step[0] - (int)'a';
        motion.y2 = BOARD_SIZE - ((int)step[4] - (int)'0');
        motion.x2 = (int)step[3] - (int)'a';
        break;
    case 6:
        if (step[5] != '#') {
            motion.y1 = BOARD_SIZE - ((int)step[2] - (int)'0');
            motion.x1 = (int)step[1] - (int)'a';
            motion.y2 = BOARD_SIZE - ((int)step[5] - (int)'0');
            motion.x2 = (int)step[4] - (int)'a';
        } else {
            motion.y1 = BOARD_SIZE - ((int)step[1] - (int)'0');
            motion.x1 = (int)step[0] - (int)'a';
            motion.y2 = BOARD_SIZE - ((int)step[4] - (int)'0');
            motion.x2 = (int)step[3] - (int)'a';
        }
        break;
    case 7:
        motion.y1 = BOARD_SIZE - ((int)step[2] - (int)'0');
        motion.x1 = (int)step[1] - (int)'a';
        motion.y2 = BOARD_SIZE - ((int)step[5] - (int)'0');
        motion.x2 = (int)step[4] - (int)'a';
    default:
        break;
    }
}

bool king_step(
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        motion motion,
        bool error_output)
{
    if (!((chess_board[motion.y1][motion.x1] == 'K')
          || (chess_board[motion.y1][motion.x1] == 'k'))) {
        if (error_output == true)
            cout << "\nError: Wrong body type" << endl;
        return false;
    }
    if ((abs(motion.y2 - motion.y1) > 1) || (abs(motion.x2 - motion.x1) > 1)
        || ((motion.x2 - motion.x1 == 0) && (motion.y2 - motion.y1 == 0))) {
        cout << "\nError: Wrong move" << endl;
        return false;
    }
    return true;
}

bool queen_step(
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        motion motion,
        bool error_output)
{
    if (!((chess_board[motion.y1][motion.x1] == 'Q')
          || (chess_board[motion.y1][motion.x1] == 'q'))) {
        if (error_output == true)
            cout << "\nError: Wrong body type" << endl;
        return false;
    }
    if (!((abs(motion.x1 - motion.x2) == abs(motion.y1 - motion.y2))
          || ((motion.y2 - motion.y1 == 0) && (abs(motion.x1 - motion.x2) > 0))
          || ((motion.x2 - motion.x1 == 0)
              && (abs(motion.y1 - motion.y2) > 0)))) {
        cout << "\nError: Wrong move" << endl;
        return false;
    }
    if ((motion.y2 - motion.y1 == 0) && (abs(motion.x1 - motion.x2) > 0)) {
        if (motion.x2 > motion.x1) {
            motion.x1++;
            while (motion.x2 > motion.x1) {
                if (chess_board[motion.y1][motion.x1] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x1++;
            }
        }
        if (motion.x1 > motion.x2) {
            motion.x2++;
            while (motion.x1 > motion.x2) {
                if (chess_board[motion.y2][motion.x2] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x2++;
            }
        }
    }
    if ((motion.x2 - motion.x1 == 0) && (abs(motion.y1 - motion.y2) > 0)) {
        if (motion.y2 > motion.y1) {
            motion.y1++;
            while (motion.y2 > motion.y1) {
                if (chess_board[motion.y1][motion.x1] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.y1++;
            }
        }
        if (motion.y1 > motion.y2) {
            motion.y2++;
            while (motion.y1 > motion.y2) {
                if (chess_board[motion.y2][motion.x2] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x2++;
            }
        }
    }
    if (abs(motion.x1 - motion.x2) == abs(motion.y1 - motion.y2)) {
        if ((motion.x1 > motion.x2) && (motion.y1 > motion.y2)) {
            motion.x2++;
            motion.y2++;
            while ((motion.x1 > motion.x2) && (motion.y1 > motion.y2)) {
                if (chess_board[motion.y2][motion.x2] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x2++;
                motion.y2++;
            }
        }
        if ((motion.x1 > motion.x2) && (motion.y1 < motion.y2)) {
            motion.x2++;
            motion.y2--;
            while ((motion.x1 > motion.x2) && (motion.y1 < motion.y2)) {
                if (chess_board[motion.y2][motion.x2] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x2++;
                motion.y2--;
            }
        }
        if ((motion.x1 < motion.x2) && (motion.y1 > motion.y2)) {
            motion.x2--;
            motion.y2++;
            while ((motion.x1 < motion.x2) && (motion.y1 > motion.y2)) {
                if (chess_board[motion.y2][motion.x2] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x2--;
                motion.y2++;
            }
        }
        if ((motion.x1 < motion.x2) && (motion.y1 < motion.y2)) {
            motion.x1++;
            motion.y1++;
            while ((motion.x1 < motion.x2) && (motion.y1 < motion.y2)) {
                if (chess_board[motion.y1][motion.x1] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x1++;
                motion.y1++;
            }
        }
    }
    return true;
}

bool rook_step(
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        motion motion,
        bool error_output)
{
    if (!((chess_board[motion.y1][motion.x1] == 'R')
          || (chess_board[motion.y1][motion.x1] == 'r'))) {
        if (error_output == true)
            cout << "\nError: Wrong body type" << endl;
        return false;
    }
    if (!(((motion.y2 - motion.y1 == 0) && (abs(motion.x1 - motion.x2) > 0))
          || ((motion.x2 - motion.x1 == 0)
              && (abs(motion.y1 - motion.y2) > 0)))) {
        cout << "\nError: Wrong move" << endl;
        return false;
    }
    if ((motion.y2 - motion.y1 == 0) && (abs(motion.x1 - motion.x2) > 0)) {
        if (motion.x2 > motion.x1) {
            motion.x1++;
            while (motion.x2 > motion.x1) {
                if (chess_board[motion.y1][motion.x1] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x1++;
            }
        }
        if (motion.x1 > motion.x2) {
            motion.x2++;
            while (motion.x1 > motion.x2) {
                if (chess_board[motion.y2][motion.x2] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x2++;
            }
        }
    }
    if ((motion.x2 - motion.x1 == 0) && (abs(motion.y1 - motion.y2) > 0)) {
        if (motion.y2 > motion.y1) {
            motion.y1++;
            while (motion.y2 > motion.y1) {
                if (chess_board[motion.y1][motion.x1] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.y1++;
            }
        }
        if (motion.y1 > motion.y2) {
            motion.y2++;
            while (motion.y1 > motion.y2) {
                if (chess_board[motion.y2][motion.x2] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x2++;
            }
        }
    }
    return true;
}

bool knight_step(
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        motion motion,
        bool error_output)
{
    if (!((chess_board[motion.y1][motion.x1] == 'N')
          || (chess_board[motion.y1][motion.x1] == 'n'))) {
        if (error_output == true)
            cout << "\nError: Wrong body type" << endl;
        return false;
    }
    if (!(((abs(motion.y2 - motion.y1) == 2)
           && (abs(motion.x1 - motion.x2) == 1))
          || ((abs(motion.x2 - motion.x1) == 2)
              && (abs(motion.y1 - motion.y2) == 1)))) {
        cout << "\nError: Wrong move" << endl;
        return false;
    }
    return true;
}

bool bishop_step(
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        motion motion,
        bool error_output)
{
    if (!((chess_board[motion.y1][motion.x1] == 'B')
          || (chess_board[motion.y1][motion.x1] == 'b'))) {
        if (error_output == true)
            cout << "\nError: Wrong body type" << endl;
        return false;
    }
    if (!(abs(motion.x1 - motion.x2) == abs(motion.y1 - motion.y2))) {
        cout << "\nError: Wrong move" << endl;
        return false;
    }
    if (abs(motion.x1 - motion.x2) == abs(motion.y1 - motion.y2)) {
        if ((motion.x1 > motion.x2) && (motion.y1 > motion.y2)) {
            motion.x2++;
            motion.y2++;
            while ((motion.x1 > motion.x2) && (motion.y1 > motion.y2)) {
                if (chess_board[motion.y2][motion.x2] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x2++;
                motion.y2++;
            }
        }
        if ((motion.x1 > motion.x2) && (motion.y1 < motion.y2)) {
            motion.x2++;
            motion.y2--;
            while ((motion.x1 > motion.x2) && (motion.y1 < motion.y2)) {
                if (chess_board[motion.y2][motion.x2] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x2++;
                motion.y2--;
            }
        }
        if ((motion.x1 < motion.x2) && (motion.y1 > motion.y2)) {
            motion.x2--;
            motion.y2++;
            while ((motion.x1 < motion.x2) && (motion.y1 > motion.y2)) {
                if (chess_board[motion.y2][motion.x2] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x2--;
                motion.y2++;
            }
        }
        if ((motion.x1 < motion.x2) && (motion.y1 < motion.y2)) {
            motion.x1++;
            motion.y1++;
            while ((motion.x1 < motion.x2) && (motion.y1 < motion.y2)) {
                if (chess_board[motion.y1][motion.x1] != ' ') {
                    cout << "Error: You cannot step over pieces" << endl;
                    return false;
                }
                motion.x1++;
                motion.y1++;
            }
        }
    }
    return true;
}

bool pawn_step(
        string step,
        motion motion,
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        bool move_white)
{
    if (!((step[2] == '-') || (step[2] == 'x'))) {
        cout << "\nError: Unknown step type" << endl;
        return false;
    }
    if ((motion.x1 > 7) || (motion.x1 < 0) || (motion.x2 > 7) || (motion.x2 < 0)
        || (motion.y1 > 7) || (motion.y1 < 0) || (motion.y2 > 7)
        || (motion.y2 < 0)) {
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
        if (((move_white == true)
             && ((chess_board[motion.y2][motion.x2] >= 65)
                 && (chess_board[motion.y2][motion.x2] <= 90)))
            || ((move_white == false)
                && ((chess_board[motion.y2][motion.x2] >= 97)
                    && (chess_board[motion.y2][motion.x2] <= 122)))) {
            cout << "\nError: You cannot attack your pieces" << endl;
            return false;
        }
    }

    return true;
}

bool check_step(
        string step,
        motion motion,
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        bool move_white)
{
    bool error_output = true;
    switch (step.size()) {
    case 5:
        if (pawn_step(step, motion, chess_board, move_white) == false)
            return false;
        break;
    case 6:
        if (step[5] != '#') {
            if (!((step[3] == '-') || (step[3] == 'x'))) {
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
            if ((chess_board[motion.y2][motion.x2] != ' ')
                && (step[3] == '-')) {
                cout << "\nError: You cannot make a silent move to another "
                        "piece"
                     << endl;
                return false;
            }
            if ((chess_board[motion.y2][motion.x2] == ' ')
                && (step[3] == 'x')) {
                cout << "\nError: You can't take an empty cage" << endl;
                return false;
            }
            if ((move_white == false)
                && ((chess_board[motion.y1][motion.x1] >= 65)
                    && (chess_board[motion.y1][motion.x1] <= 90))) {
                cout << "\nError: Black must go" << endl;
                return false;
            }
            if ((move_white == true)
                && ((chess_board[motion.y1][motion.x1] >= 97)
                    && (chess_board[motion.y1][motion.x1] <= 122))) {
                cout << "\nError: White must go" << endl;
                return false;
            }
            if (((move_white == true)
                 && ((chess_board[motion.y2][motion.x2] >= 65)
                     && (chess_board[motion.y2][motion.x2] <= 90)))
                || ((move_white == false)
                    && ((chess_board[motion.y2][motion.x2] >= 97)
                        && (chess_board[motion.y2][motion.x2] <= 122)))) {
                cout << "\nError: You cannot attack your pieces" << endl;
                return false;
            }
            if (step[0] == 'K') { // King
                if (king_step(chess_board, motion, error_output) == false)
                    return false;
            }
            if (step[0] == 'Q') { // Queen
                if (queen_step(chess_board, motion, error_output) == false)
                    return false;
            }
            if (step[0] == 'R') { // Rook
                if (rook_step(chess_board, motion, error_output) == false)
                    return false;
            }
            if (step[0] == 'N') { // kNight
                if (knight_step(chess_board, motion, error_output) == false)
                    return false;
            }
            if (step[0] == 'B') { // Bishop
                if (bishop_step(chess_board, motion, error_output) == false)
                    return false;
            }
        }
        if (step[5] == '#') {
            if (step[2] != 'x') {
                cout << "\nError: Wrong mate" << endl;
                return false;
            }
            if (pawn_step(step, motion, chess_board, move_white) == false)
                return false;
        }
        break;
    case 7:
        error_output = false;
        if (step[6] != '#') {
            cout << "\nError: Wrong step" << endl;
            return false;
        }
        if (step[3] != 'x') {
            cout << "\nError: Wrong mate" << endl;
            return false;
        }
        if ((move_white == false)
            && ((chess_board[motion.y1][motion.x1] >= 65)
                && (chess_board[motion.y1][motion.x1] <= 90))) {
            cout << "\nError: Black must go" << endl;
            return false;
        }
        if ((move_white == true)
            && ((chess_board[motion.y1][motion.x1] >= 97)
                && (chess_board[motion.y1][motion.x1] <= 122))) {
            cout << "\nError: White must go" << endl;
            return false;
        }
        if (((move_white == true)
             && ((chess_board[motion.y2][motion.x2] >= 65)
                 && (chess_board[motion.y2][motion.x2] <= 90)))
            || ((move_white == false)
                && ((chess_board[motion.y2][motion.x2] >= 97)
                    && (chess_board[motion.y2][motion.x2] <= 122)))) {
            cout << "\nError: You cannot attack your pieces" << endl;
            return false;
        }
        if ((knight_step(chess_board, motion, error_output) == false)
            && (king_step(chess_board, motion, error_output) == false)
            && (queen_step(chess_board, motion, error_output) == false)
            && (rook_step(chess_board, motion, error_output) == false)
            && (knight_step(chess_board, motion, error_output) == false))
            return false;
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
