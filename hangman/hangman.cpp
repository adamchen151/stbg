#include <algorithm>
#include <iostream>
#include <vector>
#include <cctype>
#include <stdlib.h> // Clear console supposedly
#include <fstream>
using namespace std;

vector<string> words = {"penguin", "octopus", "dinosaur", "bumblebee", 
"jazz", "food", "happy", "sad", "amazing", "legendary", "angry",
"epic", "terrible", "earth", "giraffe", "fish", "salmon", "antartica", "alaska", "canada",
"water", "ocean", "lake", "bottle", "game", "video", "ship", "chess", "hangman", "checkers",
"pizza", "cup", "backpack", "school", "course", "different"};

void printbox(int wrongLetters) {
  string line1 = "    -------";
  string line2 = "    |     |";
  string line3 = "    |     ";
  string line4 = "    |    ";
  string line5 = "    |    ";
  string line6 = "----------";


  if (wrongLetters > 0) line3 += 'o';
  if (wrongLetters > 1) line4 += '-';
  if (wrongLetters > 2) line4 += '|';
  if (wrongLetters > 3) line4 += '-';
  if (wrongLetters > 4) line5 += '/';
  if (wrongLetters > 5) line5 += " \\";

  cout << '\n' << line1 << '\n' << line2 << '\n' << line3 << '\n' << line4 << '\n' << line5 << '\n' << line6 << '\n';
  if (wrongLetters > 6) cout << "You lose L bozo get good";
  }

string s1;

void letterbox(char c) { cout << "   Letters used: " << s1 << '\n'; }

// Generate a word
string getWord() {
  cout << "\nDo you want to use your own word instead of a pregenerated one (Y/N): ";
  char yesNo;
  cin >> yesNo;

  // Make sure wrong input doesn't mess up everything
  cin.clear();
  cin.ignore(100, '\n');

  // Get random word from words array
  srand(time(NULL));
  int random = rand() % words.size();
  string s = words[random]; // The word to guess

  if (tolower(yesNo) == 'y') {
    cout << "\nEnter the word to guess: ";
    cin >> s;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; // because system("CLS"); doesn't work
    return s;
  }
  
  return s;
}

int main() {
  string word = getWord();
  string s = word;
  for (int i = 0; i < word.size(); i++) {
    word[i] = '_';
  }

  char guess;
  int wrongLetters = 0;
  bool letterInWord;
  bool isRepeatLetter;

  while (wrongLetters < 7) {
    for (int i = 0; i < word.size(); i++) {
      cout << word[i] << ' ';
    }
    // cout << word;

    cout << "\nGuesser, enter a letter to guess: ";
    cin >> guess;
    cin.ignore(100, '\n');
    guess = tolower(guess);

    cout << "\n";
    for (int i = 0; i < word.size(); i++) {
      if (s[i] == guess) {
        word[i] = guess;
        letterInWord = true;
      }
    }

    for (int i = 0; i < s1.length(); i++) {
      if (s1[i] == guess) {
        isRepeatLetter = true;
        break;
      } else
        isRepeatLetter = false;
    }

    s1 += guess;

    if (isRepeatLetter) {
      cout << "\nYou already used this letter.";
    } else {
      if (!letterInWord) {
        wrongLetters++;
        letterbox(guess);
        cout << "\n\nThe letter isn't in the word. Tries left: " << 7 - wrongLetters;
        printbox(wrongLetters);
      }
      letterInWord = false;
    }

    if (word == s) {
      cout << "\nYou guessed the word!";
      break;
    }
  }
  if (wrongLetters >= 7) {
    cout << "\nBetter luck next time! The word was " << s << '.';
  }

  cout << "\nThank you for playing Penguin's Hangman game!\n";
  ifstream fileout("penguin.txt");
  string text;
  while (getline(fileout, text)) {
    std::cout << text << '\n';
  }
  fileout.close();
}
