#ifndef _MINMAXPLAYER_H
#define _MINMAXPLAYER_H

#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm>
using namespace std;

template <typename T>
class X_O_MinMax_Player : public Player<T> {
public:
    X_O_MinMax_Player(T symbol, Board<T>* board);  // Pass board pointer to constructor

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing, int depth);
    pair<int, int> getBestMove();
};

template <typename T>
X_O_MinMax_Player<T>::X_O_MinMax_Player(T symbol, Board<T>* board) : Player<T>(symbol) {
    this->boardPtr = board;  // Initialize boardPtr with the passed board pointer
    this->name = "AI Player";
}

template <typename T>
void X_O_MinMax_Player<T>::getmove(int& x, int& y) {
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

template <typename T>
int X_O_MinMax_Player<T>::calculateMinMax(T s, bool isMaximizing, int depth) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -10 + depth : 10 - depth; // Depth-based scoring
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing, depth + 1);
                this->boardPtr->update_board(i, j, 0);

                bestValue = isMaximizing ? max(bestValue, value) : min(bestValue, value);
            }
        }
    }

    return bestValue;
}

template <typename T>
pair<int, int> X_O_MinMax_Player<T>::getBestMove() {
    int bestValue = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false, 0);
                this->boardPtr->update_board(i, j, 0);

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}

#endif //_MINMAXPLAYER_H
