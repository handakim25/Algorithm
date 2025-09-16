#include <vector>

// 영역이란 것은 같은 원소값들이 연속으로 존재하는 구간을 의미한다.
// dfs/bfs를 이용하면 연결된 모든 값들을 찾을 수 있고, 좌상단부터 실행할 경우 모든 경우의 수를 파악할 수 있다.

using namespace std;

int dfs(int row, int col, vector<vector<int>>& board, vector<vector<bool>>& visited);
bool is_reachable(int nr, int nc, vector<vector<int>>& board);

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;

    int rows = picture.size();
    int cols = picture[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(picture[row][col] != 0 && !visited[row][col] ) {
                number_of_area++;
                int size_of_one_area = dfs(row, col, picture, visited);
                max_size_of_one_area = max(max_size_of_one_area, size_of_one_area);
            }
        }
    }
    
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}

int dfs(int row, int col, vector<vector<int>>& board, vector<vector<bool>>& visited) {
    visited[row][col] = true;

    // left, up, right, down
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};
    
    int area_size = 1;
    for(int i = 0; i < 4; i++) {
        int nr = row + dr[i];
        int nc = col + dc[i];
        if(is_reachable(nr, nc, board)
          && !visited[nr][nc]
          && board[row][col] == board[nr][nc]) {
            area_size += dfs(nr, nc, board, visited);
        }
    }
    
    return area_size;
}

bool is_reachable(int nr, int nc, vector<vector<int>>& board) {
    int rows = board.size();
    int cols = board[0].size();
    
    return nc >= 0 && nc < cols && nr >= 0 && nr < rows;
}