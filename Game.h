

#ifndef BOARDGAME_GAME_H
#define BOARDGAME_GAME_H

#include "Connect_Ultimate.h"



class Game {
private:
    Connect_Ultimate roundGame;
    char roundBoards[2][3][3]; // 2 round 3x3 table
    int xScore;
    int oScore;

public:
    Game();
    void startGame();
    void playNormalRound(int roundNumber);
    void playThirdRound();
    void printFinalWinner();
};
#endif //BOARDGAME_GAME_H