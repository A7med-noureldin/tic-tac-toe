#include <iostream>
#include "BoardGame_Classes.h"
#include "MinMaxPlayer.h"
#include "Connect4.h"
#include "G9x9_X_O.h"
using namespace std;

int main() {
//    int choice;
//    Player<char>* players[2];
//    auto* B = new Connect4_board<char>();
//    string playerXName, player2Name;
//
//    cout << "Welcome to FCAI X-O Game. :)\n";
//
//    // Set up player 1
//    cout << "Enter Player X name: ";
//    cin >> playerXName;
//    cout << "Choose Player X type:\n";
//    cout << "1. Human\n";
//    cout << "2. Random Computer\n";
//    cout << "3. Smart Computer (AI)\n";
//    cin >> choice;
//
//    switch(choice) {
//        case 1:
//            players[0] = new Connect4_Player<char>(playerXName, 'X');
//            break;
//        case 2:
//            players[0] = new Connect4_Random_Player<char>(6, 7, 'X');
//            break;
//        case 3:
//            players[0] = new Connect4_MCTSPlayer<char>('X');
//            players[0]->setBoard(B);
//            break;
//        default:
//            cout << "Invalid choice for Player 1. Exiting the game.\n";
//            delete B;
//            return 1;
//    }
//
//    // Set up player 2
//    cout << "Enter Player 2 name: ";
//    cin >> player2Name;
//    cout << "Choose Player 2 type:\n";
//    cout << "1. Human\n";
//    cout << "2. Random Computer\n";
//    cout << "3. Smart Computer (AI)\n";
//    cin >> choice;
//
//    switch(choice) {
//        case 1:
//            players[1] = new Connect4_Player<char>(player2Name, 'O');
//            break;
//        case 2:
//            players[1] = new Connect4_Random_Player<char>(6, 7, 'O');
//            break;
//        case 3:
//            players[1] = new Connect4_MCTSPlayer<char>('O');
//            players[1]->setBoard(B);
//            break;
//        default:
//            cout << "Invalid choice for Player 2. Exiting the game.\n";
//            delete B;
//            return 1;
//    }
//
//    // Set board for all players
//    players[0]->setBoard(B);
//    players[1]->setBoard(B);
//
//    // Create the game manager and run the game
//    GameManager<char> connect4_game(B, players);
//    connect4_game.run();
//
//    // Clean up
//    delete B;
//    for (int i = 0; i < 2; ++i) {
//        delete players[i];
//    }

    int choice;
    Player<char>* players[2];
    auto* B = new XO9x9_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new XO9x9_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new XO9x9_Random_Player<char>('X');
            break;
        case 3:
            players[0] = new Connect4_MCTSPlayer<char>('X');
            players[0]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            delete B;
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new XO9x9_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new XO9x9_Random_Player<char>( 'O');
            break;
        case 3:
            players[1] = new Connect4_MCTSPlayer<char>('O');
            players[1]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            delete B;
            return 1;
    }

    // Set board for all players
    players[0]->setBoard(B);
    players[1]->setBoard(B);

    // Create the game manager and run the game
    GameManager<char> XO_9x9_game(B, players);
    XO_9x9_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    return 0;
}

