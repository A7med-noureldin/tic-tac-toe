#ifndef TIC_TAC_TOE_NUMERICAL_X_O_H
#define TIC_TAC_TOE_NUMERICAL_X_O_H
#include "BoardGame_Classes.h"

template <typename T>
class Numerical_X_O_board:public Board<T> {
public:
    vector<int>* numbers_pool[2];
    Numerical_X_O_board ();
    ~Numerical_X_O_board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    T getCell(int x,int y){
        return this->board[x][y];
    }
};
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>
Numerical_X_O_board<T>::Numerical_X_O_board() {
    this->rows = this->columns = 3;
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
Numerical_X_O_board<T>::~Numerical_X_O_board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
bool Numerical_X_O_board<T>::update_board(int x, int y, T number) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| number == 0)) {
        if (number == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = number;
        }

        return true;
    }
    numbers_pool[(number%2 ? 0 : 1)]->push_back(number);
    return false;
}

template <typename T>
void Numerical_X_O_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << char(this->board[i][j] + '0') << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool Numerical_X_O_board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
            if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 &&
                    this->board[i][0] && this->board[i][1] && this->board[i][2]) ||
                (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15 &&
                        this->board[0][i] && this->board[1][i] && this->board[2][i])) {
                return true;
            }
    }

    // Check diagonals
    if(this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0){
        if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) ||
            (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15)) {
            return true;
        }
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Numerical_X_O_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Numerical_X_O_board<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
class Numerical_X_O_player : public Player<T> {
public:
    vector<int> numbers_pool;
    Numerical_X_O_player (string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Numerical_X_O_Random_Player : public RandomPlayer<T> {
public:
    T selectedNumber;
    vector<int> numbers_pool;
    Numerical_X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

// Constructor for Numerical_X_O_Random_Player
template <typename T>
Numerical_X_O_Random_Player<T>::Numerical_X_O_Random_Player(T symbol)
        : RandomPlayer<T>(symbol), selectedNumber(0) {
    for (int i = 1; i <= 9; ++i) {
        // Add only numbers matching the parity of the player's symbol
        if (symbol % 2 == i % 2) {
            numbers_pool.push_back(i);
        }
    }
}

// Generate random move and number
template <typename T>
void Numerical_X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % 3;

    int randomIndex = rand() % numbers_pool.size();
    selectedNumber = numbers_pool[randomIndex];

    this->symbol = selectedNumber;
    numbers_pool.erase(numbers_pool.begin() + randomIndex);
}

template <typename T>
Numerical_X_O_player<T>::Numerical_X_O_player(string name, T symbol) : Player<T>(name, symbol) {
    for (int i = 1; i <= 9; ++i) {
        if(symbol%2 == i%2){
            numbers_pool.push_back(i);
        }
    }
}

template <typename T>
void Numerical_X_O_player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;

    int selectedNumber;
    cout << "Available numbers to place: ";
    for (int num : numbers_pool) {
        cout << num << " ";
    }
    cout << "\nPlease select a number to place: ";
    cin >> selectedNumber;

    while (find(numbers_pool.begin(), numbers_pool.end(), selectedNumber) == numbers_pool.end()) {
        cout << "Invalid selection. Please select a number from the pool: ";
        cin >> selectedNumber;
    }

    this->symbol = selectedNumber;
    numbers_pool.erase(find(numbers_pool.begin(), numbers_pool.end(), selectedNumber));
}

#endif //TIC_TAC_TOE_NUMERICAL_X_O_H
