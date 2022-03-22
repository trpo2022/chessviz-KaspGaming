#pragma once

#include <clocale>
#include <cmath>
#include <iostream>
#include <string>

#define BOARD_SIZE 8

using namespace std;

struct motion {
    int y1;
    int x1;
    int y2;
    int x2;
};

void print_board(char chess_board[BOARD_SIZE][BOARD_SIZE]);

void translation(string step, motion& motion);

bool check_step(
        string step,
        motion motion,
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        bool move_white);

int turn(
        string step,
        motion motion,
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        bool& move_white);
