#ifndef TIC_TAC_TOE_G9X9_X_O_H
#define TIC_TAC_TOE_G9X9_X_O_H

#include "BoardGame_Classes.h"

template <typename T>
class X_O_Board:public Board<T> {
public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    T get_cell(int row, int col) const;
};
template <typename T>
T X_O_Board<T>::get_cell(int row, int col) const {
    if (row >= 0 && row < this->rows && col >= 0 && col < this->columns) {
        return this->board[row][col];
    }
    return 0;
}

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
using namespace std;

// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
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
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_Board<T>::display_board() {
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
bool X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
class XO9x9_Board:public Board<T> {
private:
    vector<vector<X_O_Board<T>>> sub_boards;
public:
    XO9x9_Board() {
        sub_boards.resize(3, vector<X_O_Board<T>>(3));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                sub_boards[i][j] = X_O_Board<T>(); // Create a new instance
            }
        }        this->rows = this->columns = 3;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }
    bool update_board (int x,int y, T symbol);
    void display_board ();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};
template <typename T>
bool XO9x9_Board<T>::update_board(int x, int y, T mark) {
    int a = x / 3,b = y / 3;
    x %= 3,y %= 3;
    if (!(a < 0 || a >= this->rows || b < 0 || b >= this->columns) && (this->board[a][b] == 0|| mark == 0)) {
        if (sub_boards[a][b].game_is_over()) {
            return false;
        }
        if (sub_boards[a][b].update_board(x, y, mark)) {
            if (sub_boards[a][b].is_win()) {
                this->board[a][b] = mark;
            }
            return true;
        }
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void XO9x9_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->rows; j++) {
            for (int k = 0; k < this->columns; ++k) {
                cout << "| ";
                for (int l = 0; l < this->columns; ++l) {
                    T symbol = sub_boards[i][k].get_cell(j, l);
                    cout << (symbol ? symbol : ' ') << " ";
                }
            }
            cout << '|' << endl;
        }
        cout << string(12 * 3, '-') << endl;
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool XO9x9_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool XO9x9_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool XO9x9_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
class XO9x9_Player : public Player<T> {
public:
    XO9x9_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

// Constructor for X_O_Player
template <typename T>
XO9x9_Player<T>::XO9x9_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void XO9x9_Player<T>::getmove(int& x, int& y) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "X (" << 3 * i << ',' << -1 + 3 * (i + 1) << ')' << " Y (" << 3 * j << ',' << -1 + 3 * (j + 1) << ')' << '|';
        }
        cout << endl;
    }
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}
template <typename T>
class XO9x9_Random_Player : public RandomPlayer<T>{
public:
    XO9x9_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
// Constructor for X_O_Random_Player
template <typename T>
XO9x9_Random_Player<T>::XO9x9_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void XO9x9_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 8
    y = rand() % this->dimension;
}


#endif //TIC_TAC_TOE_G9X9_X_O_H
