#include <ctest.h>
#include <libchessviz/chessviz.h>

char chess_board[BOARD_SIZE][BOARD_SIZE]
        = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
           {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
           {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
           {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
           {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
           {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
           {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
           {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

motion motion;

CTEST(quiet_step_suite, step_size_false)
{
    string step = "Nb1-c3B";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(quiet_step_suite, quiet_running_true)
{
    string step = "e2-e4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(quiet_step_suite, quiet_running_true2)
{
    string step = "Nb1-c3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(quiet_step_suite, quiet_running_false)
{
    string step = "e2/e4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(quiet_step_suite, quiet_running_false2)
{
    string step = "Be1'e4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(quiet_step_suite, small_type)
{
    string step = "nb1-c3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(quiet_step_suite, move_to_non_empty_cell)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', ' ', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', 'p', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "e2-e4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(quiet_step_suite, quiet_running_pawn_2_step_false)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', 'P', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', ' ', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

    string step = "d3-d5";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(quiet_step_suite, move_from_empty_cell)
{
    string step = "e3-e4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(quiet_step_suite, going_out_of_field)
{
    string step = "e0-e2";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(quiet_step_suite, white_must_go_true)
{
    string step = "e2-e4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(quiet_step_suite, black_must_go_true)
{
    string step = "e7-e5";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, false, false);

    ASSERT_TRUE(result);
}

CTEST(quiet_step_suite, white_must_go_false)
{
    string step = "e7-e5";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(quiet_step_suite, black_must_go_false)
{
    string step = "e2-e4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, false, false);

    ASSERT_FALSE(result);
}

CTEST(take_step_suite, take_empty)
{
    string step = "e2xe4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(take_step_suite, friendly_fire)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', 'P', ' ', ' '},
               {'P', 'P', 'P', 'P', 'P', ' ', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "e2xf3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(pawn_step, type_is_true)
{
    string step = "e2-e3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(pawn_step, type_is_false)
{
    string step = "e1-e2";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(pawn_step, step_back)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', 'p', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', 'P', ' ', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "e4-e2";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(pawn_step, take_true)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', ' ', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', 'p', ' ', ' '},
               {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "e2xf3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(pawn_step, take_false)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', ' ', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', 'p', ' ', ' '},
               {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "f2xf3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(pawn_step, stepping_over_is_false)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', ' ', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', 'p', ' ', ' ', ' '},
               {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "e2-e4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(king_step, type_is_true)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', 'P', ' ', ' ', ' '},
               {'P', 'P', 'P', 'P', ' ', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Ke1-e2";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(king_step, type_is_false)
{
    string step = "Ke2-e3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(king_step, step_is_true)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', 'P', ' ', ' ', ' '},
               {'P', 'P', 'P', 'P', ' ', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Ke1-e2";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(king_step, step_is_false)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', 'P', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', 'P', ' ', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Ke1-e3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(king_step, step_is_true_2)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', 'P', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', ' ', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Ke1-d2";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(king_step, take_is_true)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', ' ', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', 'P', 'p', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Ke1xe2";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(queen_step, step_is_true)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', ' ', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Qd1-d4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(queen_step, step_is_true2)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', 'Q', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', ' ', 'K', 'B', 'N', 'R'}};
    string step = "Qd3-f3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(queen_step, step_is_true3)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', 'P', ' ', ' ', ' '},
               {'P', 'P', 'P', 'P', ' ', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Qd1-f3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(queen_step, step_is_flase)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', ' ', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Qd1-e3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(queen_step, stepping_over_is_false)
{
    string step = "Qd1-d4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(rook_step, step_is_true)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Ra1-a4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(rook_step, step_is_true2)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'R', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
               {' ', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Ra3-f3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(rook_step, stepping_over_is_false)
{
    string step = "Ra1-a4";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(bishop_step, step_is_true)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', ' ', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Bc1-e3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(bishop_step, step_is_false)
{
    string step = "Bc1-e3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}

CTEST(knight_step, step_is_true)
{
    string step = "Nb1-c3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(knight_step, step_is_true2)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', ' ', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Nb1-d2";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_TRUE(result);
}

CTEST(knight_step, step_is_false)
{
    char chess_board[BOARD_SIZE][BOARD_SIZE]
            = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
               {'P', 'P', 'P', ' ', 'P', 'P', 'P', 'P'},
               {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    string step = "Nb1-d3";
    translation(step, motion);
    bool result = check_step(step, motion, chess_board, true, false);

    ASSERT_FALSE(result);
}
