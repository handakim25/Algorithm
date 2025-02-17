#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>

using namespace std;

// 아이디어
// 1. 한 번 이동에 무조건 다른 곳에 접근이 가능하므로 weight가 1인 상황과 같다. bfs를 이용할 수 있다.

void bfs_distance(pair<int, int> start, const vector<string>& graph, vector<vector<int>>& distances);
pair<int, int> next_move_pos(pair<int, int> start, pair<int, int> dir, const vector<string>& graph);
bool IsInBoard(pair<int, int> pos, const vector<string>& graph);

int solution(vector<string> board) {
    int rows = board.size();
    int cols = board[0].length();
    pair<int, int> start;
    pair<int, int> end;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(board[row][col] == 'R') {
                start = make_pair(row, col);
            }
            else if(board[row][col] == 'G') {
                end = make_pair(row, col);
            }
        }
    }
    
    vector<vector<int>> distances(rows, vector<int>(cols, -1));
    bfs_distance(start, board, distances);
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            cout << distances[row][col] << ' ';
        }
        cout << endl;
    }
    
    return distances[end.first][end.second];
}

// left, up, right, down
const int dir_x[] = {-1, 0, 1, 0};
const int dir_y[] = {0, 1, 0, -1};
const int dir_counts = 4;

void bfs_distance(pair<int, int> start, const vector<string>& graph, vector<vector<int>>& distances) {
    queue<pair<int, int>> q;
    q.push(start);
    distances[start.first][start.second] = 0;
    
    while(!q.empty()) {
        pair<int, int> node = q.front();
        q.pop();
        for(int i = 0; i < dir_counts; i++) {
            pair<int, int> neighbor = next_move_pos(node, make_pair(dir_x[i], dir_y[i]), graph);
            if(distances[neighbor.first][neighbor.second] == -1) {
                distances[neighbor.first][neighbor.second] = distances[node.first][node.second] + 1;
                q.push(neighbor);
            }
        }
    }
}


pair<int, int> operator+(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}
pair<int, int>& operator+=(pair<int, int>& lhs, const pair<int, int>& rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

pair<int, int> next_move_pos(pair<int, int> start, pair<int, int> dir, const vector<string>& graph) {
    pair<int, int> next_pos = start;
    
    while(IsInBoard(next_pos + dir, graph) && graph[next_pos.first + dir.first][next_pos.second + dir.second] != 'D') {
        next_pos += dir;
    }
    
    return next_pos;
}

bool IsInBoard(pair<int, int> pos, const vector<string>& graph) {
    int rows = graph.size();
    int cols = graph[0].length();
    
    return pos.first >= 0 && pos.first < rows && pos.second >= 0 && pos.second < cols;
}
