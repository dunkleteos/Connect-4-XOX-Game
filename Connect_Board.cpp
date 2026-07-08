#include <iostream>
#include <cstdlib> // rand() kullanimi icin eklendi
#include "Connect_Board.h"
using namespace std;

Connect_Board::Connect_Board() {
    resetBoard();
}

void Connect_Board::resetBoard() {
    int i;
    int j;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            cells[i][j] = ' ';
        }
    }
    filledCells = 0;
    winner = ' ';
    finished = 0;
}

void Connect_Board::dropDisc(int column, char player){
    int row;
    if (finished == 1) {
        cout << "Error: This small board is already finished." << endl;
        return;
    }
    if (column < 1 || column > 7) {
        cout << "Error: Invalid column number. Please enter a value between 1 and 7." << endl;
        return;
    }
    if (isColumnFull(column) == 1) {
        cout <<"Error: This column is full. Please choose another column." << endl;
        return;
    }
    column = column - 1;
    for(row = 5; row >= 0; row = row - 1) {
        if (cells[row][column]== ' '){
            cells[row][column]= player;
            filledCells++;
            if (checkWin(player) == 1) {
                winner = player;
                finished = 1;
            }
            else if (checkDraw() == 1) {
                winner = tieBreaker();
                finished = 1;
            }
            return;
        }
    }
}

int Connect_Board::isColumnFull(int column) {
    if(column < 1 || column > 7) {
        cout << "Error: Invalid column number." << endl;
        return 1;
    }
    if(cells[0][column - 1] != ' ') {
        return 1;
    }
    return 0;
}

int Connect_Board::checkWin(char player) {
    int i,j;
    for (i = 0; i < 6; i++) {
        for (j = 0; j <= 3; j++) {
            if (cells[i][j] == player &&
                cells[i][j+1]== player &&
                cells[i][j+2]== player &&
                cells[i][j+3]== player) {
                return 1;
            }
        }
    }
    for(i = 0; i <= 2; i++) {
        for (j = 0; j < 7; j++) {
            if (cells[i][j]== player &&
                cells[i+1][j] == player &&
                cells[i+2][j] == player &&
                cells[i+3][j]== player) {
                return 1;
            }
        }
    }
    for(i = 0; i <= 2; i++){
        for (j = 0; j <= 3; j++){
            if (cells[i][j] == player &&
                cells[i + 1][j + 1]== player &&
                cells[i + 2][j + 2]== player &&
                cells[i + 3][j + 3]== player){
                return 1;
            }
        }
    }
    for(i = 3; i < 6; i++){
        for (j = 0; j <= 3; j++){
            if (cells[i][j]== player &&
                cells[i - 1][j + 1]== player &&
                cells[i - 2][j + 2]== player &&
                cells[i - 3][j + 3]== player) {
                return 1;
            }
        }
    }
    return 0;
}

int Connect_Board::checkDraw(){
    if(filledCells == 42) {
        return 1;
    }
    return 0;
}

int Connect_Board::tieBreaker(){
    int i,j;
    int xScore,oScore;
    int rowValue;
    xScore = 0;
    oScore = 0;
    for(i = 0; i < 6; i++) {
        rowValue = 6 - i;
        for (j = 0; j < 7; j++){
            if (cells[i][j] == 'X'){
                xScore = xScore + rowValue;
            }
            else if (cells[i][j]== 'O'){
                oScore = oScore + rowValue;
            }
        }
    }

    // HATA DÜZELTİLDİ: Tam eşitlik durumu adil hale getirildi
    if (xScore > oScore) {
        return 'X';
    }
    else if (oScore > xScore) {
        return 'O';
    }
    else {
        // Eşitse rastgele kazanan ata
        if (rand() % 2 == 0) {
            return 'X';
        }
        return 'O';
    }
}

void Connect_Board::print(){
    int i,j;
    cout << "---------------" << endl;
    for (i = 0; i < 6; i++) {
        cout << "|";
        for (j = 0; j < 7; j++) {
            // HATA DÜZELTİLDİ: Boşluklar da aynı hizada basılacak, şekil kaymayacak
            cout << cells[i][j] << "|";
        }
        cout << endl;
    }
    cout << "---------------" << endl;
    cout << " 1 2 3 4 5 6 7 " << endl;
}

char Connect_Board::getWinner() {
    return winner;
}

int Connect_Board::isFinished(){
    return finished;
}