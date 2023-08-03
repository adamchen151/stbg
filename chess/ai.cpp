#include <iostream>
#include <vector>
#include <stdlib.h>
#include "functions.h"

// AI only white for now
int get_piece_value(int i, int j) {
  int ans = 0;
  switch (board[i][j].name) {
    case 'P': 
      ans = 1;
      break;
    case 'N':
      ans = 3;
      break;
    case 'B':
      ans = 3;
      break;
    case 'R':
      ans = 5;
      break;
    case 'Q':
      ans = 9;
      break;
    case 'K':
      ans = 60;
      break;
  }

  if (board[i][j].colour != 'W') ans *= -1;
  return ans;
}


int evaluate_board() {
    int score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            score += get_piece_value(i, j);
        }
    }
    return score;
}

// Make a move struct
struct move {
  int x1;
  int y1;
  int x2;
  int y2;
};


void get_possible_moves(std::vector<move> &v) {
  for (int x1 = 0; x1 < 8; x1++) {
    for (int y1 = 0; y1 < 8; y1++) {
      if (board[x1][y1].colour != 'W') continue; 
      
      for (int x2 = 0; x2 < 8; x2++) {
        for (int y2 = 0; y2 < 8; y2++) {
          if (board[x2][y2].colour == 'W') continue;
          piece temp1 = board[x1][y1];
          piece temp2 = board[x2][y2];
          if (movePiece(x1, y1, x2, y2)) {
            v.push_back({x1, y1, x2, y2});
            board[x1][y1] = temp1;
            board[x2][y2] = temp2;
          }
        }
      }
    }
  }
}

// Need to not move when getting possible moves
move decide_move() {
    move best_move;
    int best_score = -200;
    std::vector<move> possible_moves;
    get_possible_moves(possible_moves);
  
    for (move m : possible_moves) {
      piece temp1 = board[m.x1][m.y1];
      piece temp2 = board[m.x2][m.y2];
      movePiece(m.x1, m.y1, m.x2, m.y2);
      int score = evaluate_board();
      
      board[m.x1][m.y1] = temp1;
      board[m.x2][m.y2] = temp2;
      if (score > best_score) {
          best_score = score;
          best_move = m;
          std::cout << "New best move: " << m.x1 << m.y1 << ' ' << m.x2 << m.y2;
      }
    }
    return best_move;
}
