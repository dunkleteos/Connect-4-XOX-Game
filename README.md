Connect 4 Ultimate - Local PvP Edition

Connect 4 Ultimate is a strategic board game developed using C++ and Raylib. It is a unique combination of the classic Connect 4 and XOX (Tic-Tac-Toe) games, utilizing the mechanics of "Ultimate Tic-Tac-Toe".

Note: This project was originally designed as Player vs PC (AI), but was later completely redesigned to focus entirely on Local PvP (Player vs Player) gameplay.

---

Features

- Fully PvP (Player vs Player): Play against a friend locally on the same computer (Hot-seat).
- Connect 4 meets XOX: A massive strategic network consisting of 9 different small Connect 4 boards arranged in a 3x3 XOX grid.
- Dynamic Game Flow: Your opponent's move determines which board you are forced to play on in your next turn.
- Modern UI: Smooth, click-based graphical interface developed with the Raylib game engine in a 16:9 (1280x720) resolution.
- Visual Feedback: Colored text indicating whose turn it is and glowing highlight effects for the required board.

---

How to Play (Game Rules)

There are 9 small Connect 4 boards arranged in a 3x3 grid on the game screen.

1. Objective: To win 3 small boards in a row horizontally, vertically, or diagonally on the large (Mega) board, just like in a classic game of XOX.
2. Winning Small Boards: You capture a small board by connecting 4 of your discs (Green for X, Red for O) horizontally, vertically, or diagonally within that specific board.
3. Forced Move (Critical Rule): The column a player drops their disc into determines the specific small board the opponent must play on during their next turn. 
   Example: If Player 1 drops a disc into the 3rd column of any board, Player 2 is forced to make their next move on the 3rd small board. The UI highlights this required board in yellow.
4. Free Move: If the required small board is already won, finished, or completely full, the next player earns the right to make a Free Move on any available board.

---

Technologies Used

- Language: C++ (C++17 Standards)
- Graphics Library: Raylib (v5.0)
- Build Tool: CMake (Downloads Raylib automatically via FetchContent)

---

Installation and Running

Play Instantly (No Compilation Required)
If you just want to play the game without dealing with code, compilers, or IDEs, you can download the ready-to-play .exe file directly from the Releases section of this repository! Just download, extract, and play.

For CLion Users (Source Code)
1. Open the project with CLion.
2. The IDE will automatically read the CMakeLists.txt file and download Raylib.
3. From the top-right corner, select Build -> Clean Project and then Rebuild Project.
4. Select the 242_p2 (or your specific project name) target and click the Run button.

Compiling via Terminal (Command Line)
If you have CMake and MinGW/GCC installed on your system, you can run the following commands in the directory:

mkdir build
cd build
cmake ..
cmake --build .

Once the compilation is complete, you can enter the game by running the generated executable file.

---

Controls

The game is played entirely using the Mouse.
- Left Click: Used to click buttons in menus and drop discs into the desired column on the valid board during gameplay.

---

Developers

- Game Logic and Core Code: Efe Ozgur & Yaren Baris
- User Interface (UI) and Gameplay: Efe Ozgur
