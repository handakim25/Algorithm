#include <string>
#include <vector>
#include <queue>

using namespace std;

// 최단 시간이므로 최단 거리이고 거리가 모두 1이므로 BFS를 이용해서 최단 거리를 계산할 수 있다.
// n : 지역
// roads : Graph, 간선 리스트
// sources : 거리 시작
// destination : 목적지
// 아이디어
// 1. 목적지가 하나이므로 목적지에서 모든 정점에 대해서 BFS를 실행하고 확인하면 된다.
// 2. 간선 리스트이므로 인접 리스트로 변경해야 한다.
// 3. 정점의 인덱스는 1-base이므로 배열 생성 등에서 주의한다.

// 0-base로 변환
vector<vector<int>> convert_edge_to_adj(int n, const vector<vector<int>>& edge_list);
// 도달 불가능은 -1
vector<int> bfs_distance(int start, const vector<vector<int>>& graph);

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<vector<int>> adj_list = convert_edge_to_adj(n, roads);
    vector<int> distances = bfs_distance(destination - 1, adj_list);
    
    vector<int> result;
    for(int source : sources) {
        result.push_back(distances[source - 1]);        
    }
    
    return result;
}

vector<vector<int>> convert_edge_to_adj(int n, const vector<vector<int>>& edge_list) {
    vector<vector<int>> result(n);
    
    for(const auto& edge : edge_list) {
        int v1 = edge[0] - 1;
        int v2 = edge[1] - 1;
        
        result[v1].push_back(v2);
        result[v2].push_back(v1);
    }
    
    return result;
}

vector<int> bfs_distance(int start, const vector<vector<int>>& graph) {
    int n = graph.size();
    
    queue<int> q;
    vector<int> distances(n, -1);
    
    q.push(start);
    distances[start] = 0;
    
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        
        for(int neighbor : graph[node]) {
            if(distances[neighbor] == -1) {
                q.push(neighbor);
                distances[neighbor] = distances[node] + 1;    
            }
        }
    }
    
    return distances;
}