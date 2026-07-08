
#ifndef BOARDGAME_CONNECT_BOARD_H
#define BOARDGAME_CONNECT_BOARD_H
#include "Board.h"



class Connect_Board : public Board {
private:
    char cells[6][7];//This board subtype is the smallest boardType and its 6x7 sized.
    int filledCells;

public://We have some functions different from xox game board like isColumnFull, dropDisc because they are specific for only this bard game
    Connect_Board();
    void resetBoard();
    void dropDisc(int column, char player);
    int isColumnFull(int column);
    int checkWin(char player);
    int checkDraw();
    int tieBreaker();
    void print();
    char getWinner();
    int isFinished();
};

#endif