#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
void print(vector<vector<char>> v) {
  cout << "1 | 2 | 3 | 4 | 5 | 6 | 7\n";
  for (int i = 0; i < 7; i++) {
    cout << v[i][0] << " | " << v[i][1] << " | " << v[i][2] << " | " << v[i][3]
         << " | " << v[i][4] << " | " << v[i][5] << " | " << v[i][6] << "\n";
  }
}

bool checkWin(vector<vector<char>> &board, char player) {
  // Check horizontal lines
  for (int row = 0; row < 7; ++row) {
    for (int col = 0; col < 4; ++col) {
      bool win = true;
      for (int i = 0; i < 4; ++i) {
        if (board[row][col + i] != player) {
          win = false;
          break;
        }
      }
      if (win)
        return true;
    }
  }

  // Check vertical lines
  for (int col = 0; col < 7; ++col) {
    for (int row = 0; row < 4; ++row) {
      bool win = true;
      for (int i = 0; i < 4; ++i) {
        if (board[row + i][col] != player) {
          win = false;
          break;
        }
      }
      if (win)
        return true;
    }
  }

  // Check diagonal lines (top-left to bottom-right)
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      bool win = true;
      for (int i = 0; i < 4; ++i) {
        if (board[row + i][col + i] != player) {
          win = false;
          break;
        }
      }
      if (win)
        return true;
    }
  }

  // Check diagonal lines (bottom-left to top-right)
  for (int row = 3; row < 7; ++row) {
    for (int col = 0; col < 4; ++col) {
      bool win = true;
      for (int i = 0; i < 4; ++i) {
        if (board[row - i][col + i] != player) {
          win = false;
          break;
        }
      }
      if (win)
        return true;
    }
  }

  return false;
}

int findEmpty(vector<vector<char>> &v, int col) {
  for (int row = 6; row >= 0; row--) {
    if (v[row][col] == '.')
      return row;
  }
  return 0;
}

void takeTurn(vector<vector<char>> &v, char c, int player) {
  int i;
  cout << "\nPlayer " << player << ", enter the square to place your marker: ";
  while (!(cin >> i) || i < 1 || i > 7 || v[0][i - 1] == 'X' ||
         v[0][i - 1] == 'O') { // Check if input is valid
    cin.clear();
    cin.ignore();
    v[0][i - 1] == 'X' || v[0][i - 1] == 'O'
        ? cout << "The column is full. Try again: "
        : cout << "\nInvalid entry. Try again: ";
  }
  v[findEmpty(v, i - 1)][i - 1] = c;
}

int main() {
  cout << "Penguin's Epic Connect-4 Game he made because he has nothing to do "
          "and he's bored.\n\n";
  vector<vector<char>> v(7, vector<char>(7, '.'));

  for (int turn = 1; turn <= 49; turn++) {
    print(v);
    turn % 2 == 1 ? takeTurn(v, 'X', 1) : takeTurn(v, 'O', 2);

    if (turn % 2 == 1 ? checkWin(v, 'X') : checkWin(v, 'O')) {
      print(v);
      int player = turn % 2 == 1 ? 1 : 2;
      cout << "\nPlayer " << player << " has won!";
      break;
    }

    if (turn == 49 && !checkWin(v, 'X'))
      cout << "\nTie. What a boring ending";
  }

  cout << "\nThank you for playing Penguin's Connect-4 game!\n";
  ifstream fileout("penguin.txt");
  string text;
  while (getline(fileout, text)) {
    std::cout << text << '\n';
  }
  fileout.close();
}
