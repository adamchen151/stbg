#include <iostream>
#include <vector>
#include "functions.h"
// Computer functions
struct move {
  int x1;
  int y1;
  int x2;
  int y2;
};
int get_piece_value(int i, int j, char colour);
int evaluate_board(char colur);
void get_possible_moves(std::vector<move> &v, char colour);
move decide_move(char colour);
