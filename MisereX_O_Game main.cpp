#include <iostream>
#include "BoardGame_Classes.h"
#include "MisereX_O_Game.h"
#include "MinMaxPlayer.h"
using namespace std;

int main() {
    int choice1, choice2;
    Player<char>* players[2];
    MisereX_O_Board<char>* board = new MisereX_O_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI MisereX-O Game. :)\n";

    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. MinMax AI Player\n";
    cin >> choice1;

    if (choice1 == 1) {
        cout << "Enter Player X name: ";
        cin >> playerXName;
    } else if (choice1 == 3) {
        playerXName = "AI Player X";
    } else {
        playerXName = "Random Computer X";
    }

    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. MinMax AI Player\n";
    cin >> choice2;

    if (choice2 == 1) {
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
    } else if (choice2 == 3) {
        player2Name = "AI Player O";
    } else {
        player2Name = "Random Computer O";
    }

    if (choice1 == 1 && choice2 == 2) {
        player2Name = "Random Computer O";
    } else if (choice1 == 2 && choice2 == 1) {
        playerXName = "Random Computer X";
    } else if (choice1 == 2 && choice2 == 2) {
        playerXName = "Random Computer X";
        player2Name = "Random Computer O";
    }

    swap(playerXName, player2Name);
    static_cast<MisereX_O_Player<char>*>(players[0])->setName(playerXName);
    static_cast<MisereX_O_Player<char>*>(players[1])->setName(player2Name);

    switch(choice1) {
        case 1:
            players[0] = new MisereX_O_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new MisereX_O_Random_Player<char>('X');
            break;
        case 3:
            players[0] = new X_O_MinMax_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    switch(choice2) {
        case 1:
            players[1] = new MisereX_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new MisereX_O_Random_Player<char>('O');
            break;
        case 3:
            players[1] = new X_O_MinMax_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    GameManager<char> misere_x_o_game(board, players);
    misere_x_o_game.run();

    delete board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
