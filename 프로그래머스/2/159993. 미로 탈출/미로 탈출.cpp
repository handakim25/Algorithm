#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <iostream>

using namespace std;

// 최단 거리 문제이다. 가중치가 없을 경우 BFS를 이용해서 최단 거리를 해결할 수 있다.
// 시작 지점부터 레버까지, 그리고 레버부터 출구까지 값을 구한다.
// 중간에 경로가 없을 경우 -1을 반환한다.

// tuple : [distance, destX, destY], 도달 불가능할 경우 distance == -1
tuple<int, int, int> bfs_distance(int startX, int startY, char dest_ch, const vector<string>& maps);
bool IsInMap(int row, int col, const vector<string>& maps);

int solution(vector<string> maps) {
    int rows = maps.size();
    int cols = maps[0].length();
    
    int startX = -1, startY = -1;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(maps[row][col] == 'S') {
                startX = row;
                startY = col;
                // Fix3. S를 찾으면 더 검색할 필요 없다.
                break;
            }
        }
        // 이중 for문 탈출
        if(startX != -1) break;
    }
    
    auto [lever_distance, leverX, leverY] = bfs_distance(startX, startY, 'L', maps);
    cout << "lever : " << lever_distance << endl;
    if(lever_distance == -1) {
        return -1;
    }
    auto [exit_distance, exitX, exitY] = bfs_distance(leverX, leverY, 'E', maps);
    if(exit_distance == -1) {
        return -1;
    }

    return lever_distance + exit_distance;
}

// 좌, 상, 우, 하 방향
// Fix2. 상수는 const를 붙여둔다.
const pair<int, int> dir[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

tuple<int, int, int> bfs_distance(int startX, int startY, char dest_ch, const vector<string>& maps) {
    int rows = maps.size();
    int cols = maps[0].length();
    
    vector<vector<int>> distances(rows, vector<int>(cols, -1));
    distances[startX][startY] = 0;
    
    queue<pair<int, int>> q;
    q.push({startX, startY});
    
    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i].first;
            int ny = y + dir[i].second;
            
            
            if(IsInMap(nx, ny, maps) && distances[nx][ny] == -1) {
                distances[nx][ny] = distances[x][y] + 1;
                q.push({nx, ny});
                
                if(maps[nx][ny] == dest_ch) {
                    return {distances[nx][ny], nx, ny};
                }
            }
        }
    }
    
    return {-1, -1, -1};
}

bool IsInMap(int row, int col, const vector<string>& maps) {
    int rows = maps.size();
    int cols = maps[0].length();
    
    // Fix1. if-else로 하는 것보다 차라리 이런 식으로 바로 반환하는 것이 짧고 간결하다.
    // 이전 코드에서는 거기다가 false, flase를 반환하는 실수까지 했다. 그런 것까지 포함해서 실수를 줄이려면 바로 반환하는 것이 낫다고 생각하나.
    return (row >= 0 && row < rows && col >= 0 && col < cols && maps[row][col] != 'X');
}