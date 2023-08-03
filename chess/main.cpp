#include "ai.h"
#include "functions.h"
#include <iostream>
#include <vector>
// TO-DO refactor the moves to 1 function
int main() {
  // std::cout << "\033[42m";
  int turn = 1;
  char colour;
  initializeBoard();
  std::pair<int, int> b, e; // beginning coords, end coords
  bool isMove;

  do {
    colour = turn % 2 == 1 ? 'W' : 'B';
    colour == 'W' ? std::cout << "White's turn!" : std::cout << "Red's turn!";
    printBoard();
    turn++;
    isMove = false;

    if (colour == 'B') {
      while (!isMove) {
        do {
          b = getInput("\nInput the starting coordinates (x y): ");
          // Have to somehow validate ending coords
          e = getInput("\nInput the ending coordinates (x y): ");
        } while (board[b.first][b.second].colour != colour);

        if (board[b.first][b.second].colour ==
            board[e.first][e.second].colour) {
          std::cout << "\nYou moved to a square that you occupy";
          continue;
        }

        if (movePiece(b.first, b.second, e.first, e.second))
          isMove = true;
        if (!isMove)
          std::cout << "\nYour move failed";
      }
    }

    if (colour == 'W') {
      move m = decide_move();
      movePiece(m.x1, m.y1, m.x2, m.y2);
    }
    printBoard();
  } while (!isWin(colour));

  std::cout << "\nThank you for playing Penguin's Chess game!";
}
