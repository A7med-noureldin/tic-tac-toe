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

    const T* get_board_row(int row) const {
        // Ensure `row` is within valid range
        if (row < 0 || row >= this->rows) {
            cerr << "Row index out of bounds: " << row << endl;
            throw std::out_of_range("Row index out of bounds");
        }
        return this->board[row];  // Access the board directly (no cast needed)
    }

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

struct Node {
    vector<shared_ptr<Node>> children;
    int visits = 0;
    double reward = 0;
    int move;  // The column or move that was made to reach this node
    Node* parent = nullptr;
    vector<vector<char>> board_state;  // Store the board state at this node

    // Constructor to initialize the node
    Node(int move, const vector<vector<char>>& board_state, Node* parent = nullptr)
            : move(move), board_state(board_state), parent(parent) {}
};


// Select the best child using UCT
shared_ptr<Node> select_best_child(const shared_ptr<Node>& node) {
    double best_value = -numeric_limits<double>::infinity();
    shared_ptr<Node> best_child;
    for (const auto& child : node->children) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                cout << "| " << (child->board_state[i][j] ? child->board_state[i][j] : ' ') << " ";
            }
            cout << "|\n";
        }
        for (int j = 0; j < 7; j++) {
            cout << "----";
        }
        cout << "-\n";
        double uct_value = child->reward / (child->visits + 1e-5) +
                           sqrt(2 * log(node->visits + 1) / (child->visits + 1e-5));
        if (uct_value > best_value) {
            best_value = uct_value;
            best_child = child;
        }
    }
    return best_child;
}

void expand_node(shared_ptr<Node>& node, const vector<int>& valid_moves) {
    for (int move : valid_moves) {
        // Create a new board state after the move
        vector<vector<char>> new_board_state = node->board_state;  // Copy the current board state
        int row = 5;
        while (new_board_state[row][move] != 0 && row > 0) {  // Find the next empty row in the column
            row--;
        }
        new_board_state[row][move] = 'X';  // Assuming 'X' is the current player (this could vary)

        // Create a new child node with the updated board state
        node->children.push_back(make_shared<Node>(move, new_board_state, node.get()));
    }
}

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

template <typename T>
int simulate_game(vector<vector<char>>& board, char player_symbol) {
    random_device rd;
    mt19937 generator(rd());  // More robust random number generator

    while (true) {
        vector<int> valid_moves;
        for (int col = 0; col < 7; ++col) {
            if (board[0][col] == 0) {  // Check top row for empty column
                valid_moves.push_back(col);
            }
        }

        if (valid_moves.empty()) {
            return 0;  // Draw if no valid moves
        }

        // Use uniform distribution over valid moves
        uniform_int_distribution<int> distribution(0, valid_moves.size() - 1);
        int random_index = distribution(generator);
        int move = valid_moves[random_index];

        // Find the lowest empty row in the selected column
        int row = 5;
        while (row >= 0 && board[row][move] != 0) {
            row--;
        }

        // Sanity check to prevent out-of-bounds access
        if (row < 0) {
            continue;  // Skip this iteration if column is full
        }

        board[row][move] = player_symbol;

        // Check if the current player has won
        if (is_win<T>(board)) {
            return (player_symbol == 'X') ? 1 : -1;  // Return +1 for 'X', -1 for 'O'
        }

        // Switch players
        player_symbol = (player_symbol == 'X') ? 'O' : 'X';
    }
}

void backpropagate(shared_ptr<Node>& node, int result) {
    Node* current = node.get();
    while (current != nullptr) {
        current->visits++;
        current->reward += result;
        current = current->parent;
    }
}
template <typename T>
class Connect4_MCTSPlayer : public Player<T> {
public:
    Connect4_MCTSPlayer(T symbol) : Player<T>(symbol) {}
    vector<vector<T>> get_board_state() {
        vector<vector<T>> board_copy(6, vector<T>(7, 0));  // Assuming 6 rows, 7 columns
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                board_copy[i][j] = get_board_row(i)[j];  // Copy from the actual board
            }
        }
        return board_copy;
    }

    void getmove(int& x, int& y) override {
        shared_ptr<Node> root = make_shared<Node>(-1, get_board_state(), nullptr);

        expand_node(root, get_valid_moves());

        int iterations = 1000;  // Number of MCTS iterations
        for (int i = 0; i < iterations; ++i) {
            shared_ptr<Node> node = root;

            // Selection
            while (!node->children.empty()) {
                node = select_best_child(node);
            }

            // Expansion
            expand_node(node, get_valid_moves());

            // Simulation
            vector<vector<char>> board = copy_board_state();
            int result = simulate_game<T>(board, this->symbol);

            // Backpropagation
            backpropagate(node, result);
        }

        // Choose the best move from the root's children
        auto best_child = select_best_child(root);
        y = best_child->move;
        x = 5;
        while (x >= 0 && get_board_row(x)[y] != 0) {  // Ensure x is within bounds
            x--;
        }
    }

private:
    vector<int> get_valid_moves() {

        // Ensure the dynamic cast is successful
        auto board = dynamic_cast<Connect4_board<T>*>(this->boardPtr);
        if (!board) {
            cerr << "Dynamic cast failed in get_valid_moves!" << endl;
            throw std::runtime_error("Invalid board pointer.");
        }

        vector<int> valid_moves;
        // Loop through the columns and find empty spaces
        for (int col = 0; col < 7; ++col) {
            if (board->get_board_row(0)[col] == 0) {  // 0 indicates empty space
                valid_moves.push_back(col);
            }
        }

        if (valid_moves.empty()) {
            cerr << "No valid moves found!" << endl;
        }

        return valid_moves;
    }




    vector<vector<char>> copy_board_state() {
        vector<vector<char>> board_copy(6, vector<char>(7, ' '));
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                board_copy[i][j] = get_board_row(i)[j];
            }
        }
        return board_copy;
    }

    const T* get_board_row(int row) const {
        return dynamic_cast<Connect4_board<T>*>(this->boardPtr)->get_board_row(row);
    }
};

#endif // TIC_TAC_TOE_CONNECT4_H
