#include "raylib.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Game Screen Definitions
enum GameScreen { SCREEN_START, SCREEN_GAME, SCREEN_GAMEOVER };

// Global Game Variables
GameScreen currentScreen = SCREEN_START;
char cells[9][6][7];       // 9 small boards (6 rows, 7 columns)
char boardWinners[9];      // Winners of each small board (' ', 'X', 'O', 'T')
char megaWinner = ' ';     // Overall game winner
int nextBoard = -1;        // Required board to play (-1 = free choice)
char currentPlayer = 'X';  // 'X' (Player 1) or 'O' (Player 2)

// Function Prototypes
void ResetGame();
bool DropDisc(int boardIdx, int col, char player);
void CheckSmallBoardWin(int boardIdx, char p);
void CheckMegaBoardWin(char p);

int main() {
    // Window Setup - 16:9 Format (1280x720)
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Ultimate Connect 4 - Local PvP");
    SetTargetFPS(60);
    srand(time(0));

    ToggleFullscreen();

    // 2. "Made By Efe :) " SPLASH SCREEN
    float splashTimer = 0.0f;
    while (splashTimer < 3.0f && !WindowShouldClose()) {
        splashTimer += GetFrameTime();

        BeginDrawing();
        ClearBackground(GetColor(0x1a1a2eFF));

        int textSize = 60;
        const char* text = "Welcome :) ";
        int textWidth = MeasureText(text, textSize);

        DrawText(text, (screenWidth - textWidth) / 2, screenHeight / 2 - (textSize / 2), textSize, LIGHTGRAY);

        EndDrawing();
    }

    ResetGame();

    // Main Game Loop
    while (!WindowShouldClose()) {

        // -------- UPDATE (GAME LOGIC) --------
        switch (currentScreen) {
            case SCREEN_START: {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mousePos = GetMousePosition();
                    if (mousePos.x >= 540 && mousePos.x <= 740 && mousePos.y >= 400 && mousePos.y <= 460) {
                        currentScreen = SCREEN_GAME;
                    }
                }
                break;
            }

            case SCREEN_GAME: {
                if (megaWinner != ' ') {
                    currentScreen = SCREEN_GAMEOVER;
                    break;
                }

                // Her iki oyuncu için de sadece fare tıklaması bekleniyor
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mousePos = GetMousePosition();

                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            int bIdx = i * 3 + j;
                            int bx = 165 + j * 310;
                            int by = 100 + i * 200;

                            if (nextBoard != -1 && nextBoard != bIdx && boardWinners[nextBoard] == ' ')
                                continue;

                            if (boardWinners[bIdx] != ' ')
                                continue;

                            if (mousePos.x >= bx && mousePos.x <= bx + 280 &&
                                mousePos.y >= by && mousePos.y <= by + 180) {

                                int col = (mousePos.x - bx) / 40;

                                if (col >= 0 && col < 7) {
                                    if (DropDisc(bIdx, col, currentPlayer)) {

                                        CheckSmallBoardWin(bIdx, currentPlayer);
                                        CheckMegaBoardWin(currentPlayer);

                                        if (boardWinners[col] == ' ')
                                            nextBoard = col;
                                        else
                                            nextBoard = -1;

                                        // Sırayı diğer oyuncuya geçir
                                        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            }

            case SCREEN_GAMEOVER: {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mousePos = GetMousePosition();
                    if (mousePos.x >= 540 && mousePos.x <= 740 && mousePos.y >= 450 && mousePos.y <= 510) {
                        ResetGame();
                        currentScreen = SCREEN_GAME;
                    }
                }
                break;
            }
        }

        // -------- DRAWING --------
        BeginDrawing();
        ClearBackground(GetColor(0x1a1a2eFF));

        switch (currentScreen) {

            case SCREEN_START: {
                int titleWidth = MeasureText("CONNECT 4 ULTIMATE", 50);
                DrawText("CONNECT 4 ULTIMATE", (screenWidth - titleWidth) / 2, 200, 50, GOLD);

                int subWidth = MeasureText("Local Multiplayer (PvP)", 20);
                DrawText("Local Multiplayer (PvP)", (screenWidth - subWidth) / 2, 270, 20, LIGHTGRAY);

                DrawRectangle(540, 400, 200, 60, MAROON);
                DrawRectangleLinesEx(Rectangle{540, 400, 200, 60}, 2, WHITE);

                int btnTextWidth = MeasureText("START GAME", 20);
                DrawText("START GAME", 540 + (200 - btnTextWidth) / 2, 420, 20, WHITE);

                break;
            }

            case SCREEN_GAME: {
                // Hangi oyuncunun sırasıysa ekrana yazdırıyoruz
                if (currentPlayer == 'X')
                    DrawText("PLAYER 1 TURN (X)", 165, 40, 30, GREEN);
                else
                    DrawText("PLAYER 2 TURN (O)", 165, 40, 30, RED);

                if (nextBoard != -1 && boardWinners[nextBoard] == ' ') {
                    const char* reqText = TextFormat("Required Board: %d", nextBoard + 1);
                    int reqTextWidth = MeasureText(reqText, 24);
                    DrawText(reqText, 1115 - reqTextWidth, 45, 24, GOLD);
                }
                else {
                    const char* freeText = "Free Move: Play on Any Board";
                    int freeTextWidth = MeasureText(freeText, 24);
                    DrawText(freeText, 1115 - freeTextWidth, 45, 24, LIGHTGRAY);
                }

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {

                        int bIdx = i * 3 + j;
                        int bx = 165 + j * 310;
                        int by = 100 + i * 200;

                        if (boardWinners[bIdx] == ' ') {
                            if (nextBoard == bIdx)
                                DrawRectangle(bx - 5, by - 5, 290, 190, GetColor(0x3e3e12FF));
                            else
                                DrawRectangle(bx, by, 280, 180, GetColor(0x16213eFF));
                        }

                        for (int r = 0; r < 6; r++) {
                            for (int c = 0; c < 7; c++) {

                                int cx = bx + c * 40 + 20;
                                int cy = by + r * 30 + 15;

                                if (cells[bIdx][r][c] == 'X')
                                    DrawCircle(cx, cy, 12, GREEN);
                                else if (cells[bIdx][r][c] == 'O')
                                    DrawCircle(cx, cy, 12, RED);
                                else
                                    DrawCircle(cx, cy, 12, GetColor(0x0f172aFF));
                            }
                        }

                        DrawRectangleLinesEx(Rectangle{(float)bx, (float)by, 280, 180}, 2, DARKBLUE);
                        DrawText(TextFormat("Board %d", bIdx + 1), bx + 10, by - 20, 16, GRAY);

                        if (boardWinners[bIdx] == 'X') {
                            DrawRectangle(bx, by, 280, 180, Fade(GREEN, 0.4f));
                            DrawText("X", bx + 110, by + 40, 100, WHITE);
                        }
                        else if (boardWinners[bIdx] == 'O') {
                            DrawRectangle(bx, by, 280, 180, Fade(RED, 0.4f));
                            DrawText("O", bx + 110, by + 40, 100, WHITE);
                        }
                    }
                }
                break;
            }

            case SCREEN_GAMEOVER: {
                int goWidth = MeasureText("GAME OVER", 50);
                DrawText("GAME OVER", (screenWidth - goWidth) / 2, 200, 50, GOLD);

                if (megaWinner == 'X') {
                    int wWidth = MeasureText("PLAYER 1 (X) WINS!", 34);
                    DrawText("PLAYER 1 (X) WINS!", (screenWidth - wWidth) / 2, 300, 34, GREEN);
                }
                else if (megaWinner == 'O') {
                    int lWidth = MeasureText("PLAYER 2 (O) WINS!", 34);
                    DrawText("PLAYER 2 (O) WINS!", (screenWidth - lWidth) / 2, 300, 34, RED);
                }
                else {
                    int dWidth = MeasureText("IT'S A DRAW!", 34);
                    DrawText("IT'S A DRAW!", (screenWidth - dWidth) / 2, 300, 34, LIGHTGRAY);
                }

                DrawRectangle(540, 450, 200, 60, DARKBLUE);
                DrawRectangleLinesEx(Rectangle{540, 450, 200, 60}, 2, WHITE);

                int rWidth = MeasureText("PLAY AGAIN", 20);
                DrawText("PLAY AGAIN", 540 + (200 - rWidth) / 2, 470, 20, WHITE);

                break;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void ResetGame() {
    for (int b = 0; b < 9; b++) {
        boardWinners[b] = ' ';
        for (int r = 0; r < 6; r++)
            for (int c = 0; c < 7; c++)
                cells[b][r][c] = ' ';
    }
    megaWinner = ' ';
    nextBoard = -1;
    currentPlayer = 'X'; // Oyuna her zaman 1. oyuncu (X) başlar
}

bool DropDisc(int boardIdx, int col, char player) {
    for (int r = 5; r >= 0; r--) {
        if (cells[boardIdx][r][col] == ' ') {
            cells[boardIdx][r][col] = player;
            return true;
        }
    }
    return false;
}

void CheckSmallBoardWin(int b, char p) {
    // Horizontal
    for (int r = 0; r < 6; r++)
        for (int c = 0; c < 4; c++)
            if (cells[b][r][c] == p &&
                cells[b][r][c+1] == p &&
                cells[b][r][c+2] == p &&
                cells[b][r][c+3] == p) {
                boardWinners[b] = p;
                return;
            }

    // Vertical
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 7; c++)
            if (cells[b][r][c] == p &&
                cells[b][r+1][c] == p &&
                cells[b][r+2][c] == p &&
                cells[b][r+3][c] == p) {
                boardWinners[b] = p;
                return;
            }

    // Diagonal (Down-Right)
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 4; c++)
            if (cells[b][r][c] == p &&
                cells[b][r+1][c+1] == p &&
                cells[b][r+2][c+2] == p &&
                cells[b][r+3][c+3] == p) {
                boardWinners[b] = p;
                return;
            }

    // Diagonal (Down-Left)
    for (int r = 0; r < 3; r++)
        for (int c = 3; c < 7; c++)
            if (cells[b][r][c] == p &&
                cells[b][r+1][c-1] == p &&
                cells[b][r+2][c-2] == p &&
                cells[b][r+3][c-3] == p) {
                boardWinners[b] = p;
                return;
            }
}

void CheckMegaBoardWin(char p) {
    int combinations[8][3] = {
            {0,1,2}, {3,4,5}, {6,7,8},
            {0,3,6}, {1,4,7}, {2,5,8},
            {0,4,8}, {2,4,6}
    };

    for (int i = 0; i < 8; i++) {
        if (boardWinners[combinations[i][0]] == p &&
            boardWinners[combinations[i][1]] == p &&
            boardWinners[combinations[i][2]] == p) {

            megaWinner = p;
            return;
        }
    }
}