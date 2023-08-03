#include <iostream>
#include <vector>
#include <utility> //pair
#include "functions.h"

//Not playing with forced captures, because that's lame


int main() {
    initializeBoard();
    int turn = 1;
  
    while (!checkWin()) {
        char color = turn++ % 2 == 0 ? 'R' : 'B';
        printBoard();
        color == 'R' ? std::cout << "Red's turn!\n" : std::cout << "Black's turn!\n";

        //Move
        bool hasMoved = false;
        do {
            std::pair<int, int> before = getInput("\nEnter the coordinates of the piece you want to move: ");
            std::pair<int, int> after = getInput("\nEnter the coordinates of where you want to move the piece: ");
          
            if (isValid(before.first, before.second, after.first, after.second, color)) {
                movePiece(before.first, before.second, after.first, after.second, color);
                hasMoved = true;
            }
        } while (!hasMoved);
        
    }
    return 0;
}
