#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

// Tetromino shapes
int shapes[7][4][4] = {
    // I
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    // J
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // L
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // O
    {
        {1,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // S
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // T
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // Z
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }
};

int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};
int currentShape[4][4];
int currentX = 3, currentY = 0;
int currentType = 0;
int score = 0;
int linesCleared = 0;
int level = 1;
bool gameOver = false;

// Set cursor position to prevent screen flickering
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hide console cursor for clean rendering
void hideCursor() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void copyShape(int src[4][4], int dest[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            dest[i][j] = src[i][j];
}

void spawnPiece() {
    currentType = rand() % 7;
    copyShape(shapes[currentType], currentShape);
    currentX = 3;
    currentY = 0;

    // Check for game over on spawn
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentShape[i][j] && board[currentY + i][currentX + j]) {
                gameOver = true;
            }
        }
    }
}

bool checkCollision(int posX, int posY, int shape[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j]) {
                int newX = posX + j;
                int newY = posY + i;
                if (newX < 0 || newX >= BOARD_WIDTH || newY >= BOARD_HEIGHT)
                    return true;
                if (newY >= 0 && board[newY][newX])
                    return true;
            }
        }
    }
    return false;
}

void mergePiece() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentShape[i][j]) {
                if (currentY + i >= 0)
                    board[currentY + i][currentX + j] = 1;
            }
        }
    }
}

void rotatePiece() {
    int temp[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            temp[i][j] = currentShape[3 - j][i];

    if (!checkCollision(currentX, currentY, temp)) {
        copyShape(temp, currentShape);
    }
}

void removeLines() {
    for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
        bool fullLine = true;
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (!board[i][j]) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }
            for (int j = 0; j < BOARD_WIDTH; j++) {
                board[0][j] = 0;
            }
            score += 100 * level;
            linesCleared++;
            if (linesCleared % 5 == 0) level++;
            i++; // Re-check same row index
        }
    }
}

void drawBoard() {
    gotoxy(0, 0);
    cout << "===========================\n";
    cout << "       TETRIS (VS Code)    \n";
    cout << "===========================\n";

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        cout << "|";
        for (int j = 0; j < BOARD_WIDTH; j++) {
            bool isPiece = false;
            int pX = j - currentX;
            int pY = i - currentY;
            if (pX >= 0 && pX < 4 && pY >= 0 && pY < 4) {
                if (currentShape[pY][pX]) isPiece = true;
            }

            if (isPiece) cout << "[]";
            else if (board[i][j]) cout << "[]";
            else cout << "  ";
        }
        cout << "|\n";
    }
    cout << "===========================\n";
    cout << "Score : " << score << "\tLevel: " << level << "\n";
    cout << "Lines : " << linesCleared << "\n";
    cout << "Controls: A/D or Arrows to Move\n";
    cout << "          W/Up to Rotate | S to Drop | ESC to Quit\n";
}

int main() {
    srand(time(0));
    hideCursor();
    system("cls");

    spawnPiece();
    int fallCounter = 0;
    int speedThreshold = 30; // Speed control

    while (!gameOver) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 27) break; // ESC to exit
            else if (ch == 'a' || ch == 'A' || ch == 75) { // Left
                if (!checkCollision(currentX - 1, currentY, currentShape)) currentX--;
            }
            else if (ch == 'd' || ch == 'D' || ch == 77) { // Right
                if (!checkCollision(currentX + 1, currentY, currentShape)) currentX++;
            }
            else if (ch == 's' || ch == 'S' || ch == 80) { // Down Soft Drop
                if (!checkCollision(currentX, currentY + 1, currentShape)) currentY++;
            }
            else if (ch == 'w' || ch == 'W' || ch == 72) { // Rotate
                rotatePiece();
            }
        }

        if (++fallCounter >= speedThreshold) {
            fallCounter = 0;
            if (!checkCollision(currentX, currentY + 1, currentShape)) {
                currentY++;
            } else {
                mergePiece();
                removeLines();
                spawnPiece();
            }
        }

        drawBoard();
        Sleep(30); // Frame delay
    }

    system("cls");
    cout << "\n\n===========================\n";
    cout << "        GAME OVER !        \n";
    cout << "   Final Score: " << score << "      \n";
    cout << "===========================\n\n";
    return 0;
}