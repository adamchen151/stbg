#include <iostream>
#include <vector>
#include <utility>

struct Piece {
    bool isKing = false;
    char color;
};

std::pair<int, int> getInput(std::string text) {
    int x, y;
    std::cout << text;
    std::cin >> y >> x;
        while (std::cin.fail()) {
            std::cin.clear();  // Clear the error state
            std::cin.ignore(100, '\n');  // Ignore the rest of the line
            std::cout << "Invalid input. Please enter two integers seperated by a space: ";
            std::cin >> y >> x;
        }
    x--; y--;
    return std::make_pair(x, y);
}

std::vector<std::vector<Piece>> board(8, std::vector<Piece>(8));

void initializeBoard() {
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if((i+j) % 2 == 1) {
                if(i < 3) board[i][j] = {false, 'R'};
                else if(i > 4) board[i][j] = {false, 'B'};
            } 
        }
    }
}

void printBoard() {
    std::cout << "  1 2 3 4 5 6 7 8\n\n";
    for(int i=0; i<8; i++) {
        std::cout << i+1 << " ";
        for(int j=0; j<8; j++) {
            if((i+j) % 2 == 0) std::cout << " ";
            else if(board[i][j].color == 'R') {
              !board[i][j].isKing ? std::cout << "R" : std::cout << "ℝ";
            }

            else if(board[i][j].color == 'B') {
              !board[i][j].isKing ? std::cout << "B" : std::cout << "𝔹";
            }

            else std::cout << "-";
            std::cout << " ";
        }
        std::cout << "\n\n";
    }
}

//Check win and print win text
bool checkWin() {
    bool isRed = false, isBlack = false;
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(board[i][j].color == 'R') isRed = true;
            if(board[i][j].color == 'B') isBlack = true;
        }
    }
    if (!isRed) {
        std::cout << "Black Wins!";
        return true;
    }
    if (!isBlack) {
        std::cout << "Red Wins!";
        return true;
    }

    return false;
}

bool isValid(int x1, int y1, int x2, int y2, char color) {
  //Something's wrong
    if ((x2+y2) % 2 == 0 || (x1+y1) % 2 == 0 || x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || x1 > 7 || y1 > 7 || x2 > 7 || y2 > 7) {
        std::cout << "Invalid coordinates";
        return false;
    }

    if (board[x1][y1].color != color) {
        std::cout << "That is not your piece";
        return false;
    } 

    if (board[x2][y2].color == color) {
        std::cout << "The new square is occupied";
        return false;
    }

    if (color == 'R' && x2 < x1 && !board[x1][y1].isKing ||
      color == 'B' && x2 > x1 && !board[x1][y1].isKing) {
        std::cout << "You can't move backwards";
        return false;
    }

    //If jump
    if(abs(x2 - x1) == 2 && abs(y2 - y1) == 2) {
        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;

        if (board[midX][midY].color == board[x1][y1].color) {
            std::cout << "The attempted jump collides with your own piece";
        } 
        if (board[midX][midY].color == '\0') { // '\0' is NULL
            std::cout << "The attempted jump jumps over nothing";
        } 
    }

    return true;
}

bool isJumpPossible(int x1, int y1, char color) {
    // Check all 4 possible jump directions
    int directions[4][2] = {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}};
    
    for(int i=0; i<4; ++i) {
        int newX = x1 + directions[i][0];
        int newY = y1 + directions[i][1];
        
        if(newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            int midX = x1 + directions[i][0] / 2;
            int midY = y1 + directions[i][1] / 2;
            
            // If there's an enemy piece to jump over and the landing spot is empty, and the piece is moving forward if not a king
            if(board[midX][midY].color != color && board[midX][midY].color != '\0' && board[newX][newY].color == '\0' 
              && color == 'R' && midX > x1 && !board[x1][y1].isKing ||
      color == 'B' && midX < x1 && !board[x1][y1].isKing) {
                return true;
            }
        }
    }
    return false;
}

// Move piece from (x1, y1) to (x2, y2)
bool movePiece(int x1, int y1, int x2, int y2, char color) {
    bool wasJump = false;
    
    if(abs(x2 - x1) == 2 && abs(y2 - y1) == 2) {
        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;

        board[midX][midY] = Piece(); //Empty Piece
        wasJump = true;
    }
    
    std::swap(board[x1][y1], board[x2][y2]);

    //TODO add option to decline jump
    if(isJumpPossible(x2, y2, color) && wasJump) {
        printBoard();
        std::pair<int, int> after = getInput("\nAnother jump is possible. Please enter the next move: ");
    
        if (isValid(x2, y2, after.first, after.second, color)) {  
          movePiece(x2, y2, after.first, after.second, color);
        }
    }

    //Make kings
    if (color == 'R' && x2 == 8 || color == 'B' && x2 == 1) {
        board[x2][y2].isKing = true;
    }

    return true;
}
