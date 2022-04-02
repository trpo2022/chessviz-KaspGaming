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

bool king_step(
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        motion motion,
        bool error_output);

bool queen_step(
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        motion motion,
        bool error_output);

bool rook_step(
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        motion motion,
        bool error_output);

bool knight_step(
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        motion motion,
        bool error_output);

bool bishop_step(
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        motion motion,
        bool error_output);

bool pawn_step(
        string step,
        motion motion,
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        bool move_white, bool error_output);
	
bool check_step(
        string step,
        motion motion,
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        bool move_white, bool output);

int turn(
        string step,
        motion motion,
        char chess_board[BOARD_SIZE][BOARD_SIZE],
        bool& move_white);
