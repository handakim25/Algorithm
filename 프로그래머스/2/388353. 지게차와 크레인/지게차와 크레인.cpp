#include <string>
#include <vector>
#include <algorithm>
#include <queue>

// 지게차 : 접근이 가능한 컨테이너(1면이 외부와 연결)
// 크레인 : 모든 컨테이너

// 지게차를 검출할 수 있는 로직이 필요하다.
// 외부가 존재하지 않는데 외부를 미리 정의해서 처리하는 것이 쉬울 수도 있다.
// 외부의 경우 외곽에서 테스트를 하면 된다. 
// 제일 간단한 방법은 그래프 탐색을 이용하면 외부에서 접근 가능한 시점을 확인할 수 있다.
// 한 번 접근에서 collect할 대상을 체크하고 모든 과정이 지나면 한 번에 제거하면 된다.

using namespace std;

void add_external(vector<string>& storage);
void remove_outside(vector<string>& storage, vector<vector<bool>>& visited, char remove);
void remove_all(vector<string>& storage, char remove);
bool is_in_range(int row, int col, int rows, int cols);

int solution(vector<string> storage, vector<string> requests) {
    add_external(storage);
    
    vector<vector<bool>> visited(storage.size(), vector<bool>(storage[0].length(), false));
    for(const string& request : requests) {
        if(request.size() == 1) {
            remove_outside(storage, visited, request[0]);
            for(vector<bool>& row : visited) {
                fill(row.begin(), row.end(), false);
            }
        }
        else if(request.size() == 2) {
            remove_all(storage, request[0]);
        }
    }
    
    int count = 0;
    for(const string& cols : storage) {
        // fix4: count_if로 변경
        count += count_if(cols.begin(), cols.end(), [](const char& ch) {return ch != ' ';});
    }
    return count;
}

void add_external(vector<string>& storage) {
    if(storage.empty()) {
        return;
    }
    
    for(string& cols : storage) {
        cols.insert(cols.begin(), ' ');
        cols.insert(cols.end(), ' ');
    }
    
    size_t new_length = storage[0].length();
    storage.insert(storage.begin(), string(new_length, ' '));
    storage.insert(storage.end(), string(new_length, ' '));
}

// fix3 : pair를 constexpr로 수정
// left, up, right, down
constexpr pair<int, int> dt[] = {
    {0, -1},
    {-1, 0},
    {0, 1},
    {1, 0},
};

void remove_outside(vector<string>& storage, vector<vector<bool>>& visited, char remove) {
    vector<pair<int, int>> removes;
    // 재귀를 쓰기 번거로우니 bfs를 이용하기로 한다.
    queue<pair<int, int>> q;
    q.push({0, 0});
    visited[0][0] = true;

    int rows = storage.size();
    int cols = storage[0].length();
    
    while(!q.empty()) {
        // fix5 : 구조 분해로 변경, 가급적이면 간결하게 작성해야 덜 헷갈린다.
        auto [row, col] = q.front();
        q.pop();
        
        for(int i = 0; i < 4; i++) {
            // fix: next_node는 굳이 필요하지 않으므로 삭제했다.
            int next_row = row + dt[i].first;
            int next_col = col + dt[i].second;
            
            if(is_in_range(next_row, next_col, rows, cols)
              && !visited[next_row][next_col]) {
                char next_node_val = storage[next_row][next_col];
                visited[next_row][next_col] = true;
                
                if(next_node_val == ' ') {
                    q.push({next_row, next_col});
                }
                // ' '가 아닌 경우 outside인 경우이다.
                // outside일 경우 추가적으로 탐색을 진행하지 않는다.
                else if(next_node_val == remove) {
                    removes.push_back({next_row, next_col});
                }
            }
        }
    }
    
    for(const pair<int, int>& to_remove : removes) {
        storage[to_remove.first][to_remove.second] = ' ';
    }
}

void remove_all(vector<string>& storage, char remove) {
    for(string& row : storage) {
        // fix2 : for 루프를 replace로 변경
        replace(row.begin(), row.end(), remove, ' ');
    }
}

bool is_in_range(int row, int col, int rows, int cols) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}