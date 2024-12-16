#ifndef GAMETEST_TICTACTOE_PROB7_H
#define GAMETEST_TICTACTOE_PROB7_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Board4_4: public Board<T> {
public:
    Board4_4();
    ~Board4_4();
    void display_board ();
    bool update_board (int n , int m , T symbol);
    bool is_draw();
    bool is_win();
    bool game_is_over();
};

template <typename T>
Board4_4<T>::~Board4_4() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];  // Clean up each row
    }
    delete[] this->board;  // Clean up the main board
}

template <typename T>
class Player4_4: public Player<T>{
public:
    Player4_4 (string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class RandomPlayer4_4 : public RandomPlayer<T>{
public:
    RandomPlayer4_4 (string name,T symbol);
    void getmove(int &x, int &y);
};

///////--------------------------------Implementation---------------------------------------///////
///////----------------------Board Implementation----------------------///////

bool comp = false;

template<typename T>
Board4_4<T>::Board4_4() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    // Initialize 1st Row
    this->board[0][0] = 'O', this->board[0][1] = 'X', this->board[0][2] = 'O', this->board[0][3] = 'X';
    // Initialize last Row
    this->board[3][0] = 'X', this->board[3][1] = 'O', this->board[3][2] = 'X', this->board[3][3] = 'O';
}

template<typename T>
bool Board4_4<T>::update_board(int n, int m, T symbol) {
    int x, y;
    if(this->board[n][m] == 'X' || this->board[n][m] == 'O'){
        if(this->board[n][m] != symbol && !comp){
            cout << "\nPlease choose the cell that contain " << symbol << " symbol!\n";
            return false;
        }
        else if(this->board[n][m] != symbol){
            return false;
        }

        char c = this->board[n][m];
        this->board[n][m] = 0;

        if(comp){
            x = rand() % 4;
            y = rand() % 4;
        }
        else {
            cout << "\nPlease enter the position you want to move to: ";
            cin >> x >> y;
        }

        while(this->board[x][y] != 0 || (x < 0 || x >= this->rows || y < 0 || y >= this->columns) ||
        !(n == x && abs(m-y) == 1 || m == y && abs(x-n) == 1) || (x == y && n == m && abs(n-x) == 1)){
            if(comp){
                x = rand() % 4;
                y = rand() % 4;
            }
            else {
                cout << "\nPlease enter valid position you want to move to: ";
                cin >> x >> y;
            }
        }
        comp = false;
        this->board[x][y] = c;
        return true;
    }
    return false;
}

template<typename T>
void Board4_4<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
    }
    cout << endl;
}

template<typename T>
bool Board4_4<T>::is_draw() {
    return false;
}

template<typename T>
bool Board4_4<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0) ||
            (this->board[i][1] == this->board[i][2] && this->board[i][1] == this->board[i][3] && this->board[i][1] != 0) ||
            (this->board[1][i] == this->board[2][i] && this->board[1][i] == this->board[3][i] && this->board[1][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0) ||
        (this->board[1][1] == this->board[2][2] && this->board[1][1] == this->board[3][3] && this->board[1][1] != 0) ||
        (this->board[0][1] == this->board[1][2] && this->board[0][1] == this->board[2][3] && this->board[0][1] != 0) ||
        (this->board[1][0] == this->board[2][1] && this->board[1][0] == this->board[3][2] && this->board[1][0] != 0) ||
        (this->board[0][3] == this->board[1][2] && this->board[1][2] == this->board[2][1] && this->board[0][3] != 0) ||
        (this->board[3][0] == this->board[1][2] && this->board[1][2] == this->board[2][1] && this->board[3][0] != 0) ||
        (this->board[1][3] == this->board[2][2] && this->board[1][3] == this->board[3][1] && this->board[1][3] != 0)) {
        return true;
    }
    return false;
}

template<typename T>
bool Board4_4<T>::game_is_over() {
    return is_win();
}

///////----------------------Player Implementation----------------------///////

template<typename T>
Player4_4<T>::Player4_4(string name, T symbol):Player<T>(name, symbol) {}

template<typename T>
void Player4_4<T>::getmove(int &n, int &m) {
    cout << "\nPlease enter valid position you want to move from: ";
    cin >> n >> m;
}

///////----------------------Random Player Implementation----------------------///////

template<typename T>
RandomPlayer4_4<T>::RandomPlayer4_4(string name, T symbol):RandomPlayer<T>(symbol) {
    this->name = name;
    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void RandomPlayer4_4<T>::getmove(int &x, int &y) {
    x = rand() % 4;  //Rows = 4
    y = rand() % 4; // Columns = 4
    comp = true;
}

#endif //GAMETEST_TICTACTOE_PROB7_H
