#ifndef GAMETEST_PYRAMID_XO_H
#define GAMETEST_PYRAMID_XO_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Board_XO: public Board<T> {
public:
    Board_XO();
    bool update_board (int x , int y , T symbol);
    void display_board ();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Player_XO: public Player<T>{
public:
    Player_XO (string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class RandomPlayer_XO : public RandomPlayer<T>{
public:
    RandomPlayer_XO (string name,T symbol);
    void getmove(int &x, int &y);
};


///////--------------------------------Implementation---------------------------------------///////
///////----------------------Board Implementation----------------------///////
template<typename T>
Board_XO<T>::Board_XO() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

set<pair<int,int>> s = {{0,0}, {0,1}, {0,3}, {0,4}, {1,0}, {1,4}}; // Invalid positions

template<typename T>
bool Board_XO<T>::update_board(int x, int y, T symbol) {
    if(!(x < 0 || x >= this->rows || y < 0 || y >= this->columns || s.count(make_pair(x, y))) && (this->board[x][y] == 0 || symbol == 0)){
        if (symbol == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }
        return true;
    }
    return false;
}

template<typename T>
void Board_XO<T>::display_board() {
    bool good = true;
    cout << endl << setw(19);
    for (int i = 0; i < 3; i++) {
        if (i == 1)
            cout << setw(10);
        for (int j = 0; j < 5; j++) {
            if(s.count(make_pair(i,j)))continue;
            if(good){
                cout << "|";
                good = !good;
            }
            cout << '(' << i << ',' << j << ')' << setw(3) << this->board[i][j] << "|";
        }
        good = !good;
        cout << endl;
    }
    cout << "----------------------------------------------------\n";
}

template<typename T>
bool Board_XO<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool Board_XO<T>::is_win() {
    //check Rows
    if(this->board[1][1] == this->board[1][2] && this->board[1][1] == this->board[1][3] && this->board[1][1] != 0){
        return true;
    }

    if(this->board[2][0] == this->board[2][1] && this->board[2][0] == this->board[2][2] && this->board[2][0] != 0){
        return true;
    }

    if(this->board[2][1] == this->board[2][2] && this->board[2][1] == this->board[2][3] && this->board[2][1] != 0){
        return true;
    }

    if(this->board[2][2] == this->board[2][3] && this->board[2][2] == this->board[2][4] && this->board[2][2] != 0){
        return true;
    }

    //check Column
    if(this->board[2][2] == this->board[0][2] && this->board[2][2] == this->board[1][2] && this->board[2][2] != 0){
        return true;
    }

    //check Diagonals
    if(this->board[0][2] == this->board[1][3] && this->board[0][2] == this->board[2][4] && this->board[0][2] != 0){
        return true;
    }

    if(this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0] && this->board[0][2] != 0){
        return true;
    }

    return false;
}

template<typename T>
bool Board_XO<T>::game_is_over() {
    return (is_win() || is_draw());
}

///////----------------------Player Implementation----------------------///////

template<typename T>
Player_XO<T>::Player_XO(string name, T symbol):Player<T>(name, symbol) {}

template<typename T>
void Player_XO<T>::getmove(int &x, int &y) {
    cout << "\nPlease enter your move x (0 to 2) and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

///////----------------------Random Player Implementation----------------------///////

template<typename T>
RandomPlayer_XO<T>::RandomPlayer_XO(string s, T symbol):RandomPlayer<T>(symbol) {
    this->name = s;
    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void RandomPlayer_XO<T>::getmove(int &x, int &y) {
    x = rand() % 3;  //Rows = 3
    y = rand() % 5; // Columns = 5
}

#endif //GAMETEST_PYRAMID_XO_H