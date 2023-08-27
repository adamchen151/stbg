#include <iostream>
#include <stdlib.h> // For colours
#include <vector>
// TO-DO, implement check, checkmate, en passant, castling

struct piece {
  char name;
  char colour;
};

std::vector<std::vector<piece>> board(8, std::vector<piece>(8));
bool isAI;

// For one pawn function lol (This is probably an unnecessary global variable but I'm too lazy to refactor the code)
char aiColour;

std::pair<int, int> getInput(std::string text) {
  char x, y;
  std::cout << text;
  std::cin >> x >> y;
  while (std::cin.fail() || y > '8' || y < '1' || x > 'h' || x < 'a') {
    std::cin.clear();           // Clear the error state
    std::cin.ignore(100, '\n'); // Ignore the rest of the line
    std::cout << "\nInvalid input. An example input is e7 : ";
    std::cin >> x >> y;
  }
  return std::make_pair('8' - y, x -= 'a');
}

void initializeBoard() {
  board[0] = {{'R', 'B'}, {'N', 'B'}, {'B', 'B'}, {'Q', 'B'},
              {'K', 'B'}, {'B', 'B'}, {'N', 'B'}, {'R', 'B'}};
  // Pawns
  for (int i = 0; i < 8; i++) {
    board[1][i] = {'P', 'B'};
    board[6][i] = {'P', 'W'};
  }

  board[7] = {{'R', 'W'}, {'N', 'W'}, {'B', 'W'}, {'Q', 'W'},
              {'K', 'W'}, {'B', 'W'}, {'N', 'W'}, {'R', 'W'}};
}

void printBoard() {
  std::cout << "\n(y)\n";
  for (int i = 0; i < 8; i++) {
    std::cout << 8 - i << '|';
    for (int j = 0; j < 8; j++) {
      char name = board[i][j].name != '\0' ? board[i][j].name : '_';
      // 37 makes text white, 31 makes text red
      if (board[i][j].colour == 'W')
        std::cout << "\033[37m" << name << "\033[0m";
      else if (board[i][j].colour == 'B')
        std::cout << "\033[31m" << name << "\033[0m";
      else
        std::cout << name;

      std::cout << '|';
    }
    std::cout << '\n';
  }
  std::cout << "  a b c d e f g h (x)\n";
}

bool isWin(char colour) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j].name == 'K' && board[i][j].colour != colour)
        return false;
    }
  }
  printBoard();
  colour == 'W' ? std::cout << "White wins!" : std::cout << "Red wins!";
  return true;
}