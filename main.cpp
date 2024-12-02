#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "Pyramid_XO.h"

using namespace std;

int main() {
    cout << "The board contains cells [ x , y ] , every cell has row number (x) and column number (y)\n";
    cout << "so this is the board and each cell's information :\n";
    cout << "                   -- [ 0 , 2 ] -- \n";
    cout << "          - [ 1 , 1 ] [ 1 , 2 ] [ 1 , 3 ] - \n";
    cout << "  [ 2 , 0 ] [ 2 , 1 ] [ 2 , 2 ] [ 2 , 3 ] [ 2 , 4 ] \n";
    cout << "-----------------------------------------------------\n";
    cout << "You have to enter the row's number first , then the column's number(space between 'EM). \n";
    cout << "                    Have a good game! :)                         \n";
    cout << endl;

    int choice;
    Player<char>* players[2];
    Board_XO<char>* B = new Board_XO<char>();
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
        case 1:
            players[0] = new Player_XO<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new RandomPlayer_XO<char>('X');
            break;
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
        case 1:
            players[1] = new Player_XO<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new RandomPlayer_XO<char>('O');
            break;
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
