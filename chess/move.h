#include <iostream>
#include <stdlib.h>
#include <vector>
#ifndef MOVE_H
#define MOVE_H
bool pawnMove(int x1, int y1, int x2, int y2);
bool rookMove(int x1, int y1, int x2, int y2);
bool bishopMove(int x1, int y1, int x2, int y2);
bool knightMove(int x1, int y1, int x2, int y2);
bool queenMove(int x1, int y1, int x2, int y2);
bool kingMove(int x1, int y1, int x2, int y2);
bool movePiece(int x1, int y1, int x2, int y2);
#endif
