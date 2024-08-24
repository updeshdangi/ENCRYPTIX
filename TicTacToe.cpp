#include <iostream>
#include <vector>
#include <limits>
using namespace std;
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = ' ';

class TicTacToe 
{
private:
    vector<vector<char>> board;
    char currentPlayer;
    char opponent;

public:
    TicTacToe() : board(3, vector<char>(3, EMPTY)), currentPlayer(PLAYER_X), opponent(PLAYER_O) {}

    void printBoard() const
     {
        cout << "  0 1 2\n";
        for (int i = 0; i < 3; ++i)
         {
            cout << i << " ";
            for (int j = 0; j < 3; ++j) 
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isBoardFull() const
    {
        for (const auto& row : board) 
        {
            for (char cell : row) {
                if (cell == EMPTY) return false;
            }
        }
        return true;
    }

    bool checkWin(char player) const 
    {
        // Check rows, columns, and diagonals
        for (int i = 0; i < 3; ++i) 
        {
            if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
                (board[0][i] == player && board[1][i] == player && board[2][i] == player)) 
            {
                return true;
            }
        }
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
            (board[0][2] == player && board[1][1] == player && board[2][0] == player)) 
        {
            return true;
        }
        return false;
    }

    int evaluateBoard() const 
    {
        if (checkWin(PLAYER_X)) return 10;
        if (checkWin(PLAYER_O)) return -10;
        return 0;
    }

    int minimax(int depth, bool isMaximizing) 
    {
        int score = evaluateBoard();

        if (score == 10) return score - depth;
        if (score == -10) return score + depth;
        if (isBoardFull()) return 0;

        if (isMaximizing) 
        {
            int best = numeric_limits<int>::min();
            for (int i = 0; i < 3; ++i) 
            {
                for (int j = 0; j < 3; ++j) 
                {
                    if (board[i][j] == EMPTY) 
                    {
                        board[i][j] = PLAYER_X;
                        best = max(best, minimax(depth + 1, false));
                        board[i][j] = EMPTY;
                    }
                }
            }
            return best;
        } else {
            int best = numeric_limits<int>::max();
            for (int i = 0; i < 3; ++i) 
            {
                for (int j = 0; j < 3; ++j) 
                {
                    if (board[i][j] == EMPTY) 
                    {
                        board[i][j] = PLAYER_O;
                        best = min(best, minimax(depth + 1, true));
                        board[i][j] = EMPTY;
                    }
                }
            }
            return best;
        }
    }

    pair<int, int> findBestMove() 
    {
        int bestVal = numeric_limits<int>::min();
        pair<int, int> bestMove = {-1, -1};

        for (int i = 0; i < 3; ++i) 
        {
            for (int j = 0; j < 3; ++j) 
            {
                if (board[i][j] == EMPTY) 
                {
                    board[i][j] = PLAYER_X;
                    int moveVal = minimax(0, false);
                    board[i][j] = EMPTY;
                    if (moveVal > bestVal) 
                    {
                        bestMove = {i, j};
                        bestVal = moveVal;
                    }
                }
            }
        }
        return bestMove;
    }

    void makeMove(int x, int y, char player) 
    {
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == EMPTY) 
        {
            board[x][y] = player;
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
            opponent = (opponent == PLAYER_X) ? PLAYER_O : PLAYER_X;
        }
    }

    void playGame() 
    {
        while (true) 
        {
            printBoard();
            if (isBoardFull() || checkWin(PLAYER_X) || checkWin(PLAYER_O)) break;

            if (currentPlayer == PLAYER_X) 
            {
                cout << "Enter move for X (row and column): ";
                int x, y;
                cin >> x >> y;
                makeMove(x, y, PLAYER_X);
            } else 
             {
                cout << "AI is making a move...\n";
                pair<int, int> move = findBestMove();
                makeMove(move.first, move.second, PLAYER_O);
                cout << "AI chose: " << move.first << " " << move.second << endl;
             }
        }

        printBoard();
        if (checkWin(PLAYER_X)) cout << "Player X wins!" << endl;
        else if (checkWin(PLAYER_O)) cout << "Player O wins!" << endl;
        else cout << "It's a draw!" << endl;
    }
};

int main() 
{
    TicTacToe game;
    game.playGame();
    return 0;
}
