#include <iostream>
#include "BoardGame_Classes.h"
#include "5x5TicTacToe.h"
using namespace std;

int main() {
    int choice1, choice2;
    Player<char>* players[2];
    TicTacToe5x5Board<char>* board = new TicTacToe5x5Board<char>();
    string playerXName, playerOName;

    cout << "Welcome to FCAI 5x5 Tic-Tac-Toe Game. :)\n";

    // Set up player X type first
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice1;

    // Ask for player X name only if human
    if (choice1 == 1) {
        cout << "Enter Player X name: ";
        cin >> playerXName;
    } else {
        playerXName = "Random Computer X"; // Default name for random player
    }

    // Set up player O type
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice2;

    // Ask for player O name only if human
    if (choice2 == 1) {
        cout << "Enter Player O name: ";
        cin >> playerOName;
    } else {
        playerOName = "Random Computer O"; // Default name for random player
    }

    // Set up player X
    switch (choice1) {
        case 1:
            players[0] = new TicTacToePlayer<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new TicTacToeRandomPlayer<char>('X');
            break;
        default:
            cout << "Invalid choice for Player X. Exiting the game.\n";
            delete board;
            return 1;
    }

    // Set up player O
    switch (choice2) {
        case 1:
            players[1] = new TicTacToePlayer<char>(playerOName, 'O');
            break;
        case 2:
            players[1] = new TicTacToeRandomPlayer<char>('O');
            break;
        default:
            cout << "Invalid choice for Player O. Exiting the game.\n";
            delete board;
            return 1;
    }

    // If one player is random, set the name accordingly
    if (choice1 == 2) {
        playerXName = "Random Computer X";
    }
    if (choice2 == 2) {
        playerOName = "Random Computer O";
    }

    // Update player names for display
    static_cast<TicTacToePlayer<char>*>(players[0])->setName(playerXName);
    static_cast<TicTacToePlayer<char>*>(players[1])->setName(playerOName);

    // Create the game manager and run the game
    GameManager<char> game_manager(board, players);  // Create game manager
    game_manager.run();  // Start the game

    // Display final scores
    auto scores = board->get_scores();
    cout << "Final Scores:\n";
    cout << playerXName << " (X): " << scores.first << "\n";
    cout << playerOName << " (O): " << scores.second << "\n";

    if (scores.first > scores.second)
    {
        cout << playerXName << " wins!\n";
    }
    else if (scores.second > scores.first)
    {
        cout << playerOName << " wins!\n";
    }
    else
    {
        cout << "It's a draw!\n";
    }

    // Clean up
    delete board;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }

    return 0;
}
