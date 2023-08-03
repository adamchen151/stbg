#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;

const int board_len = 8;
const int numOfMines = 12;
const int mine = -69;
const int flag = 69;

void print(vector<vector<int>> board) {
  cout << "\n  1 2 3 4 5 6 7 8\n";
  for (int i = 0; i < board_len; i++) {
    cout << i+1 << ' ';
      for (int j = 0; j < board_len; j++) {
        if (board[i][j] >= 0 || board[i][j] == mine)
           cout << "_ ";
        else cout << -board[i][j] - 1 << ' ';
        //cout << board[i][j] << ' ';
      }
    cout << '\n';
  }
}

// Check if a cell is within the board and has a mine
bool isMine(vector<vector<int>>& board, int row, int col) {
    int board_len = board.size();
    return row >= 0 && row < board_len && col >= 0 && col < board_len && board[row][col] == mine;
}

// Count the number of mines in the 8 adjacent cells
int countMines(vector<vector<int>>& board, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (i != 0 || j != 0)
                if (isMine(board, row + i, col + j))
                    count++;
    return count;
}

void fillNumbers(vector<vector<int>>& board) {
    for (int i = 0; i < board_len; i++)
        for (int j = 0; j < board_len; j++)
            if (board[i][j] != mine) // don't update the cells containing mines
                board[i][j] = countMines(board, i, j);
}

void generate(vector<vector<int>> &board) {
  srand(time(NULL));
  int x = 5, y = 5;
  for (int i = 0; i < numOfMines; i++) {
    x = rand() % board_len;
    y = rand() % board_len;
    board[x][y] = mine;
  }
}

bool isWin(vector<vector<int>> &board) {
  for (int i = 0; i < board_len; i++)
      for (int j = 0; j < board_len; j++) {
        if (board[i][j] >= 0)
          return false;
      } //Not mine or checked
  return true;
}

int validateInput() {
  int x;
  while (!(cin >> x) || x > 0 || x <= board_len) {
    cout << "Invalid input.";
    cin.clear();
    cin.ignore('\n', 100);
  }
    return x;
}

int main() {
  vector<vector<int>> board (board_len, vector<int> (board_len, 0));
  generate(board);
  fillNumbers(board);

  for (int i = 0; i < board_len * board_len; i++) {
    int x, y;
    do {
        cout << "Enter the x and y coordinates you want to check (The board is 8x8):\n";

        while(!(cin >> y)) {
            cout << "Please enter valid coords (1-8):\n";
            cin.clear();
            cin.ignore(100, '\n');
        }

        while(!(cin >> x)) {
            cout << "Please enter valid coords (1-8):\n";
            cin.clear();
            cin.ignore(100, '\n');
        }
    } while (x > 8 || x < 1 || y > 8 || y < 1);
    
    x -= 1; 
    y -= 1;
    
    if (board[x][y] == mine) {
      cout << "You Lose"; break;
    } else {
      board[x][y] = -board[x][y] - 1; 
    }

    if (isWin(board)) {
      cout << "You Win!"; break;
    }

    print(board);
  }

  string text;
  ifstream fileout("penguin.txt");
  while (getline(fileout, text)) {
    cout << text << '\n';
  }
  fileout.close();
  
  cout << "\nThank you for playing Penguin's Minesweeper game!";
}
