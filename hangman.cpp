#include <algorithm>
#include <iostream>
using namespace std;

void printbox(int lose) {
  if (lose > 0)
    cout << "\n\n----------\n";
  if (lose > 1)
    cout << "    |\n";
  if (lose > 2)
    cout << "    o\n";
  if (lose > 3)
    cout << "   -|-\n";
  if (lose > 4)
    cout << "   / \\\n";
  if (lose > 5)
    cout << "----------\n";
  if (lose > 6)
    cout << " You Lose!\n";
}

string s1;

void letterbox(char c) { cout << "   Letters used: " << s1 << '\n'; }

int main() {
  string s = "penguin"; // The word to guess
  string win;
  win.resize(s.size());
  for (int i = 0; i < win.size(); i++) {
    win[i] = '_';
  }

  char guess;
  int lose = 0;
  bool check;
  bool repeat;

  while (lose < 7) {
    cout << "\nGuesser, enter a letter to guess: ";
    cin >> guess;
    cin.ignore(100, '\n');

    cout << "\n";
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == guess) {
        win[i] = guess;
        check = true;
      }
    }

    cout << win;

    for (int i = 0; i < s1.length(); i++) {
      if (s1[i] == guess) {
        repeat = true;
        break;
      } else
        repeat = false;
    }

    s1 += guess;

    if (repeat) {
      cout << "\nYou already used this letter.";
    } else {
      if (!check) {
        lose++;
        letterbox(guess);
        cout << "\n\nThe letter isn't in the word. Tries left: " << 7 - lose;
        printbox(lose);
      }
      check = false;
    }

    if (win == s) {
      cout << "\nYou guessed the word!";
      break;
    }
  }
  if (lose >= 7) {
    cout << "\nBetter luck next time! The word was " << s;
  }
}
