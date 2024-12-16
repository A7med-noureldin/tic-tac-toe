#ifndef _MISEREX_O_GAME_H
#define _MISEREX_O_GAME_H

#include "BoardGame_Classes.h"

template <typename T>
class MisereX_O_Board : public Board<T> {
public:
    MisereX_O_Board();
    ~MisereX_O_Board();
    bool update_board(int row, int col, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
MisereX_O_Board<T>::~MisereX_O_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];  // Clean up each row
    }
    delete[] this->board;  // Clean up the main board
}

template <typename T>
class MisereX_O_Player : public Player<T> {
public:
    MisereX_O_Player(string player_name, T symbol);
    void getmove(int& row, int& col);

    // Getter for player name (moved to implementation)
    string getName() const;

    // Setter for player name (moved to implementation)
    void setName(const string& new_name);
};

template <typename T>
class MisereX_O_Random_Player : public RandomPlayer<T> {
public:
    MisereX_O_Random_Player(T symbol);
    void getmove(int& row, int& col);
};

// --------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for MisereX_O_Board
template <typename T>
MisereX_O_Board<T>::MisereX_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool MisereX_O_Board<T>::update_board(int row, int col, T mark) {
    // Only update if move is valid
    if (!(row < 0 || row >= this->rows || col < 0 || col >= this->columns) && (this->board[row][col] == 0 || mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[row][col] = 0;
        }
        else {
            this->n_moves++;
            this->board[row][col] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void MisereX_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool MisereX_O_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
       if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
        return true ;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true ;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool MisereX_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool MisereX_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// --------------------------------------

// Constructor for MisereX_O_Player
template <typename T>
MisereX_O_Player<T>::MisereX_O_Player(string player_name, T symbol) : Player<T>(player_name, symbol) {}

template <typename T>
void MisereX_O_Player<T>::getmove(int& row, int& col) {
    cout << "\nPlease enter your move row and col (0 to 2) separated by spaces: ";
    cin >> row >> col;
}

// Getter for player name (now in implementation)
template <typename T>
string MisereX_O_Player<T>::getName() const {
    return this->name;
}

// Setter for player name (now in implementation)
template <typename T>
void MisereX_O_Player<T>::setName(const string& new_name) {
    this->name = new_name;
}

// Constructor for MisereX_O_Random_Player
template <typename T>
MisereX_O_Random_Player<T>::MisereX_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void MisereX_O_Random_Player<T>::getmove(int& row, int& col) {
    row = rand() % this->dimension;  // Random number between 0 and 2
    col = rand() % this->dimension;
}

#endif //_MISEREX_O_GAME_H
