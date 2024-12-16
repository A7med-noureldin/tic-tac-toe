#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "Pyramid_XO.h"
#include "Word_TicTacToe.h"
#include "Numerical_X_O.h"
using namespace std;
// Function to set up a player
template <typename T>
Player<T>* setupPlayer(const string& playerName, int playerType, Board<T>* board) {
    switch(playerType) {
        case 1: // Human Player
            return new Numerical_X_O_player<T>(playerName, 1);
        case 2: // Random Computer
            return new Numerical_X_O_Random_Player<T>(1);
        default:
            cout << "Invalid choice. Exiting the game setup.\n";
            return nullptr;
    }
}

// Menu to choose a game
void displayMenu() {
    cout << "================ Game Menu ================\n";
    cout << "1. Numerical Tic-Tac-Toe\n";
    cout << "2. Word Tic-Tac-Toe\n";
    cout << "3. Pyramid Tic-Tac-Toe\n";
    cout << "0. Exit\n";
    cout << "===========================================\n";
    cout << "Choose a game: ";
}
int main() {
    srand(time(0));
    int choice;
    Player<char>* players[2];
    Numerical_X_O_board<char>* B = new Numerical_X_O_board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
//    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1: {
            // Create a new Numerical_X_O_player instance
            players[0] = new Numerical_X_O_player<char>(playerXName, 1);

            // Access the derived class instance to print or use numbers_pool if needed
            Numerical_X_O_player<char> *numericalPlayer = dynamic_cast<Numerical_X_O_player<char> *>(players[0]);

            if (numericalPlayer) {
                B->numbers_pool[0] = &numericalPlayer[0].numbers_pool;
                cout << "setting numbers pool" << endl;
            }
            break;
        }
        case 2: {
            players[0] = new Numerical_X_O_Random_Player<char>(1);

            // Access the derived class instance to print or use numbers_pool if needed
            Numerical_X_O_Random_Player<char> *numericalPlayer = dynamic_cast<Numerical_X_O_Random_Player<char> *>(players[0]);

            if (numericalPlayer) {
                B->numbers_pool[0] = &numericalPlayer[0].numbers_pool;
                cout << "setting numbers pool" << endl;
            }
            break;
        }
//        case 3:
//            players[0] = new X_O_MinMax_Player<char>('X');
//            players[0]->setBoard(B);
//            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
//    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1: {
            players[1] = new Numerical_X_O_player<char>(player2Name, 2);
            Numerical_X_O_player<char> *numericalPlayer = dynamic_cast<Numerical_X_O_player<char> *>(players[1]);

            if (numericalPlayer) {
                B->numbers_pool[1] = &numericalPlayer[0].numbers_pool;
                cout << "setting numbers pool" << endl;
            }
            break;
        }
        case 2: {
            players[1] = new Numerical_X_O_Random_Player<char>(2);
            Numerical_X_O_Random_Player<char> *numericalPlayer = dynamic_cast<Numerical_X_O_Random_Player<char> *>(players[1]);

            if (numericalPlayer) {
                B->numbers_pool[1] = &numericalPlayer[0].numbers_pool;
                cout << "setting numbers pool" << endl;
            }
            break;
        }
//        case 3:
//            players[1] = new X_O_MinMax_Player<char>('O');
//            players[1]->setBoard(B);
//            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }


    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}