#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"

using namespace std;

Game::Game(){ // Oyundan önce skorları sıfırlar ve hücreleri temizler
    int i,j,k;

    xScore = 0;
    oScore = 0;

    for (i = 0; i < 2;i++)
    {
        for (j = 0; j < 3;j++) {
            for (k = 0; k < 3; k++) {
                roundBoards[i][j][k] = ' ';
            }
        }
    }
}

void Game::startGame(){
    srand(time(0));

    cout << "Ultimate Connect 4 Game Started" << endl;

    playNormalRound(1);

    if (xScore == 2 || oScore == 2){
        printFinalWinner();
        return;
    }

    playNormalRound(2);

    if (xScore == 2 || oScore == 2){
        printFinalWinner();
        return;
    }

    if (xScore == 1 && oScore == 1){
        playThirdRound();
    }

    printFinalWinner();
}

void Game::playNormalRound(int roundNumber){
    char roundWinner;

    cout << endl;
    cout << "Round " << roundNumber << " started." << endl;

    roundGame.resetUltimate();
    roundGame.playRound();

    roundWinner = roundGame.getWinner();

    if (roundWinner == 'D') {
        cout << "Large board ended with draw." << endl;
        cout << "This round will be restarted." << endl;
        playNormalRound(roundNumber);
        return;
    }

    if (roundWinner=='X'){
        xScore++;
    }
    else if (roundWinner == 'O'){
        oScore++;
    }

    roundGame.copyMetaBoard(roundBoards[roundNumber - 1]);

    cout << "Score" << endl;
    cout << "X: " << xScore << endl;
    cout << "O: " << oScore << endl;
}

void Game::playThirdRound(){
    char thirdWinner;

    cout << endl;
    cout << "Round 3 started. Both players, please take your turns." << endl;

    // 3. turda da otomatik hesaplama yerine tahtayı sıfırlayıp normal oyunu başlatıyoruz
    roundGame.resetUltimate();
    roundGame.playRound();

    thirdWinner = roundGame.getWinner();

    if (thirdWinner == 'D') {
        cout << "Large board ended with draw." << endl;
        cout << "This round will be restarted." << endl;
        playThirdRound();
        return;
    }

    if (thirdWinner == 'X'){
        xScore++;
    }
    else if (thirdWinner == 'O'){
        oScore++;
    }
}

void Game::printFinalWinner(){
    cout << endl;
    cout << "Final Score" << endl;
    cout << "X: " << xScore << endl;
    cout << "O: " << oScore << endl;

    if(xScore > oScore) {
        cout << "Player X wins the game." << endl;
    }
    else if(oScore > xScore) {
        cout << "Player O wins the game." << endl;
    }
    else{
        cout << "The game ended with draw." << endl;
    }
}