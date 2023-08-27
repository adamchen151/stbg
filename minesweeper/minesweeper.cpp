#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;

// Most scuffed mine system I've ever seen
const int board_len = 8;
const int numOfMines = 12;
const int mine = -69;
const int flag = 69;

int correctInput(char x) {
  return x - 'a';
}

void print(vector<vector<int>> board) {
  // First row
  cout << "\n  ";
  for (int i = 0; i < board_len; i++) {
    char c = 'a' + i;
    cout << c << ' ';
  }
  cout << "\n";


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

int main() {
  vector<vector<int>> board (board_len, vector<int> (board_len, 0));
  generate(board);
  fillNumbers(board);
  print(board);

  for (int i = 0; i < board_len * board_len; i++) {
    int y;
    char xChar;
    string input;
    do {
        cout << "Enter the x and y coordinates you want to check (The board is 8x8):\n";
        cin >> input;
        cout << input << endl;
        xChar = input[0];
        y = input[1] - '0';
        cout << xChar << y;
    } while (xChar > 'h' || xChar < 'a' || y > 8 || y < 1);
    int x = correctInput(xChar);
    
    //x--; 
    y--;
    swap(x, y); //kekw 
    
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
