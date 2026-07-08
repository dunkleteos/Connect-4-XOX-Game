/* Yaren Barış– 2637460, Efe Özgür – 2638104
We read and accept the submission rules and the extra rules specified
in each question. This is our own work that is done by us only */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"


using namespace std;

Game::Game(){// Before the game starts, set scores to zero and sets cell values all zero
    int i,j,k;

    xScore = 0;
    oScore = 0;

    for (i = 0; i < 2;i++)
    {
        for (j = 0; j < 3;j++) {
            for (k = 0; k < 3; k++) {
                roundBoards[i][j][k] = ' '; //Empty value for all cells
            }
        }
    }
}

void Game::startGame(){//game is best of three. That means 2 point wins
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

void Game::playNormalRound(int roundNumber){//regular round there is no need for winner calculate scores and prints
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

void Game::playThirdRound(){// on that round score should be 1-1(tieBrake). So tieBreaak function calculates the board score and decides the winner
    char thirdWinner;

    cout << endl;
    cout << "Round 3 started." << endl;
    cout << "No player input will be taken in this round." << endl;

    roundGame.resetUltimate();
    thirdWinner = roundGame.calculateThirdRound(roundBoards[0], roundBoards[1]);

    if (thirdWinner == 'X'){
        xScore++;
    }
    else if (thirdWinner == 'O'){
        oScore++;
    }
}

void Game::printFinalWinner(){//Prints scores and winner
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