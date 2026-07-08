#include <iostream>
#include <cstdlib>
#include "Connect_Ultimate.h"
using namespace std;

Connect_Ultimate::Connect_Ultimate() {
    resetUltimate();
}

void Connect_Ultimate::resetUltimate() {
    int i, j;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            smallBoards[i][j].resetBoard();
            metaBoard[i][j] = ' ';
        }
    }
    winner = ' ';
    finished = 0;
}

void Connect_Ultimate::playRound() {
    char currentPlayer;
    int moveResult;
    currentPlayer = 'X';
    while (finished == 0) {
        print();
        moveResult = makeMove(currentPlayer);
        if (moveResult == 1) {
            if (checkMetaWin(currentPlayer) == 1) {
                winner = currentPlayer;
                finished = 1;
                print();
                cout << "Round winner is " << winner << endl;
            }
            else if (checkMetaDraw() == 1) {
                winner = 'D';
                finished = 1;
                print();
                cout << "This round is draw." << endl;
            }
            else {
                if (currentPlayer == 'X') {
                    currentPlayer = 'O';
                }
                else {
                    currentPlayer = 'X';
                }
            }
        }
        else {
            cout << "Please try again." << endl;
        }
    }
}

int Connect_Ultimate::makeMove(char player) {
    int boardNumber;
    int column;
    int row, col;
    cout << "Player " << player << " turn." << endl;
    cout << "Choose small board number between 1 and 9: ";
    cin >> boardNumber;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error: Invalid input. Board number must be an integer." << endl;
        return 0;
    }
    if (boardNumber < 1 || boardNumber > 9) {
        cout << "Error: Invalid board number. Please enter a value between 1 and 9." << endl;
        return 0;
    }
    row = (boardNumber - 1) / 3;
    col = (boardNumber - 1) % 3;
    if (smallBoards[row][col].isFinished() == 1) {
        cout << "Error: Selected small board is already finished." << endl;
        return 0;
    }
    cout << "Choose column number between 1 and 7: ";
    cin >> column;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error: Invalid input. Column number must be an integer." << endl;
        return 0;
    }
    if (column < 1 || column > 7) {
        cout << "Error: Invalid column number. Please enter a value between 1 and 7." << endl;
        return 0;
    }
    if (smallBoards[row][col].isColumnFull(column) == 1) {
        cout << "Error: This column is full. Please choose another column." << endl;
        return 0;
    }
    smallBoards[row][col].dropDisc(column, player);
    updateMetaBoard();
    return 1;
}

void Connect_Ultimate::updateMetaBoard() {
    int i, j;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            if (smallBoards[i][j].isFinished() == 1) {
                metaBoard[i][j] = smallBoards[i][j].getWinner();
            }
        }
    }
}

int Connect_Ultimate::checkMetaWin(char player) {
    int i;
    for (i=0; i<3; i++) {
        if (metaBoard[i][0] == player &&
            metaBoard[i][1] == player &&
            metaBoard[i][2] == player) {
            return 1;
        }
    }
    for (i=0; i<3; i++) {
        if (metaBoard[0][i] == player &&
            metaBoard[1][i] == player &&
            metaBoard[2][i] == player) {
            return 1;
        }
    }
    if (metaBoard[0][0] == player &&
        metaBoard[1][1] == player &&
        metaBoard[2][2] == player) {
        return 1;
    }
    if (metaBoard[0][2] == player &&
        metaBoard[1][1] == player &&
        metaBoard[2][0] == player) {
        return 1;
    }
    return 0;
}

int Connect_Ultimate::checkMetaDraw() {
    int i, j;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            if (metaBoard[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void Connect_Ultimate::copyMetaBoard(char target[3][3]) {
    int i, j;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            target[i][j] = metaBoard[i][j];
        }
    }
}

void Connect_Ultimate::setMetaBoard(const char source[3][3]) {
    int i, j;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            metaBoard[i][j] = source[i][j];
        }
    }
}

void Connect_Ultimate::print() {
    int i, j;
    int boardNumber;

    cout << "\n=== KUCUK OYUN TAHTALARI (1-9) DURUMU ===" << endl;
    boardNumber = 1;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            cout << "--- Tahta No: " << boardNumber << " ";
            if (smallBoards[i][j].isFinished()) {
                cout << "(Bitti, Kazanan: " << smallBoards[i][j].getWinner() << ")";
            } else {
                cout << "(Devam Ediyor)";
            }
            cout << " ---" << endl;

            smallBoards[i][j].print();
            boardNumber++;
        }
    }

    cout << "========================================" << endl;
    cout << "Mevcut Meta Board Durumu: " << endl;
    cout << "-------------" << endl;
    boardNumber = 1;
    for (i=0; i<3; i++) {
        cout << "|";
        for (j=0; j<3; j++) {
            if (metaBoard[i][j] == ' ') {
                cout << boardNumber << " |";
            }
            else {
                cout << metaBoard[i][j] << " |";
            }
            boardNumber++;
        }
        cout << endl;
        cout << "-------------" << endl;
    }
    cout << "\n" << endl;
}

char Connect_Ultimate::getWinner() {
    return winner;
}

int Connect_Ultimate::isFinished() {
    return finished;
}