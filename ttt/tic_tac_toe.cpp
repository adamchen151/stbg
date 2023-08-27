#include <iostream>
#include <vector>
#include <fstream>
#include "functions.h"
using namespace std;
void print(vector<char> v) {
  cout << v[0] << " | " << v[1] << " | " << v[2] << "\n";
  cout << v[3] << " | " << v[4] << " | " << v[5] << "\n";
  cout << v[6] << " | " << v[7] << " | " << v[8] << "\n";
}

bool checkWin(vector<char> v) {
  for (int i = 0; i < 3; i++) if (v[i] == v[i+3] && v[i] == v[i+6]) return true; //Columns
  for (int i = 0; i < 7; i += 3) if (v[i] == v[i+1] && v[i] == v[i+2]) return true; //Rows
  if ((v[0] == v[4] && v[0] == v[8]) || (v[2] == v[4] && v[2] == v[6])) return true; //Diagonals
  return false;
}

void takeTurn(vector<char> &v, char c, int player) {
  int i;
  cout << "\nPlayer " << player << ", enter the square to place your marker: ";
  while (!(cin >> i) || i < 1 || i > 9 || v[i-1] == 'X' || v[i-1] == 'O') { //Check if input is valid
    cin.clear();
    cin.ignore();
    v[i-1] == 'X' || v[i-1] == 'O' ? cout << "This square is already used. Try again: " : cout << "\nInvalid entry. Try again: ";
  }
  v[i-1] = c;
}

void funnyComments(vector<char> v, int turn) {
  if (turn == 1 && v[4] == 'X') cout << "\nImagine going in the middle first cringe gameplay\n";
  if (turn == 9 && v[4] == 'X') cout << "\nWhat the flip happened lmao\n";
}

int main() {
  cout << "Penguin's Epic Tic-Tac-Toe Game he made because he has nothing to do and he's bored.\n\n";
  vector<char> v = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  
  for(int turn = 1; turn <= 9; turn++) {
    print(v);
    turn % 2 == 1 ? takeTurn(v, 'X', 1) : aiTurn(v, 'O', 2);

    funnyComments(v, turn);
    
    if (checkWin(v)) {
      print(v);
      cout << "\nPlayer " << turn % 2 << " has won!";
      break;
    }
    if (turn == 9 && !checkWin(v)) cout << "\nTie. What a boring ending";
  }

  cout << "\nThank you for playing Penguin's Tic-Tac-Toe game!\n";
  ifstream fileout("penguin.txt");
  string text;
  while (getline(fileout, text)) {
    std::cout << text << '\n';
  }
  fileout.close();
}
