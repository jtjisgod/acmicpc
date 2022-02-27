#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

auto board = new int[9][9];

void read() {
    for(int row=0;row<9; row++) {
        for(int col=0;col<9; col++) {
            cin >> board[row][col];
        }
    }
}

void show() {
    for_each(&board[0], &board[9], [](int row[9]) -> void {
        for_each(&row[0], &row[9], [](int item) -> void {
            cout << item << " ";
        });
        cout << endl;
    });
}

bool predict() {
    for(int row=0;row<9; row++) {
        int row_start = (int)(row / 3) * 3;
        int row_end = row_start+3;
        for(int col=0;col<9; col++) {
            if(board[row][col] != 0) continue;
            vector<int> candidated{1,2,3,4,5,6,7,8,9};
            int col_start = (int)(col / 3) * 3;
            int col_end = col_start+3;
            for(int i=0; i<9; i++) {
                candidated.erase(std::remove(candidated.begin(), candidated.end(), board[i][col]), candidated.end());
                candidated.erase(std::remove(candidated.begin(), candidated.end(), board[row][i]), candidated.end());
                if(row_start <= i && i < row_end) {
                    for(int j=col_start; j<col_end; j++) {
                        candidated.erase(std::remove(candidated.begin(), candidated.end(), board[i][j]), candidated.end());
                    }
                }
            }
            auto preVal = board[row][col];
            for(auto iter: candidated) {
                board[row][col] = iter;
                bool is_success = predict();
                if(is_success) {
                    return true;
                }
            }
            board[row][col] = preVal;
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    read();
    predict();
    show();
    return 0;
}
