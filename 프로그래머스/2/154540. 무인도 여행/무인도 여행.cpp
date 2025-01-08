#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

// 아이디어1
// 2차원 상태에서의 그래프 문제라고 생각한다.
// 2차원 그리드 상태에서라면 좌상(0,0)에서 차례대로 접근하면 항상 좌측 상단을 루트로 이용할 수 있다.
// 이를 이용해서 bfs를 이용해서 모든 접근 가능한 부분을 접근해서 합을 구하면 된다.

// 아이디어2
// 탐색 방향을 오른쪽, 아래쪽으로만 하는 것은 안 된다. 가령 ㅗ 모양 섬이 존재할 경우 가장 왼쪽이 처리 안 될 수 있다.
// ㅛ 모양 같은 것도 존재하므로 전방향 탐색이 필요하다.

// bfs로 노드를 관리하기가 번거로우므로 dfs로 변경

// 회고1
// 동시에 dfs 탐색과 코스트 계산을 하니까 실수가 좀 있었다.
// 굳이 동시에 구현보다는 한 번에 하나의 기능을 구현하고 태스트를 하는 것이 구현하기 쉬웠을 것 같다.

using namespace std;

int dfs_sum_cost(int row, int col, const vector<string>& maps, vector<vector<bool>>& visited);

vector<int> solution(vector<string> maps) {
    int rows = maps.size();
    int cols = maps[0].length();
    
    vector<int> costs;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(maps[row][col] != 'X' && !visited[row][col]) {
                int cost = dfs_sum_cost(row, col, maps, visited);
                costs.push_back(cost);
            }
        }
    }
    
    if(costs.empty()) {
        return {-1};
    }
    
    sort(costs.begin(), costs.end());
    return costs;
}

// left, up, right, down
constexpr pair<int, int> dirs[4] = {{-1,0}, {0, 1}, {1, 0}, {0, -1}};

int dfs_sum_cost(int row, int col, const vector<string>& maps, vector<vector<bool>>& visited) {
    int rows = maps.size();
    int cols = maps[0].size();
    visited[row][col] = true;
    
    int cost = maps[row][col] - '0';
    for(pair<int, int> dir : dirs) {
        int next_row = row + dir.first;
        int next_col = col + dir.second;
        
        if( (next_row >= 0 && next_row < rows && next_col >= 0 && next_col < cols)
           && maps[next_row][next_col] != 'X'
           && !visited[next_row][next_col]) {
            cost += dfs_sum_cost(next_row, next_col, maps, visited);
        }
    }
    
    return cost;
}