#ifndef BOARDGAME_BOARD_H
#define BOARDGAME_BOARD_H


class Board {
protected:
    char winner;
    int finished;
public:
    Board();
    virtual void print() = 0;
    virtual char getWinner() = 0;
    virtual int isFinished() = 0;
    virtual ~Board();
};

#endif