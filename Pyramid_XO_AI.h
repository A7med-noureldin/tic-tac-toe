#ifndef GAMETEST_PYRAMID_XO_AI_H
#define GAMETEST_PYRAMID_XO_AI_H

#include "BoardGame_Classes.h"

template <typename T>
class PyramidAI : public Player<T> {
private:
    int calculateMinMax(T s, bool isMaximizing);
    pair<int, int> getBestMove();

public:
    PyramidAI(string k, T symbol);
    void getmove(int& x, int& y) override;
};

///////--------------------------------Implementation---------------------------------------///////

#include <bits/stdc++.h>

using namespace std;

set<pair<int,int>> invalidPos = {{0,0}, {0,1}, {0,3}, {0,4}, {1,0}, {1,4}}; // Invalid positions

template<typename T>
PyramidAI<T>::PyramidAI(string k, T symbol):Player<T>(symbol) {
    this->name = k;
}

template <typename T>
void PyramidAI<T>::getmove(int& x, int& y) {
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

template <typename T>
int PyramidAI<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(invalidPos.count(make_pair(i,j))){
                continue;
            }
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0);

                if (isMaximizing) {
                    bestValue = max(bestValue, value);
                }
                else {
                    bestValue = min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

template <typename T>
pair<int, int> PyramidAI<T>::getBestMove() {
    int bestValue = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    // First, check if we can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(invalidPos.count(make_pair(i,j))){
                continue;
            }
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    return {i, j}; // Winning move found
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
            }
        }
    }

    // Second, check if the opponent can win in their next move and block them
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(invalidPos.count(make_pair(i,j))){
                continue;
            }
            if (this->boardPtr->update_board(i, j, opponentSymbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    return {i, j}; // Block opponent's winning move
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
            }
        }
    }

    // If no immediate win or block, use MinMax to find the best move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(invalidPos.count(make_pair(i,j))){
                continue;
            }
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }
    return bestMove;
}



#endif //GAMETEST_PYRAMID_XO_AI_H