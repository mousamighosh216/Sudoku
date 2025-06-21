#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

bool check(vector<vector<char>> &board, int &r, int &c, char num)
{
    // upar niche
    for (int i = 0; i < 9; i++)
    {
        if (board[r][i] == num || board[i][c] == num)
            return false;
    }

    // 3*3 box
    int srt_r = r / 3 * 3, srt_c = c / 3 * 3;
    for (int i = srt_r; i < srt_r + 3; i++)
    {
        for (int j = srt_c; j < srt_c + 3; j++)
        {
            if (board[i][j] == num)
                return false;
        }
    }

    return true;
}

bool sudoku_sol(vector<vector<char>> &board)
{
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            if (board[r][c] == '.')
            {
                for (char num = '1'; num <= '9'; num++)
                {
                    if (check(board, r, c, num))
                    {
                        board[r][c] = num;
                        if(sudoku_sol(board))
                            return true;
                        board[r][c] = '.';
                    }
                }
                
                return false;
            }
            
        }
    }
    return true;
}

void printGrid(const vector<vector<char>>& board, int cellWidth = 4) {
    int rows = board.size();
    int cols = board[0].size();

    string horizontalLine = "+";
    for (int i = 0; i < cols; ++i) {
        horizontalLine += string(cellWidth, '-') + "+";
    }

    for (int i = 0; i < rows; ++i) {
        // Print top border of row
        cout << horizontalLine << "\n";

        // Print cell values
        for (int j = 0; j < cols; ++j) {
            cout << "|";
            cout << setw(cellWidth) << board[i][j];
        }
        cout << "|\n";
    }

    // Bottom border after last row
    cout << horizontalLine << "\n";
}

int main()
{
    vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                 {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                 {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                 {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                 {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                 {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                 {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                 {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                 {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    sudoku_sol(board);
    printGrid(board);
}