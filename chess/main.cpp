#include "ai.h"
#include "functions.h"
#include "move.h"
#include <iostream>
#include <vector>
// Clean Makefile using make clean
/*
g++ -c helloWorld.cpp hello.cpp
It compiles and creates object code for the files helloWorld.cpp and hello.cpp to helloWorld.o and hello.o respectively.
 
g++ -o main.exe helloWorld.o hello.o
It links the object codes helloWorld.o and hello.o to create an executable file main.exe
 
// one file
g++ helloWorld.cpp
*/

int main() {
  int turn = 1;
  char colour;
  initializeBoard();
  std::pair<int, int> b, e; // beginning coords, end coords
  
  bool isMove;

  std::cout << "Do you want to play against an AI, or against another human (Y/N): ";
  std::cin >> colour;
  tolower(colour) == 'y' ? isAI = true : isAI = false;
  if (isAI) {
    std::cout << "What colour do you want the AI to be (W/B): ";
    std::cin >> colour;
    tolower(colour) == 'w' ? aiColour = 'W' : aiColour = 'B';
  }
  do {
    colour = turn % 2 == 1 ? 'W' : 'B';
    colour == 'W' ? std::cout << "White's turn!" : std::cout << "Red's turn!";
    printBoard();
    turn++;
    isMove = false;

    if (!isAI || colour != aiColour) {
      while (!isMove) {
        do {
          b = getInput("\nInput the starting coordinates (xy): ");
          // Have to somehow validate ending coords
          e = getInput("Input the ending coordinates (xy): ");
        } while (board[b.first][b.second].colour != colour);

        if (board[b.first][b.second].colour ==
            board[e.first][e.second].colour) {
          std::cout << "\nYou moved to a square that you occupy";
          continue;
        }

        if (movePiece(b.first, b.second, e.first, e.second))
          isMove = true;
        if (!isMove)
          std::cout << "\nYour move failed";
      }
    }

    if (isAI && colour == aiColour) {
      move m = decide_move(colour);
      movePiece(m.x1, m.y1, m.x2, m.y2);
    }
  } while (!isWin(colour));

  std::cout << "\nThank you for playing Penguin's Chess game!";
}