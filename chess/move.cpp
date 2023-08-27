#include "functions.h"
#include <iostream>
#include <vector>

// Y is X and X is Y
bool pawnMove(int x1, int y1, int x2, int y2) {
  // Make sure pawns don't move backwards
  if (board[x1][y1].colour == 'W' && x2 > x1) return false;
  if (board[x1][y1].colour == 'B' && x2 < x1) return false;

  // If pawn is moving forward
  if (y1 == y2) {
    if (abs(x1 - x2) > 1 && x1 != 1 && x1 != 6)
      return false; // If not on first rank
    if (abs(x1 - x2) > 2 && (x1 == 1 || x1 == 6))
      return false; // If on first rank
    if (board[x2][y2].name != '\0')
      return false; // If square is occupied
  }

  // If pawn is moving diagonally
  if (y1 != y2) {
    if (board[x2][y2].name == '\0') return false;
    if (abs(y1 - y2) > 1 || abs(x1 - x2) != 1) return false;
  }

  // Actual move
  board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);

  // Pawn promotion
  if (x2 == 0 || x2 == 7) {
    if (board[x2][y2].colour == aiColour) {
      board[x2][y2].name = 'Q';
      return true;
    }

    char name;
    while (name != 'Q' && name != 'R' && name != 'B' && name != 'N') {
      std::cout << "Enter the piece you want to promote to (Q, R, B, N): ";
      std::cin >> name;
      board[x2][y2].name = name;
    }
  }
  return true;
}

bool rookMove(int x1, int y1, int x2, int y2) {
  if (x1 != x2 && y1 != y2)
    return false;
  if (x1 != x2) {
    for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++) {
      if (i == x1 || i == x2)
        continue;
      if (board[i][y1].colour != '\0') {
        if (!isAI)
          std::cout << "Move goes through a piece";
        return false;
      }
    }
  }

  if (y1 != y2) {
    for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
      if (i == y1 || i == y2)
        continue;
      if (board[x1][i].colour != '\0') {
        if (!isAI)
          std::cout << "Move goes through a piece";
        return false;
      }
    }
  }

  if (board[x2][y2].name != '\0')
    board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);
  return true;
}

bool bishopMove(int x1, int y1, int x2, int y2) {
  if (abs(x1 - x2) != abs(y1 - y2))
    return false;

  if (x1 - x2 == y1 - y2) {
    for (int i = std::min(x1, x2), j = std::min(y1, y2); i <= std::max(x1, x2);
         i++, j++) {
      if (i == x2 && j == y2)
        continue;
      if (i == x1 && j == y1)
        continue;
      if (board[i][j].colour != '\0') {
        if (!isAI)
          std::cout << "Move goes through a piece";
        return false;
      }
    }
  } else {
    for (int i = std::min(x1, x2), j = std::max(y1, y2); i <= std::max(x1, x2);
         i++, j--) {
      if (i == x2 && j == y2)
        continue;
      if (i == x1 && j == y1)
        continue;
      if (board[i][j].colour != '\0') {
        if (!isAI)
          std::cout << "Move goes through a piece";
        return false;
      }
    }
  }

  if (board[x2][y2].name != '\0')
    board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);
  return true;
}

bool knightMove(int x1, int y1, int x2, int y2) {
  if (abs(x1 - x2) == 1 && abs(y1 - y2) != 2)
    return false;
  if (abs(x1 - x2) == 2 && abs(y1 - y2) != 1)
    return false;
  if (abs(x1 - x2) != 1 && abs(x1 - x2) != 2)
    return false;
  if (board[x2][y2].colour == board[x1][y1].colour) {
    if (!isAI)
      std::cout << "The square is already occupied\n";
    return false;
  }

  if (board[x2][y2].name != '\0')
    board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);
  return true;
}

bool queenMove(int x1, int y1, int x2, int y2) {
  if ((x1 != x2 && y1 != y2) && // Something may be wrong here
      (abs(x1 - x2) != abs(y1 - y2)))
    return false;
  //! rook && !bishop

  if (x1 != x2 && y1 != y2) {
    if (x1 - x2 == y1 - y2) {
      for (int i = std::min(x1, x2), j = std::min(y1, y2);
           i <= std::max(x1, x2); i++, j++) {
        if (i == x2 && j == y2)
          continue;
        if (i == x1 && j == y1)
          continue;
        if (board[i][j].colour != '\0') {
          if (!isAI)
            std::cout << "Move goes through a piece";
          return false;
        }
      }
    } else {
      for (int i = std::min(x1, x2), j = std::max(y1, y2);
           i <= std::max(x1, x2); i++, j--) {
        if (i == x2 && j == y2)
          continue;
        if (i == x1 && j == y1)
          continue;
        if (board[i][j].colour != '\0') {
          if (!isAI)
            std::cout << "Move goes through a piece";
          return false;
        }
      }
    }
  }

  else if (x1 != x2) {
    for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++) {
      if (i == x1 || i == x2)
        continue;
      if (board[i][y1].colour != '\0') {
        if (!isAI)
          std::cout << "Move goes through a piece";
        return false;
      }
    }
  }

  else if (y1 != y2) {
    for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
      if (i == y1 || i == y2)
        continue;
      if (board[x1][i].colour != '\0') {
        if (!isAI)
          std::cout << "Move goes through a piece";
        return false;
      }
    }
  }

  if (board[x2][y2].name != '\0')
    board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);
  return true;
}

bool kingMove(int x1, int y1, int x2, int y2) {
  if (abs(x1 - x2) > 1 || abs(y1 - y2) > 1)
    return false;
  if (board[x2][y2].colour == board[x1][y1].colour) {
    if (!isAI)
      std::cout << "Move goes through your own piece";
    return false;
  }
  if (board[x2][y2].name != '\0')
    board[x2][y2] = piece();
  std::swap(board[x1][y1], board[x2][y2]);
  return true;
}

bool movePiece(int x1, int y1, int x2, int y2) {
  if (board[x1][y1].name == 'P') {
    if (pawnMove(x1, y1, x2, y2))
      return true;
  }
  if (board[x1][y1].name == 'R') {
    if (rookMove(x1, y1, x2, y2))
      return true;
  }
  if (board[x1][y1].name == 'B') {
    if (bishopMove(x1, y1, x2, y2))
      return true;
  }
  if (board[x1][y1].name == 'N') {
    if (knightMove(x1, y1, x2, y2))
      return true;
  }
  if (board[x1][y1].name == 'Q') {
    if (queenMove(x1, y1, x2, y2))
      return true;
  }
  if (board[x1][y1].name == 'K') {
    if (kingMove(x1, y1, x2, y2))
      return true;
  }
  return false;
}