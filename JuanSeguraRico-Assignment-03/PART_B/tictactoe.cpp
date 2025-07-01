//
// Created by Juan Segura Rico on 6/30/23.
//

#include "tictactoe.h"
#include <iostream>
using namespace std;

bool isWin(const char& player, const char board[][3]) {
    // check horizontal and vertical moves
    for (int i = 0; i < sizeof(board); i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // check diagonal moves
    if (board[1][1] == player && ((board[0][0] == player && board[2][2] == player) || (board[2][0] == player && board[0][2] == player))) {
        return true;
    }

    return false;
}

bool isDraw(char board[][3]) {
    if (board[0][0] != ' ' && board[0][1] != ' ' && board[0][2] != ' '
        && board[1][0] != ' ' && board[1][1] != ' ' && board[1][2] != ' '
        && board[2][0] != ' ' && board[2][1] != ' ' && board[2][2] != ' ')
        return true;
    else return false;
}

void displayBoard(char board[][3]) {
    cout << "-------------" << endl;
    cout << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |" << endl;
    cout << "-------------" << endl;
    cout << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |" << endl;
    cout << "-------------" << endl;
    cout << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |" << endl;
    cout << "-------------" << endl;
}

void makeAMove(char board[][3], const char& player) {

    int row;
    int col;
    bool done = false;

    while (!done) {
        do { // enter row, request re-enter if invalid choice
            cout << "Enter a row (0, 1, 2) for player " << player << "   : ";
            cin >> row;
            if (row != 0 && row != 1 && row != 2) {
                cout << "Please enter 0 or 1 or 2." << endl;
            }
        } while (row != 0 && row != 1 && row != 2);

        do { // enter row, request re-enter if invalid choice
            cout << "Enter a column (0, 1, 2) for player " << player << ": ";
            cin >> col;
            if (col != 0 && col != 1 && col != 2) {
                cout << "Please enter 0 or 1 or 2." << endl;
            }
        } while (col != 0 && col != 1 && col != 2);

        if (board[row][col] == ' ') { // if empty place player
            board[row][col] = player;
            done = true;
        }
        else { // if not empty try again
            cout << "This cell is already occupied.  Try a different cell." << endl;
        }
    }
}

int main() {

    char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
    displayBoard(board);

    while (true) {

        makeAMove(board, 'X');
        displayBoard(board);
        if (isWin('X', board)) {
            cout << "X player won" << endl;
            exit(0);
        }
        else if (isDraw(board)) {
            cout << "No winner" << endl;
            exit(0);
        }


        makeAMove(board, 'O');
        displayBoard(board);

        if (isWin('O', board)) {
            cout << "O player won" << endl;
            exit(0);
        }
        else if (isDraw(board)) {
            cout << "No winner" << endl;
            exit(0);
        }
    }

    return 0;
}