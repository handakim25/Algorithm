#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 룰을 위반하는 경우
// 1. 선공, 후공 순서 이슈 : 선공, 후공의 개수 차이가 1 이내로 되어야 한다.
// 2. 이미 승리한 시점에서 더 진행되어서는 안 된다.

// 1. 선공은 항상 한 번 더 둘 수 있으므로 차이의 개수가 1 이하면 가능한 배치이다.
// 2. 승리한 시점에서 게임이 종료되어야 한다.
// 승리한 플레이어를 찾고 플레이어에서 게임 진행 여부를 판단.
// 선공이 승리했을 경우 선공의 개수보다 후공의 개수가 적어야 한다.
// 후공이 승리했을 경우 선공의 개수보다 후공의 개수가 같아야 한다.

const char first_ch = 'O';
const char second_ch = 'X';

pair<int, int> count_place(const vector<string>& board);
bool is_winner(const vector<string>& board, const char piece);

int solution(vector<string> board) {
    auto [first_count, second_count] = count_place(board);
    // fix4. gap_count -> turn_diff로 변경
    // gap, count 둘 다 모호한 이름이다. diff로 차이를 나타내고 count보다는 턴의 차이란 것을 나타낸다.
    // count는 임의의 수량이라서 현재 모호하다.
    const int turn_diff = first_count - second_count;
    if(turn_diff != 0 && turn_diff != 1) {
        return 0;
    }
    
    bool is_first_win = is_winner(board, first_ch);
    bool is_second_win = is_winner(board, second_ch);
    
    // fix3. 주석 부분 추가. 주석이 없으면 이해가 안 되는 코드이다.
    // 선공 플레이어가 승리하면 후공 플레이어보다 한 개 더 많아야 한다.
    // fix4. 이미 계산한 turn_diff를 이용
    if(is_first_win && turn_diff != 1) {
        return 0;
    }
    // 후공 플레이어가 승리하면 서로 같아야 한다.
    if(is_second_win && turn_diff != 0) {
        return 0;
    }
    
    return 1;
}

pair<int, int> count_place(const vector<string>& board) {
    int first_count = 0;
    int second_count = 0;
    
    for(const string& row : board) {
        for(const char& col : row) {
            if(col == first_ch) {
                first_count++;
            }
            if(col == second_ch) {
                second_count++;
            }
        }
    }
    
    return make_pair(first_count, second_count);
}

bool is_winner(const vector<string>& board, const char piece) {
    // 승자는 가로, 세로, 대각선의 8가지이다.
    const int rows = board.size();
    const int cols = board[0].length();
    
    // fix1. 가로, 세로를 통합해서 계산할 수 있다.
    for(int i = 0; i < rows; i++) {
        bool row_win = true;
        bool col_win = true;
        for(int j = 0; j < cols; j++) {
            if(board[i][j] != piece) row_win = false;
            if(board[j][i] != piece) col_win = false;
        }
        if(row_win || col_win) return true;
    }
    
    
    // fix2. 대각선도 하나로 통합해서 계산할 수 있다.
    bool diag1 = true;
    bool diag2 = true;
    for(int i = 0; i < rows; i++) {
        if(board[i][i] != piece) diag1 = false;
        if(board[i][cols - i - 1] != piece) diag2 = false;
    }
    if(diag1 || diag2) return true;
    
    return false;
}