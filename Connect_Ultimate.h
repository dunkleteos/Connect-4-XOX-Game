#ifndef CONNECT_ULTIMATE_H
#define CONNECT_ULTIMATE_H
#include "Board.h"
#include "Connect_Board.h"

class Connect_Ultimate : public Board {
private:
    Connect_Board smallBoards[3][3];
    char metaBoard[3][3];
public:
    Connect_Ultimate();
    void resetUltimate();
    void playRound();
    int makeMove(char player);
    void updateMetaBoard();
    int checkMetaWin(char player);
    int checkMetaDraw();
    void copyMetaBoard(char target[3][3]);
    void setMetaBoard(const char source[3][3]); // const eklendi
    char calculateThirdRound(char round1[3][3], char round2[3][3]);
    char applyAddition(char first, char second);
    char applySubtraction(char first, char second);
    char randomTieBreaker();
    void print();
    char getWinner();
    int isFinished();
};

#endif