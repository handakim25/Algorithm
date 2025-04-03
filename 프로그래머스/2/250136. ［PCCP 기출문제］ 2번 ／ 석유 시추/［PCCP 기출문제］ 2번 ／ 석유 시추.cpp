#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

// 석유의 위치에 대해서 매번 계산하는 것이 아니라 한 번 계산하고 이용하면 된다.
// 이를 위해서는 2가지 정보가 필요하다.
// - 어느 석유에 속해 있는지(Group)
// - 석유의 양이 어느 정도인지(Group의 특성)
// Grid에서 Grouping의 경우는 비슷한 문제를 풀이한 적이 있는데 문제가 정확히 기억이 나지 않는다.

// Grouping
// 1. 좌상단부터 Grouping을 시작
// 2. 0일 경우 0으로 유지
// 3. 1일 경우
// 3-1. Group Index 발급
// 3-2. Group Index를 DFS를 이용해서 마킹
// 3-3. Total Count를 Group Index에 저장
// Group Index : 1부터 시작, 0은 No Group(Block)
// result : Group Grid Vector, Group Size Vector

// 석유 시추
// Col 단위로 계산
// 1. 석유를 만날 경우
// 2. 석유 인덱스를 확인해서 기존에 없는 인덱스일 경우 합산
// 3. 석유 인덱스를 기록

// group은 1부터 시작
// index map : 특정 row, col의 group index를 저장
// total : group의 총 석유량을 저장
void generate_index_map(const vector<vector<int>>& land, vector<vector<int>>& out_index_map, vector<int>& group_total_oil);
int dfs_mark_oil(int group_index, int row, int col, const vector<vector<int>>& land, vector<vector<int>>& index_map);
bool is_in_boundary(int row, int col, int rows, int cols);
int calculate_sum(int col, const vector<vector<int>>& index_map, const vector<int>& group_total);
void print_map(const vector<vector<int>>& data_map);

int solution(vector<vector<int>> land) {
    vector<vector<int>> index_map;
    vector<int> total;
    generate_index_map(land, index_map, total);
    
    int max_total = 0;
    int cols = land[0].size();
    for(int col = 0; col < cols; col++) {
        int gather = calculate_sum(col, index_map, total);
        max_total = max(max_total, gather);
    }
    
    return max_total;
}

void generate_index_map(const vector<vector<int>>& land, vector<vector<int>>& out_index_map, vector<int>& group_total_oil) {
    int rows = land.size();
    int cols = land[0].size();
    out_index_map.resize(rows, vector<int>(cols, 0));
    group_total_oil.resize(1); // group index는 1부터시작
    
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            // tile is oil && has not visited
            if(land[row][col] == 1
              && out_index_map[row][col] == 0) {
                int group_index = group_total_oil.size(); // size 1일 경우 1의 인덱스를 반환
                int total_oil = dfs_mark_oil(group_index, row, col, land, out_index_map);
                group_total_oil.push_back(total_oil);
            }
        }
    }
}

// left, up, right, down
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
int dfs_mark_oil(int group_index, int row, int col, const vector<vector<int>>& land, vector<vector<int>>& index_map) {
    index_map[row][col] = group_index;
    
    int rows = land.size();
    int cols = land[0].size();
    
    int total_oil = 1;
    for(int i = 0; i < 4; i++) {
        // land[y][x]
        int next_row = row + dy[i];
        int next_col = col + dx[i];
        
        if(is_in_boundary(next_row, next_col, rows, cols)
          && (land[next_row][next_col] == 1 && index_map[next_row][next_col] == 0)) {
            total_oil += dfs_mark_oil(group_index, next_row, next_col, land, index_map);
        }
    }
    
    return total_oil;
}

bool is_in_boundary(int row, int col, int rows, int cols) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

int calculate_sum(int col, const vector<vector<int>>& index_map, const vector<int>& group_total) {
    int rows = index_map.size();
    set<int> groups;
    int total = 0;
    
    for(int row = 0; row < rows; row++) {
        int group_index = index_map[row][col];
        if(groups.find(group_index) == groups.end()) {
            groups.insert(group_index);
            total += group_total[group_index];
        }
    }
    
    return total;
}

void print_map(const vector<vector<int>>& data_map) {
    int rows = data_map.size();
    int cols = data_map[0].size();
    
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            cout << data_map[row][col] << " ";
        }
        cout << endl;
    }
}