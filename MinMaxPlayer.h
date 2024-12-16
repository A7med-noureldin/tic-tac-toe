#ifndef _MINMAXPLAYER_H
#define _MINMAXPLAYER_H

#include "BoardGame_Classes.h"

template <typename T>
class X_O_MinMax_Player : public Player<T> {
public:
    X_O_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getWorstMove();
};

#include <limits>
#include <algorithm>
using namespace std;

template <typename T>
X_O_MinMax_Player<T>::X_O_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

template <typename T>
void X_O_MinMax_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> worstMove = getWorstMove();
    x = worstMove.first;
    y = worstMove.second;
}

template <typename T>
int X_O_MinMax_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0);

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                } else {
                    bestValue = std::min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

template <typename T>
std::pair<int, int> X_O_MinMax_Player<T>::getWorstMove() {
    int worstValue = std::numeric_limits<int>::max();
    std::pair<int, int> worstMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0);
                    continue;
                }
                this->boardPtr->update_board(i, j, 0);
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, opponentSymbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0);
                    continue;
                }
                this->boardPtr->update_board(i, j, 0);
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0);

                if (moveValue < worstValue) {
                    worstMove = {i, j};
                    worstValue = moveValue;
                }
            }
        }
    }

    return worstMove;
}

#endif //_MINMAXPLAYER_H
