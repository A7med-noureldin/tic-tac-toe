#ifndef _5X5TICTACTOE_H
#define _5X5TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

template <typename T>
class TicTacToe5x5Board : public Board<T> {
private:
    int count_three_in_a_row(T symbol);

public:
    TicTacToe5x5Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    pair<int, int> get_scores();

template <typename T>
class TicTacToePlayer : public Player<T> {
public:
    TicTacToePlayer(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class TicTacToeRandomPlayer : public RandomPlayer<T> { //tmam
public:
    TicTacToeRandomPlayer(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION


template <typename T> //tmam
TicTacToe5x5Board<T>::TicTacToe5x5Board() {
    this->rows = this->columns = 5;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns]();
    }
    this->n_moves = 0;
}

template <typename T>
bool TicTacToe5x5Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void TicTacToe5x5Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << (this->board[i][j] == 0 ? ' ' : this->board[i][j]) << " |";
        }
        cout << "\n-----------------------------------------------";
    }
    cout << endl;
}

template <typename T>
int TicTacToe5x5Board<T>::count_three_in_a_row(T symbol) {
    int count = 0;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == symbol && this->board[i][j + 1] == symbol && this->board[i][j + 2] == symbol) {
                count++;
            }
            if (this->board[j][i] == symbol && this->board[j + 1][i] == symbol && this->board[j + 2][i] == symbol) {
                count++;
            }
        }
    }
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == symbol && this->board[i + 1][j + 1] == symbol && this->board[i + 2][j + 2] == symbol) {
                count++;
            }
            if (this->board[i][j + 2] == symbol && this->board[i + 1][j + 1] == symbol && this->board[i + 2][j] == symbol) {
                count++;
            }
        }
    }
    return count;
}

template <typename T>
bool TicTacToe5x5Board<T>::is_win() { /
    return false;
}

template <typename T>
bool TicTacToe5x5Board<T>::is_draw() {
    return false;
}

template <typename T>
bool TicTacToe5x5Board<T>::game_is_over() {
    return this->n_moves == 24;
}

template <typename T>
pair<int, int> TicTacToe5x5Board<T>::get_scores() {
    int x_score = count_three_in_a_row('X');
    int o_score = count_three_in_a_row('O');
    return {x_score, o_score};
}

// Constructor for human player
template <typename T>
TicTacToePlayer<T>::TicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void TicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move (row and column): ";
    cin >> x >> y;
}

// Constructor for random computer player
template <typename T>
TicTacToeRandomPlayer<T>::TicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));  // Seed for randomness
}

template <typename T>
void TicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 5;
    y = rand() % 5;
}

#endif //_5X5TICTACTOE_H

