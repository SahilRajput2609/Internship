#include <iostream>
using namespace std;

// Display the game board
void displayBoard(char board[3][3]) {
    cout << "\n";
    cout << "       TIC TAC TOE\n";
    cout << "=======================\n";

    for (int i = 0; i < 3; i++) {
        cout << "       |       |       \n";

        for (int j = 0; j < 3; j++) {
            cout << "   " << board[i][j] << "   ";

            if (j < 2)
                cout << "|";
        }

        cout << "\n";

        if (i < 2)
            cout << "-------|-------|-------\n";
    }

    cout << "       |       |       \n";
    cout << "=======================\n";
}

// Check whether a player has won
bool checkWin(char board[3][3], char player) {

    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player &&
            board[1][j] == player &&
            board[2][j] == player) {
            return true;
        }
    }

    // Check first diagonal
    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player) {
        return true;
    }

    // Check second diagonal
    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player) {
        return true;
    }

    return false;
}

// Check whether the board is full
bool checkDraw(char board[3][3]) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            if (board[i][j] != 'X' &&
                board[i][j] != 'O') {
                return false;
            }
        }
    }

    return true;
}

// Play one complete game
void playGame() {

    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char player = 'X';
    int choice;

    while (true) {

        displayBoard(board);

        cout << "\nPlayer " << player
             << ", enter a position (1-9): ";
        cin >> choice;

        // Validate input
        if (choice < 1 || choice > 9) {
            cout << "\nInvalid position! Enter a number from 1 to 9.\n";
            continue;
        }

        // Convert position to row and column
        int row = (choice - 1) / 3;
        int column = (choice - 1) % 3;

        // Check whether position is already occupied
        if (board[row][column] == 'X' ||
            board[row][column] == 'O') {

            cout << "\nPosition already occupied! Try again.\n";
            continue;
        }

        // Place player's symbol
        board[row][column] = player;

        // Check for winner
        if (checkWin(board, player)) {

            displayBoard(board);

            cout << "\n================================\n";
            cout << "       PLAYER " << player << " WINS!\n";
            cout << "================================\n";

            break;
        }

        // Check for draw
        if (checkDraw(board)) {

            displayBoard(board);

            cout << "\n================================\n";
            cout << "           GAME DRAW!\n";
            cout << "================================\n";

            break;
        }

        // Change player
        if (player == 'X')
            player = 'O';
        else
            player = 'X';
    }
}

// Main function
int main() {

    char replay;

    cout << "=====================================\n";
    cout << "        TIC TAC TOE GAME\n";
    cout << "=====================================\n";

    do {

        playGame();

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> replay;

    } while (replay == 'Y' || replay == 'y');

    cout << "\nThank you for playing Tic Tac Toe!\n";

    return 0;
}
