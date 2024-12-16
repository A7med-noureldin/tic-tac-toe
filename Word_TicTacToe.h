#ifndef GAMETEST_WORD_TICTACTOE_H
#define GAMETEST_WORD_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Board_Word: public Board<T> {
public:
    Board_Word();
    ~Board_Word();
    bool update_board (int x , int y , T symbol);
    void display_board ();
    bool is_win();
    bool is_draw();
    void readDic();
    bool game_is_over();
};

template <typename T>
Board_Word<T>::~Board_Word() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];  // Clean up each row
    }
    delete[] this->board;  // Clean up the main board
}


template <typename T>
class Player_Word: public Player<T>{
public:
    Player_Word (string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class RandomPlayer_Word : public RandomPlayer<T>{
public:
    RandomPlayer_Word (string name, T symbol);
    void getmove(int &x, int &y);
};


///////--------------------------------Implementation---------------------------------------///////
///////----------------------Board Implementation----------------------///////
set<string> sett;

template<typename T>
Board_Word<T>::Board_Word() {
    this->rows = this->columns = 3;
    this->readDic();
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template<typename T>
bool Board_Word<T>::update_board(int x, int y, T symbol) {
    if(!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && this->board[x][y] == 0){
        this->n_moves++;
        this->board[x][y] = toupper(symbol);

        return true;
    }
    return false;
}

template<typename T>
void Board_Word<T>::display_board() {
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

template<typename T>
bool Board_Word<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
void Board_Word<T>::readDic() {
    cout << "\nstart read dic\n";
    ifstream InFile("dic.txt");

    if(!InFile.is_open()){
        cout << "there is a trouble in opening the file!\n";
        return;
    }

    string word;
    while(getline(InFile, word)){
        sett.insert(word);
    }

    InFile.close();
}

template<typename T>
bool Board_Word<T>::is_win() {
    //check Rows
    string word = string(1, this->board[0][0]) + this->board[0][1] + this->board[0][2];
    string word2 = word;
    reverse(word2.begin(), word2.end());

    if(sett.count(word) || sett.count(word2)){
        return true;
    }

    word = string(1, this->board[1][0]) + this->board[1][1] + this->board[1][2];
    word2 = word;
    reverse(word2.begin(), word2.end());

    if(sett.count(word) || sett.count(word2)){
        return true;
    }

    word = string(1, this->board[2][0])+ this->board[2][1] + this->board[2][2];
    word2 = word;
    reverse(word2.begin(), word2.end());
    if(sett.count(word) || sett.count(word2)){
        return true;
    }

    //check Column
    word = string(1, this->board[0][0]) + this->board[1][0] + this->board[2][0];
    word2 = word;
    reverse(word2.begin(), word2.end());
    if(sett.count(word) || sett.count(word2)){
        return true;
    }

    word = string(1, this->board[0][1]) + this->board[1][1] + this->board[2][1];
    word2 = word;
    reverse(word2.begin(), word2.end());
    if(sett.count(word) || sett.count(word2)){
        return true;
    }

    word = string(1, this->board[0][2]) + this->board[1][2] + this->board[2][2];
    word2 = word;
    reverse(word2.begin(), word2.end());
    if(sett.count(word) || sett.count(word2)){
        return true;
    }

    //check Diagonals
    word = string(1, this->board[0][0]) + this->board[1][1] + this->board[2][2];
    word2 = word;
    reverse(word2.begin(), word2.end());
    if(sett.count(word) || sett.count(word2)){
        return true;
    }

    word = string(1, this->board[0][2]) + this->board[1][1] + this->board[2][0];
    word2 = word;
    reverse(word2.begin(), word2.end());
    if(sett.count(word) || sett.count(word2)){
        return true;
    }

    return false;
}

template<typename T>
bool Board_Word<T>::game_is_over() {
    return (is_win() || is_draw());
}

///////----------------------Player Implementation----------------------///////
template<typename T>
Player_Word<T>::Player_Word(string name, T symbol):Player<T>(name, symbol) {}

template<typename T>
void Player_Word<T>::getmove(int &x, int &y) {
    cout << "\nPlease enter your move x (0 to 2) and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
    while (true) {
        char c;
        cout << "\nEnter your character (A-Z): ";
        cin >> c;
        if (isalpha(c)) {
            c = toupper(c);
            this->symbol = c;
            break;
        }
        cout << "Invalid character! Please try again.\n";
    }
}

///////----------------------Random Player Implementation----------------------///////

string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

template<typename T>
RandomPlayer_Word<T>::RandomPlayer_Word(string s, T symbol):RandomPlayer<T>(symbol) {
    this->name = s;
    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void RandomPlayer_Word<T>::getmove(int &x, int &y) {
    x = rand() % 3;  //Rows = 3
    y = rand() % 3; // Columns = 3
    int pos = rand() % 26;
    this->symbol = alpha[pos];
}

#endif //GAMETEST_WORD_TICTACTOE_H
