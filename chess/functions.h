#include <iostream>
#include <vector>
#include <stdlib.h>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
struct piece {
  char name;
  char colour;
};

extern std::vector<std::vector<piece>> board;
std::pair<int, int> getInput(std::string text);
void initializeBoard();
void printBoard();
bool isWin(char colour);
bool pawnMove(int x1, int y1, int x2, int y2);
bool rookMove(int x1, int y1, int x2, int y2);
bool bishopMove(int x1, int y1, int x2, int y2);
bool knightMove(int x1, int y1, int x2, int y2);
bool queenMove(int x1, int y1, int x2, int y2);
bool kingMove(int x1, int y1, int x2, int y2);
bool movePiece(int x1, int y1, int x2, int y2);
#endif
