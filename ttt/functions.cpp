#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

bool isEmpty(char c) {
    return c != 'X' && c != 'O';
}

int almostWin(vector<char> &v, char c) {
    vector<vector<int>> rows = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    int n = rows.size();
    for (int i = 0; i < n; i++) {
        if (v[rows[i][0]] == v[rows[i][1]] && !isEmpty(v[rows[i][0]]) && isEmpty(v[rows[i][2]])) 
            return rows[i][2];
        if (v[rows[i][0]] == v[rows[i][2]] && !isEmpty(v[rows[i][0]]) && isEmpty(v[rows[i][1]])) 
            return rows[i][1];
        if (v[rows[i][1]] == v[rows[i][2]] && !isEmpty(v[rows[i][1]]) && isEmpty(v[rows[i][0]])) 
            return rows[i][0];
    }
    return -1;
}

void aiTurn(vector<char> &v, char c, int player) {
    cout << "Penguin's Turn!\n";
    int move = almostWin(v, c);
    // If there is a needed move
    if (move != -1) {
        v[move] = c;
        return;
    }

    srand(time(NULL));
    int marker;
    bool moved = false;
    // Randomly generate an index until a move is possible
    do {
        // Ensure middle/top corner is taken if Penguin is 'O'. This ensures Penguin can't lose
        if (c == 'O' && isEmpty(v[4])) {
            v[4] = c;
            return;
        } 

        marker = rand() % 9;
        if (isEmpty(v[marker])) {
            v[marker] = c;
            moved = true;
        }
    } while (!moved);
}