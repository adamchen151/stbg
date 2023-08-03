#include <iostream>
#include <vector>
#include <utility>

std::pair<int, int> getInput(std::string text);
void initializeBoard();
void printBoard();
bool isValid(int x1, int y1, int x2, int y2, char color);
bool isJumpPossible(int x1, int y1, char color);
bool movePiece(int x1, int y1, int x2, int y2, char color);
bool checkWin();
