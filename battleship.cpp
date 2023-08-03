#include <cstdlib> //rand
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void generateShips(vector<vector<char>> &board1, vector<vector<char>> &board2) {
  srand(time(NULL));
  for (int ship = 0; ship < 4; ship++) {
    int size = rand() % 2 + 3;
    bool vertical = rand() % 2;
    int x = rand() % 10;
    int y = rand() % 10;

    if (vertical) {
      if (x + size > 10)
        x -= size;
      for (int i = x; i <= x + size; i++) {
        if (i > 9)
          break;
        board1[i][y] = 'M';
      }
    }

    else {
      if (y + size > 10)
        y -= size;
      for (int i = y; i <= y + size; i++) {
        if (i > 9)
          break;
        board1[x][i] = 'M';
      }
    }
  }

  for (int ship = 0; ship < 4; ship++) {
    int size = rand() % 2 + 3;
    bool vertical = rand() % 2;
    int x = rand() % 10;
    int y = rand() % 10;

    if (vertical) {
      if (x + size > 10)
        x -= size;
      for (int i = x; i <= x + size; i++) {
        if (i > 9)
          break;
        board2[i][y] = 'M';
      }
    }

    else {
      if (y + size > 10)
        y -= size;
      for (int i = y; i <= y + size; i++) {
        if (i > 9)
          break;
        board2[x][i] = 'M';
      }
    }
  }
}

void print(vector<vector<char>> board) {
  cout << "\n  1 2 3 4 5 6 7 8 9 0\n";
  for (int i = 0; i < 10; i++) {
    i != 9 ? cout << i + 1 << ' ' : cout << "0 ";
    for (int j = 0; j < 10; j++) {
      board[i][j] == 'M' ? cout << "~ " : cout << board[i][j] << ' ';
    }
    cout << endl;
  }
}

void printEnd(vector<vector<char>> board) {
  cout << "\n  1 2 3 4 5 6 7 8 9 0\n";
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      cout << board[i][j] << ' ';
    }
    cout << endl;
  }
}

bool checkWin(vector<vector<char>> &board) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (board[i][j] == 'M')
        return false;
    }
  }
  return true;
}

void bumblebeeTurn(vector<vector<char>> &board) {
  cout << "\nBumblebee's Turn!";
  srand(time(NULL));
  int x, y;
  do {
    x = rand() % 10;
    y = rand() % 10;
  } while (board[x][y] == 'X' || board[x][y] == 'O');
  if (board[x][y] == '~') {
    board[x][y] = 'O';
    cout << "\nBumblebee misses";
  } else {
    board[x][y] = 'X';
    cout << "\nBumblebee hits!";
  }
}

void penguinTurn(vector<vector<char>> &board) {
  cout << "\nPenguin's Turn!";
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (board[i][j] == 'M') {
        board[i][j] = 'X';
        cout << "\nPenguin hits! Look at how awesome he is!";
        return;
      }
    }
  }
}

stack<pair<int, int>> nextToCheck;
void dinosaurTurn(vector<vector<char>> &board) {
  cout << "\nDinosaur's Turn!";
  srand(time(NULL));

  // The board is not empty and the stack is empty
  if (nextToCheck.empty()) {
    int x, y;
    do {
      x = rand() % 10;
      y = rand() % 10;
    } while (board[x][y] == 'X' || board[x][y] == 'O');

    if (board[x][y] == '~') {
      board[x][y] = 'O';
      cout << "\nMiss!";
      return;
    } else {
      board[x][y] = 'X';
      cout << "\nHit!";
      if (x > 0)
        nextToCheck.push({x - 1, y});
      if (x < 9)
        nextToCheck.push({x + 1, y});
      if (y > 0)
        nextToCheck.push({x, y - 1});
      if (y < 9)
        nextToCheck.push({x, y + 1});
      return;
    }
  }

  // There are cells to check
  while (!nextToCheck.empty()) {
    int x = nextToCheck.top().first;
    int y = nextToCheck.top().second;
    nextToCheck.pop();

    // Check if the cell has been checked before
    if (board[x][y] != 'X' && board[x][y] != 'O') {
      if (board[x][y] == 'M') {
        board[x][y] = 'X';
        cout << "\nDinosaur hits! Roar!\n";
        // Check around the cell
        if (x > 0)
          nextToCheck.push({x - 1, y});
        if (x < 9)
          nextToCheck.push({x + 1, y});
        if (y > 0)
          nextToCheck.push({x, y - 1});
        if (y < 9)
          nextToCheck.push({x, y + 1});
        return;
      } else {
        board[x][y] = 'O';
        cout << "\nDinosaur misses :(\n";
        return;
      }
    }
  }
}

