#include <iostream>
#include <vector>
#include <stdlib.h>
#include "functions.h"
// Computer functions
struct move {
  int x1;
  int y1;
  int x2;
  int y2;
};
int get_piece_value(int i, int j);
int evaluate_board();
void get_possible_moves(std::vector<move> &v);
move decide_move();
