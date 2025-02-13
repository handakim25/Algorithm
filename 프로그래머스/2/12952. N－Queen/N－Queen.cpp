#include <string>
#include <vector>

// n-queen problem은 대표적인 백트래킹 문제이다.
// 백트래킹 문제는 상태 공간을 탐색하는 알고리즘으로서 재귀를 통해서 탐색을 한다.
// DFS와 같이 탐색을 하지만 중간에 조건에 맞지 않는 공간일 경우 이를 건너띄게 되고 이것을 가지치기라고 한다.
// 필요한 값은 현재 정보, 공간에 대한 정보, 출력용 변수이다.

using namespace std;

// board: col을 차례로 저장한 값. board[0] == row 0에 배치된 col 값
// row번째에 퀸 배치 시도
void back_tracking(int row, int n, vector<int>& board, int& count);
bool is_safe(int row, int col, const vector<int>& board);

int solution(int n) {
    vector<int> board(n, -1);
    int count = 0;
    back_tracking(0, n, board, count);
    return count;
}

void back_tracking(int row, int n, vector<int>& board, int& count) {
    // 기저 조건
    // row가 0-base이기에 n이 되면 더 이상 배치할 수 없다.
    if(row >= n) {
        count++;
        return;
    }
    
    // 가능한 col을 선택해서 배치한다.
    for(int col = 0; col < n; col++) {
        if(is_safe(row, col, board)) {
            board[row] = col;
            back_tracking(row + 1, n, board, count);
            board[row] = -1;
        }
    }
}

bool is_safe(int row, int col, const vector<int>& board) {
    // 같은 열에 존재하면 안 되고, 대각선에 존재하지 않는다.
    // 전제 조건 : row에 처음 배치된다. row 이후에는 퀸이 배치되어 있지 않는다.
    for(int i = 0; i < row; i++) {
        // board[i] == col : i번째 퀸이 같은 열에 존재 (i번째 퀸의 위치 : (i, board[i]))
        // board[i] - col, row - i : i번째 퀸 : (i, board[i]), 현재 퀸 : (row, col)
        if(board[i] == col || abs(col - board[i]) == row - i) return false;
    }
    
    return true;
}