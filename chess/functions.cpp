#include <iostream>
#include <vector>
#include <stdlib.h>

struct piece {
  char name;
  char colour;
};

std::vector<std::vector<piece>> board (8,     std::vector<piece> (8));

std::pair<int, int> getInput(std::string text) {
    int x, y;
    std::cout << text;
    std::cin >> y >> x;
        while (std::cin.fail() || y > 8 || y < 1 || x > 8 || x < 1) {
            std::cin.clear();  // Clear the error state
            std::cin.ignore(100, '\n');  // Ignore the rest of the line
            std::cout << "\nInvalid input. Please enter two integers seperated by a space (1-8): ";
            std::cin >> y >> x;
        }
    x--; y--;
    return std::make_pair(x, y);
}

void initializeBoard() {
  board[0] = {{'R', 'B'}, {'N', 'B'}, {'B', 'B'}, {'Q', 'B'}, {'K', 'B'}, {'B', 'B'}, {'N', 'B'}, {'R', 'B'}};
  //Pawns
  for (int i = 0; i < 8; i++) {
    board[1][i] = {'P', 'B'};
    board[6][i] = {'P', 'W'};
  }

  board[7] = {{'R', 'W'}, {'N', 'W'}, {'B', 'W'}, {'Q', 'W'}, {'K', 'W'}, {'B', 'W'}, {'N', 'W'}, {'R', 'W'}};
}

void printBoard() {
  std::cout << "\n  1 2 3 4 5 6 7 8 x\n";
  for (int i = 0; i < 8; i++) {
    std::cout << i+1 << '|';
    for (int j = 0; j < 8; j++) {
      char name = board[i][j].name != '\0' ? 
      board[i][j].name : '_'; 
      //37 is white, 31 is red
      if (board[i][j].colour == 'W') std::cout << "\033[37m" << name << "\033[0m";
      else if (board[i][j].colour == 'B') std::cout << "\033[31m" << name << "\033[0m";
      else std::cout << name;

      std::cout << '|';
    }
    std::cout << '\n';
  }
  std::cout << "y\n";
}


// Y is X and X is Y
bool pawnMove(int x1, int y1, int x2, int y2) {
  if (y1 == y2) {
    if (abs(x1 - x2) > 1 && x1 != 1 && x1 != 6)
      return false; // If not on first rank
    if (abs(x1 - x2) > 2 && (x1 == 1 || x1 == 6))
      return false; // If on first rank
    if (board[x2][y2].name != '\0')
      return false; // If square is occupied
  }
  
  if (y1 != y2) {
    if (board[x2][y2].name == '\0') return false;
    if (abs(y1 - y2) > 1 || abs(x1 - x2) != 1) return false;
  }
  
  //Actual move
  board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);
  std::cout << "Knight move";
  return true;
}

bool rookMove(int x1, int y1, int x2, int y2) {
  if (x1 != x2 && y1 != y2) return false;
  if (x1 != x2) {
    for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++) {
      if (i == x1 || i == x2) continue;
      if (board[i][y1].colour != '\0') {
        std::cout << "Move goes through a piece";
        return false;
      }
    }
  }

  if (y1 != y2) {
    for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
      if (i == y1 || i == y2) continue;
      if (board[x1][i].colour != '\0') {
        std::cout << "Move goes through a piece";
        return false;
      }
    }
  }

  if (board[x2][y2].name != '\0') board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);
  return true;
}

bool bishopMove(int x1, int y1, int x2, int y2) {
  if (abs(x1 - x2) != abs(y1 - y2)) return false;

  if (x1 - x2 == y1 - y2) {
    for (int i = std::min(x1, x2), j = std::min(y1, y2); i <= std::max(x1, x2); i++, j++) {
      if (i == x2 && j == y2) continue;
      if (i == x1 && j == y1) continue;
      if (board[i][j].colour != '\0') {
        std::cout << "Move goes through a piece";
        return false;
      }
    }
  }
  else {
    for (int i = std::min(x1, x2), j = std::max(y1, y2); i <= std::max(x1, x2); i++, j--) {
      if (i == x2 && j == y2) continue;
      if (i == x1 && j == y1) continue;
      if (board[i][j].colour != '\0') {
        std::cout << "Move goes through a piece";
        return false;
      }
    }
  }

  if (board[x2][y2].name != '\0') board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);
  return true;
}

bool knightMove(int x1, int y1, int x2, int y2) {
  if (abs(x1 - x2) == 1 && abs(y1 - y2) != 2) return false;
  if (abs(x1 - x2) == 2 && abs(y1 - y2) != 1) return false;
  if (abs(x1 - x2) != 1 && abs(x1 - x2) != 2) return false;
  if (board[x2][y2].colour == board[x1][y1].colour) {
    std::cout << "The square is already occupied\n";
    return false;
  }

  if (board[x2][y2].name != '\0') board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);
  return true;
}

bool queenMove(int x1, int y1, int x2, int y2) {
  if ((x1 != x2 && y1 != y2) &&  // Something may be wrong here
    (abs(x1 - x2) != abs(y1 - y2))) return false;
  //!rook && !bishop

  if (x1 != x2 && y1 != y2) {
    if (x1 - x2 == y1 - y2) {
      for (int i = std::min(x1, x2), j = std::min(y1, y2); i <= std::max(x1, x2); i++, j++) {
        if (i == x2 && j == y2) continue;
        if (i == x1 && j == y1) continue;
        if (board[i][j].colour != '\0') {
          std::cout << "Move goes through a piece";
          return false;
        }
      }
    }
    else {
      for (int i = std::min(x1, x2), j = std::max(y1, y2); i <= std::max(x1, x2); i++, j--) {
        if (i == x2 && j == y2) continue;
        if (i == x1 && j == y1) continue;
        if (board[i][j].colour != '\0') {
          std::cout << "Move goes through a piece";
          return false;
        }
      }
    }
  }

  else if (x1 != x2) {
    for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++) {
      if (i == x1 || i == x2) continue;
      if (board[i][y1].colour != '\0') {
        std::cout << "Move goes through a piece";
        return false;
      }
    }
  }

  else if (y1 != y2) {
    for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
      if (i == y1 || i == y2) continue;
      if (board[x1][i].colour != '\0') {
        std::cout << "Move goes through a piece";
        return false;
      }
    }
  }

  if (board[x2][y2].name != '\0') board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);
  return true;
}

bool kingMove(int x1, int y1, int x2, int y2) {
  if (abs(x1 - x2) > 1 || abs(y1 - y2) > 1) return false;

  if (board[x2][y2].name != '\0') board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);
  return true;
}

bool movePiece(int x1, int y1, int x2, int y2) {
  if (board[x1][y1].name == 'P') {
    if (pawnMove(x1, y1, x2, y2)) return true;
  }
  if (board[x1][y1].name == 'R') {
    if (rookMove(x1, y1, x2, y2)) return true;
  }
  if (board[x1][y1].name == 'B') {
    if (bishopMove(x1, y1, x2, y2)) return true;
  }
  if (board[x1][y1].name == 'N') {
    if (knightMove(x1, y1, x2, y2)) return true;
  }
  if (board[x1][y1].name == 'Q') {
    if (queenMove(x1, y1, x2, y2)) return true;
  }
  if (board[x1][y1].name == 'K') {
    if (kingMove(x1, y1, x2, y2)) return true;
  }
  return false;
}

bool isWin(char colour) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j].name == 'K' && board[i][j].colour != colour) return false;
    }
  }
  
  colour == 'W' ? std::cout << "White wins!" : std::cout << "Red wins!";
  return true;
}
