// interactive terminal based sudoku

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class sudoku {
    private:
        vector<vector<int>> board,soln;
    public:    
        // getter
        vector<vector<int>>& getBoard() {
            return board;
        }

        void choice();   // options
        void take_Board_Inp();  // take input for board filling      
        sudoku(bool useDefault=false);  // default constructor
        void takeInput(vector<vector<int>> &board);
        bool logicCheck(vector<vector<int>> &board,int,int,int);
        void soln_Board(vector<vector<int>> &box);
        bool solution_logic(vector<vector<int>> &box);
        void details();
        void print_board(vector<vector<int>> &game, int); 
};

/* To view solution */
bool sudoku::solution_logic(vector<vector<int>> &box) {
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            if(box[i][j]==0) {
                for(int num=1;num<=9;num++) {
                    if(logicCheck(box,i,j,num)) {
                        box[i][j]=num;
                        if(solution_logic(box))
                            return true;
                        box[i][j]=0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void sudoku::soln_Board(vector<vector<int>> &box) {
    solution_logic(box);
    if(!solution_logic(box)) { 
        cout << "Error: No valid pattern possible\n";
        return;
    }
}

void sudoku::details() {
    cout << "Press\n-  'b' to view current board input\n-   'a' to view solution\n-   'n' to go back\n";
    char ch; cin >> ch;
    switch (ch) {
    case 'b':
        print_board(board,4);
        break;
    
    case 'a':
        print_board(soln,4);
        break;

    case 'n':
        takeInput(board);
        break;

    default:
        cerr << "Invalid option.\n"; 
        break;
    }
}

void rules() {
    cout << "->   Use 0 where you are not filling any value\n";
    cout << "->   Keep value ranging from 0-9 (otherwise it will throw error)\n\n";
}

sudoku::sudoku (bool useDefault) {
    board.resize(9, vector<int>(9, 0));
    if(useDefault) {
        board = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
                {6, 0, 0, 1, 9, 5, 0, 0, 0},
                {0, 9, 8, 0, 0, 0, 0, 6, 0},
                {8, 0, 0, 0, 6, 0, 0, 0, 3},
                {4, 0, 0, 8, 0, 3, 0, 0, 1},
                {7, 0, 0, 0, 2, 0, 0, 0, 6},
                {0, 6, 0, 0, 0, 0, 2, 8, 0},
                {0, 0, 0, 4, 1, 9, 0, 0, 5},
                {0, 0, 0, 0, 8, 0, 0, 7, 9}};     
        soln=board; 
    } else {
        take_Board_Inp();
        soln=board;
    }
}

bool check_val(int value) {
    return value>=0 && value<=9;
}

void sudoku::take_Board_Inp() {
    rules();
    const int rows=9, cols=9;
    for(int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
            cout << "Enter value for cell (" << i+1 << ", " << j+1 << ") [0-9]: \n";
            int value; cin >> value;
            while(!check_val(value)) {
                cout << "Invalid input. Enter a number(1-9): \n";
                cin >> value;
            }
            board[i][j] = value;
        }
    }
}

void sudoku::print_board(vector<vector<int>> &game, int cellWidth=4) {
    const int rows=9, cols=9;
    string horizontalLine = "+";
    for (int i = 0; i < cols; ++i) {
        horizontalLine += string(cellWidth, '-') + "+";
    }

    for (int i = 0; i < rows; ++i) {
        // top border of row
        cout << horizontalLine << "\n";

        // cell values
        for (int j = 0; j < cols; ++j) {
            cout << "|";
            cout << setw(cellWidth) << game[i][j];
        }
        cout << "|\n";
    }

    // Bottom border after last row
    cout << horizontalLine << "\n";
}



void sudoku::choice() {
    /* to handle:- 
    start game, 
    reset
    */
    cout << "____Enter your choice____\n";
    cout << "1. Start the Game\n";
    int ch; cin >> ch;

    switch(ch) {
        // start the game 
        case 1:
            cout << "Press 'y' to start the game:- ";
            char ch; cin >>ch;
            while(ch=='y') {
                takeInput(board);
                cout << "\nPress: -  'y' to continue\n-   'd' for details\n";
                cin >> ch;
                if(ch=='d') {
                    details();
                } 
            } 
            break;

        default:
            cerr << "Error: Invalid Input." << endl;
            return;
    }
}

bool sudoku::logicCheck(vector<vector<int>> &board, int r, int c, int num){
    // upar niche
    for (int i = 0; i < 9; i++){
        if (board[r][i] == num || board[i][c] == num)
            return false;
    }

    // 3*3 box
    int srt_r = r / 3 * 3, srt_c = c / 3 * 3;
    for (int i = srt_r; i < srt_r + 3; i++){
        for (int j = srt_c; j < srt_c + 3; j++){
            if (board[i][j] == num)
                return false;
        }
    }

    return true;
}

bool inp_Check(int num) {
    return num>=1 && num<=9;
}


// TODO: Improve input func.
void sudoku::takeInput(vector<vector<int>> &board) {
    cout << "Enter the index for which you want to change value :\n";
    int idx_r,idx_c;
    cout << "    Row Index(1-9) || Column Index(1-9) \n";
    cin >> idx_r >> idx_c;

    if(board[idx_r-1][idx_c-1]==0) {
        if(!inp_Check(idx_c) || !inp_Check(idx_r)) {
            cout << "Invalid input. Enter a number(1-9)  \n";
            return;
        }   

        cout << " Enter value you want to enter(1-9) \n";
        int value; cin >> value;
        if (!inp_Check(value)) {
            cout << "Invalid input. Enter a number(1-9) \n";
            return;
        }

        if(!logicCheck(board,idx_r-1,idx_c-1,value)) {
            cout << "Error: Invalid Move\n";
            cout << "Do you wish to continue?(y/n)\n";
            char ch; cin >> ch;
            if(ch=='y') 
                takeInput(board);
            else 
                return;
        } else {
            board[idx_r-1][idx_c-1] = value;
        }
    } else {
        cout << "Error: Fixed Value Position.\n";  
        return;
    }
}

int main() {
    /*
    ask choice to use sudoku with default values or create on your own 
    */
    cout << "Do you choose to use default sudoku? (y/n)\n";
    char choose; cin >> choose;
    sudoku game(choose=='y');
    game.print_board(game.getBoard());
    game.choice();
}