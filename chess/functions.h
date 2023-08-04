#include <iostream>
#include <stdlib.h>
#include <vector>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
struct piece {
  char name;
  char colour;
};

extern std::vector<std::vector<piece>> board;
extern bool isAI;
extern char aiColour;
std::pair<int, int> getInput(std::string text);
void initializeBoard();
void printBoard();
bool isWin(char colour);
#endif
