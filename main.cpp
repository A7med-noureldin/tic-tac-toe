#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "Pyramid_XO.h"
#include "Word_TicTacToe.h"
#include "Numerical_X_O.h"
#include "Connect4.h"
#include "5x5TicTacToe.h"
#include "MisereX_O_Game.h"
#include "G9x9_X_O.h"
#include "TicTacToe_Prob7.h"
using namespace std;

int getChoice(int max) {
    int choice;
    while (true) {
        cout << "Enter your choice (1 to " << max << "): ";
        cin >> choice;

        if (choice >= 1 && choice <= max) {
            return choice; // Return valid choice
        } else {
            cout << "Invalid choice. Please enter a number between " << 1 << " and " << max << ".\n";
        }
    }
    return choice;
}

// Menu to choose a game
void displayMenu() {
    cout << "================ Game Menu ================\n";
    cout << "1. Pyramid Tic-Tac-Toe\n";
    cout << "2. Connect 4\n";
    cout << "3. 5 x 5 Tic Tac Toe\n";
    cout << "4. Word Tic-Tac-Toe\n";
    cout << "5. Numerical Tic-Tac-Toe\n";
    cout << "6. Misere Tic Tac Toe\n";
    cout << "7. 4 x 4 Tic-Tac-Toe\n";
    cout << "8. Ultimate Tic Tac Toe\n";
    cout << "0. Exit\n";
    cout << "===========================================\n";
    cout << "Choose a game: ";
}
void select_players_numerical(Player<char>** players,Board<char>* board,string playersNames[2],int playersTypes[2]){
    Numerical_X_O_board<char> *numerical_board = dynamic_cast<Numerical_X_O_board<char> *>(board);
    for (int i = 0; i < 2; ++i) {
        switch(playersTypes[i]) {
            case 1: {
                players[i] = new Numerical_X_O_player<char>(playersNames[i],i+1);
                Numerical_X_O_player<char> *numericalPlayer = dynamic_cast<Numerical_X_O_player<char> *>(players[i]);

                if (numericalPlayer) {
                    numerical_board->numbers_pool[i] = &numericalPlayer[0].numbers_pool;
                }
                break;
            }
            case 2: {
                players[i] = new Numerical_X_O_Random_Player<char>(i+1);
                Numerical_X_O_Random_Player<char> *numericalPlayer = dynamic_cast<Numerical_X_O_Random_Player<char> *>(players[i]);

                if (numericalPlayer) {
                    numerical_board->numbers_pool[i] = &numericalPlayer[0].numbers_pool;
                }
                break;
            }
        }
    }
}
int main() {
    srand(time(0));
    int choice;
    Player<char>* players[2] = {nullptr, nullptr};
    Board<char>* board = nullptr;


    cout << "Welcome to FCAI X-O Game. :)\n";

    while (true) {
        displayMenu();
        while (true) {
            cout << "Enter your choice (0 to " << 8 << "): ";
            cin >> choice;

            if (choice >= 0 && choice <= 8) {
                break;
            } else {
                cout << "Invalid choice. Please enter a number between " << 0 << " and " << 8 << ".\n";
            }
        }
        // Set up players
        string player1Name, player2Name;
        int player1Type, player2Type;

        cout << "Enter Player 1 name: ";
        cin >> player1Name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n2. Random Computer\n";
        player1Type = getChoice(2);

        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n2. Random Computer\n";
        player2Type = getChoice(2);
        string playersNames[2] = {player1Name, player2Name};
        int playersTypes[2] = {player1Type, player2Type};

        switch (choice) {
            case 1:
                board = new Board_Pyramid<char>();
                for (int i = 0; i < 2; ++i) {
                    switch(playersTypes[i]) {
                        case 1: {
                            players[i] = new Player_Pyramid<char>(playersNames[i],(i ? 'B' : 'A'));
                            break;
                        }
                        case 2: {
                            players[i] = new RandomPlayer_Pyramid<char>((i ? 'B' : 'A'));
                            break;
                        }
                    }
                }
                break;
            case 2:
                board = new Connect4_board<char>();
                for (int i = 0; i < 2; ++i) {
                    switch(playersTypes[i]) {
                        case 1: {
                            players[i] = new Connect4_Player<char>(playersNames[i],(i ? 'X' : 'O'));
                            break;
                        }
                        case 2: {
                            players[i] = new Connect4_Random_Player<char>(6,7,(i ? 'X' : 'O'));
                            break;
                        }
                    }
                }
                break;
            case 3:
                board = new TicTacToe5x5Board<char>();
                for (int i = 0; i < 2; ++i) {
                    switch(playersTypes[i]) {
                        case 1: {
                            players[i] = new TicTacToePlayer<char>(playersNames[i],(i ? 'X' : 'O'));
                            break;
                        }
                        case 2: {
                            players[i] = new TicTacToeRandomPlayer<char>((i ? 'X' : 'O'));
                            break;
                        }
                    }
                }
                break;
            case 4:
                board = new Board_Word<char>();
                for (int i = 0; i < 2; ++i) {
                    switch(playersTypes[i]) {
                        case 1: {
                            players[i] = new Player_Word<char>(playersNames[i],(i ? 'B' : 'A'));
                            break;
                        }
                        case 2: {
                            players[i] = new RandomPlayer_Word<char>(playersNames[i],(i ? 'B' : 'A'));
                            break;
                        }
                    }
                }
                break;
            case 5: {
                board = new Numerical_X_O_board<char>();

                select_players_numerical(players,board, playersNames,playersTypes);
                break;
            }
            case 6:
            {
                board = new MisereX_O_Board<char>();
                swap(player1Name, player2Name);
                static_cast<MisereX_O_Player<char>*>(players[0])->setName(player1Name);
                static_cast<MisereX_O_Player<char>*>(players[1])->setName(player2Name);
                string playersNames[2] = {player1Name, player2Name};
                int playersTypes[2] = {player1Type, player2Type};
                for (int i = 0; i < 2; ++i) {
                    switch(playersTypes[i]) {
                        case 1: {
                            players[i] = new MisereX_O_Player<char>(playersNames[i],(i ? 'X' : 'O'));
                            break;
                        }
                        case 2: {
                            players[i] = new MisereX_O_Random_Player<char>((i ? 'X' : 'O'));
                            break;
                        }
                    }
                }
                break;
            }
            case 7:
                board = new Board4_4<char>();
                for (int i = 0; i < 2; ++i) {
                    switch(playersTypes[i]) {
                        case 1: {
                            players[i] = new Player4_4<char>(playersNames[i],(i ? 'X' : 'O'));
                            break;
                        }
                        case 2: {
                            players[i] = new RandomPlayer4_4<char>(playersNames[i],(i ? 'X' : 'O'));
                            break;
                        }
                    }
                }
                break;
            case 8:
                board = new XO9x9_Board<char>();
                for (int i = 0; i < 2; ++i) {
                    switch(playersTypes[i]) {
                        case 1: {
                            players[i] = new XO9x9_Player<char>(playersNames[i],(i ? 'X' : 'O'));
                            break;
                        }
                        case 2: {
                            players[i] = new XO9x9_Random_Player<char>((i ? 'X' : 'O'));
                            break;
                        }
                    }
                }
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                continue;
        }

        // Check if setup was successful
        if (!board || !players[0] || !players[1]) {
            cout << "Game setup failed. Restarting menu...\n";
            delete board;
            delete players[0];
            delete players[1];
            continue;
        }

        // Run the selected game
        GameManager<char> game(board, players);
        game.run();

        if(choice == 3){
            TicTacToe5x5Board<char> *board_5_5 = dynamic_cast<TicTacToe5x5Board<char> *>(board);
            // Display final scores
            auto scores = board_5_5->get_scores();
            cout << "Final Scores:\n";
            cout << player1Name << " (X): " << scores.first << "\n";
            cout << player2Name << " (O): " << scores.second << "\n";

            if (scores.first > scores.second) {
                cout << player1Name << " wins!\n";
            } else if (scores.second > scores.first) {
                cout << player2Name << " wins!\n";
            } else {
                cout << "It's a draw!\n";
            }
        }

        // Clean up
        delete board;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
    }
    return 0;
}