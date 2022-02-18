#include <stdio.h>
#define chess_size 8
void printChess()
{
    int i = 0, j = 0;
    char ChessViz[8][8]
            = {"rnbqkbnr",
               "pppppppp",
               "        ",
               "        ",
               "        ",
               "        ",
               "PPPPPPPP",
               "RNBQKBNR"};
    printf("\n");
    for (i = 0; i < chess_size; i++) {
        printf("%d | ", i + 1);
        for (j = 0; j < chess_size; j++) {
            printf("%c | ", ChessViz[i][j]);
        }
        printf("\n");
    }
    printf("-----------------------------------\n");
    printf("    a | b | c | d | e | f | g | h |\n");
}

int main()
{
    printChess();
    return 0;
}

