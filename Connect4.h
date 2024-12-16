#ifndef TIC_TAC_TOE_CONNECT4_H
#define TIC_TAC_TOE_CONNECT4_H
#include <memory>
#include "BoardGame_Classes.h"
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>
#include <cmath>
#include <random>
#include <limits>
#include <cctype>
#include <cmath>
template <typename T>
class Connect4_board : public Board<T> {
public:
    Connect4_board();
    ~Connect4_board();  // Destructor to clean up memory

    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool check_direction(int x, int y, int dx, int dy, T symbol);
};



template <typename T>
class Connect4_Player : public Player<T> {
public:
    Connect4_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class Connect4_Random_Player : public RandomPlayer<T> {
public:
    Connect4_Random_Player(int rows, int cols, T symbol);
    void getmove(int& x, int& y) override;

private:
    int rows, cols;
};

// Implementation of Connect4_board
template <typename T>
Connect4_board<T>::Connect4_board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
Connect4_board<T>::~Connect4_board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];  // Clean up each row
    }
    delete[] this->board;  // Clean up the main board
}

template <typename T>
bool Connect4_board<T>::update_board(int x, int y, T symbol) {
    if (y < 0 || y >= this->columns || symbol == 0) {
        if (symbol == 0){
            this->n_moves--;
            if(x >= 0 && x < this->rows && y >= 0 && y < this->columns)  // Ensure indices are within bounds
                this->board[x][y] = 0;
        }
        return false;
    }
    for (int i = this->rows - 1; i >= 0; i--) {
        if (this->board[i][y] == 0) {  // Ensure correct indexing
            this->board[i][y] = toupper(symbol);
            this->n_moves++;
            return true;
        }
    }
    return false;  // Column is full
}


template <typename T>
void Connect4_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            cout << "| " << (this->board[i][j] ? this->board[i][j] : ' ') << " ";
        }
        cout << "|\n";
    }
    for (int j = 0; j < this->columns; j++) {
        cout << "----";
    }
    cout << "-\n";
}
template <typename T>
bool Connect4_board<T>::check_direction(int x, int y, int dx, int dy, T symbol) {
    int count = 1;

    // Check in the positive direction
    for (int i = x + dx, j = y + dy;
         i >= 0 && i < this->rows && j >= 0 && j < this->columns;
         i += dx, j += dy) {
        if (this->board[i][j] != symbol) break;
        count++;
    }

    // Check in the negative direction
    for (int i = x - dx, j = y - dy;
         i >= 0 && i < this->rows && j >= 0 && j < this->columns;
         i -= dx, j -= dy) {
        if (this->board[i][j] != symbol) break;
        count++;
    }

    return count >= 4;
}

template <typename T>
bool Connect4_board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0) {
                T symbol = this->board[i][j];

                // Check horizontal, vertical, and both diagonals
                if (check_direction(i, j, 0, 1, symbol) ||   // Horizontal
                    check_direction(i, j, 1, 0, symbol) ||   // Vertical
                    check_direction(i, j, 1, 1, symbol) ||   // Primary diagonal
                    check_direction(i, j, 1, -1, symbol)) {  // Secondary diagonal
                    return true;
                }
            }
        }
    }
    return false;
}


template <typename T>
bool Connect4_board<T>::is_draw() {
    return this->n_moves == this->rows * this->columns && !this->is_win();
}

template <typename T>
bool Connect4_board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
Connect4_Player<T>::Connect4_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Connect4_Player<T>::getmove(int& x, int& y) {
    cout << "Enter column (0 to " << 7 - 1 << "): ";
    cin >> y;
    x = -1;  // x is not used since the board determines row
}


// Implementation of Connect4_Random_Player
template <typename T>
Connect4_Random_Player<T>::Connect4_Random_Player(int rows, int cols, T symbol) : RandomPlayer<T>(symbol), rows(rows), cols(cols) {}

template <typename T>
void Connect4_Random_Player<T>::getmove(int& x, int& y) {
    y = rand() % cols;
    x = -1;  // x is not used
}

#include <vector>
#include <memory>
#include <cmath>
#include <random>
#include <limits>


template <typename T>
bool check_direction(vector<vector<char>>& board,int x, int y, int dx, int dy, T symbol) {
    int count = 1;

    // Check in the positive direction
    for (int i = x + dx, j = y + dy;
         i >= 0 && i < 6 && j >= 0 && j < 7;
         i += dx, j += dy) {
        if (board[i][j] != symbol) break;
        count++;
    }

    // Check in the negative direction
    for (int i = x - dx, j = y - dy;
         i >= 0 && i < 6 && j >= 0 && j < 7;
         i -= dx, j -= dy) {
        if (board[i][j] != symbol) break;
        count++;
    }

    return count >= 4;
}

template <typename T>
bool is_win(vector<vector<char>>& board) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] != 0) {
                T symbol = board[i][j];

                // Check horizontal, vertical, and both diagonals
                if (check_direction<T>(board,i, j, 0, 1, symbol) ||   // Horizontal
                    check_direction<T>(board,i, j, 1, 0, symbol) ||   // Vertical
                    check_direction<T>(board,i, j, 1, 1, symbol) ||   // Primary diagonal
                    check_direction<T>(board,i, j, 1, -1, symbol)) {  // Secondary diagonal
                    return true;
                }
            }
        }
    }
    return false;
}


#endif // TIC_TAC_TOE_CONNECT4_H
