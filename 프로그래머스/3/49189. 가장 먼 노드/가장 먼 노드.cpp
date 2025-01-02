#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 최장 거리 문제이다. 가중치가 없을 경우 BFS를 이용해서 해결할 수 있다.
// 입력이 간선 리스트이므로 인접 리스트로 변경하고 BFS를 이용한다.
// 거리를 계산할 경우는 2가지 방법이 존재한다.
// 첫번째는 거리 리스트를 이용하는 경우이다.
// 두번째는 큐에 거리를 같이 기록하는 방법이다.
// 메모리 제한이 심하지 않을 경우는 거리 리스트도 같이 생성해서 처리한다.

vector<vector<int>> convert_edge_to_adj(int n, const vector<vector<int>>& edges);
int bfs_distance(int start, const vector<vector<int>>& adj_list, vector<int>& distances);

int solution(int n, vector<vector<int>> edge) {
    vector<vector<int>> adj_list = convert_edge_to_adj(n, edge);
    
    vector<int> distances(n, -1);
    int max_distance = bfs_distance(0, adj_list, distances);
    return count(distances.begin(), distances.end(), max_distance);
}

// edges : 1-base, 0-base로 전환해서 해결
vector<vector<int>> convert_edge_to_adj(int n, const vector<vector<int>>& edges) {
    vector<vector<int>> adj_list(n);
    
    for(const vector<int>& edge : edges) {
        int e1 = edge[0] - 1;
        int e2 = edge[1] - 1;
        adj_list[e1].push_back(e2);
        adj_list[e2].push_back(e1);
    }
    
    return adj_list;
}

int bfs_distance(int start, const vector<vector<int>>& adj_list, vector<int>& distances) {
    queue<int> q;
    q.push(start);
    distances[0] = 0;
    
    int max_val = -1;
    
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        
        for(int neighbor : adj_list[node]) {
            if(distances[neighbor] == -1) {
                distances[neighbor] = distances[node] + 1;
                q.push(neighbor);
                
                max_val = max(max_val, distances[neighbor]);
            }
        }
    }
    
    return max_val;
}