void humanTurn(vector<vector<char>> &board, int player) {
  int x, y;
  do {
    cout << "Player " << player
         << ", enter the x and y coordinates you want to hit (The board is "
            "10x10):\n";

    while (!(cin >> y)) {
      cout << "Please enter valid integers (1-10):\n";
      cin.clear();
      cin.ignore(100, '\n');
    }

    while (!(cin >> x)) {
      cout << "Please enter valid intergers (1-10):\n";
      cin.clear();
      cin.ignore(100, '\n');
    }
  } while (x > 10 || x < 1 || y > 10 || y < 1);
  x--;
  y--;
  if (board[x][y] == 'M') {
    board[x][y] = 'X';
    cout << "\nPlayer " << player << " hits!";
  } else if (board[x][y] == '~') {
    board[x][y] = 'O';
    cout << "\nPlayer " << player << " misses";
  }
}

int main() {

  vector<vector<char>> board1(10, vector<char>(10, '~'));
  vector<vector<char>> board2(10, vector<char>(10, '~'));

  generateShips(board1, board2);

  cout << "Welcome to Penguin's battleship game! You might win, but not "
          "against Penguin ;)\n\n";
  cout << "To input coords, put x coord space y coord (x and y are 1-10)\n";

  cout << "\nPick your opponent! \n1) Another human \n2) Dinosaur "
          "(Medium-Hard) \n3) Penguin (Impossible) \n4) Bumblebee (Too Easy) "
          "\nInput your choice (1-4): ";
  // cout << "\n\e[9mYou see, the purpose of the order is so that you will play
  // another human, and then play Dinosaur, the next challenge after that, and
  // then play Penguin after beating Dinosaur, and then get so demoralised from
  // that experience that you will play Bumblebee to raise your self-esteem back
  // up.\e[m\nInput your choice (1-4): ";
  int player2;
  while (!(cin >> player2) || player2 < 1 || player2 > 4) {
    cout << "Please enter an integer (1-4): ";
    cin.clear();
    cin.ignore(100, '\n');
  }

  for (int turn = 1; turn <= 200; turn++) {
    if (turn % 2 == 1) {
      humanTurn(board1, 1);
      cout << "\nTurn " << turn;
      if (checkWin(board1)) {
        cout << "Player 1 wins!";
        printEnd(board2);
        break;
      }
      print(board1);
    }

    else {
      if (player2 == 1)
        humanTurn(board2, 2);
      else if (player2 == 2)
        dinosaurTurn(board2);
      else if (player2 == 3)
        penguinTurn(board2);
      else
        bumblebeeTurn(board2);

      if (checkWin(board2)) {
        string text;
        if (player2 == 1)
          cout << "Player 2 wins!";
        else if (player2 == 2) {
          cout << "Dinosaur wins!";
          ifstream fileout("dinosaur.txt");
          while (getline(fileout, text)) {
            cout << text << '\n';
          }
          fileout.close();
        } else if (player2 == 3) {
          cout << "Penguin wins!";
          ifstream fileout("penguin.txt");
          while (getline(fileout, text)) {
            cout << text << '\n';
          }
          fileout.close();
        } else
          cout << "Bumblebee wins (and you're actually bad how did you lose)";
        printEnd(board1);
        break;
      }
      print(board2);
    }
  }

  cout << "\nThank you for playing Penguin's Battleship game! Hope you have a "
          "penguin day\n";
}
