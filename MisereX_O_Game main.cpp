#include <iostream>
#include "BoardGame_Classes.h"
#include "MisereX_O_Game.h"
using namespace std;

int main() {
    int choice1, choice2;
    Player<char>* players[2];
    MisereX_O_Board<char>* board = new MisereX_O_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI MisereX-O Game. :)\n";

    // Set up player 1 type first
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice1;

    // Ask for player 1 name only if human
    if (choice1 == 1) {
        cout << "Enter Player X name: ";
        cin >> playerXName;
    } else {
        playerXName = "Random Computer X"; // Default name for random player
    }

    // Set up player 2 type
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice2;

    // Ask for player 2 name only if human
    if (choice2 == 1) {
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
    } else {
        player2Name = "Random Computer O"; // Default name for random player
    }

    // Set up player 1
    switch(choice1) {
        case 1:
            players[0] = new MisereX_O_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new MisereX_O_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    switch(choice2) {
        case 1:
            players[1] = new MisereX_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new MisereX_O_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // If one player is random, set the name accordingly
    if (choice1 == 1 && choice2 == 2) {
        player2Name = "Random Computer O";  // Set Player 2 name as Random Computer O
    } else if (choice1 == 2 && choice2 == 1) {
        playerXName = "Random Computer X";  // Set Player 1 name as Random Computer X
    } else if (choice1 == 2 && choice2 == 2) {
        playerXName = "Random Computer X";  // Set Player 1 name as Random Computer X
        player2Name = "Random Computer O";  // Set Player 2 name as Random Computer O
    }

    swap(playerXName, player2Name);
    static_cast<MisereX_O_Player<char>*>(players[0])->setName(playerXName);  // Update name for player 1
    static_cast<MisereX_O_Player<char>*>(players[1])->setName(player2Name);  // Update name for player 2

    // Create the game manager and run the game
    GameManager<char> misere_x_o_game(board, players);
    misere_x_o_game.run();

    // Clean up
    delete board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
