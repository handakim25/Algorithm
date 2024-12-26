#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

// 무방향 가중치 그래프에서 최단 거리를 구하는 문제이다.
// 문제를 해결하기 위해서는 다익스트라 알고리즘을 사용하고 K 이하의 거리를 가진 개수를 구하면 될 것 같다.
// 다익스트라에서는 정점을 기준으로 계산하므로 간선 리스트를 인접 리스트로 바꾸고 다익스트라 알고리즘을 사용한다.

// N : 마을의 개수(1-base)
// road : 간선 리스트 (v1, v2, weight)

// pair first : node, second : weight
vector<vector<pair<int, int>>> covnert_edge_to_adj(int n, const vector<vector<int>>& edges);
// return : start로부터의 거리의 리스트
vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& graph);

int solution(int N, vector<vector<int> > road, int K) {
    vector<vector<pair<int, int>>> adj_list = covnert_edge_to_adj(N, road);
    
    vector<int> distances = dijkstra(0, adj_list);
    int count = count_if(distances.begin(), distances.end(), [K](int distance) {
        return distance <= K;
    });
    return count;
}

// 양방향 그래프
// 정수 인덱스 : 1-base -> 0-base로 맞추어야 한다.
// edge list : [v1, v2, weight]
// pair first : node, second : weight
vector<vector<pair<int, int>>> covnert_edge_to_adj(int n, const vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> adj_list(n);
    for(auto edge : edges) {
        int v1 = edge[0] - 1;
        int v2 = edge[1] - 1;
        int w = edge[2];
        
        adj_list[v1].emplace_back(v2, w);
        adj_list[v2].emplace_back(v1, w);
    }
    
    return adj_list;
}

// return : start로부터의 거리의 리스트
// graph : pair first : node, weight
vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> distances(n, numeric_limits<int>::max());
    distances[start] = 0;
    
    // pair first : node 경로까지의 distance, second : node
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<> > pq;
    pq.push({0, start});
    
    // 매번 거리가 가장 짧은 정점을 가져와서 새로운 거리를 계산하고 pq에 다음 탐색할 값들을 추가한다.
    while(!pq.empty()) {
        auto [distance, node] = pq.top();
        pq.pop();
        
        // 현재 최단 거리보다 더 클 경우 다른 경로에서 처리된 것이므로 더 처리할 필요가 없다.
        if(distance > distances[node]) continue;
        
        for(auto& edge : graph[node]) {
            auto [neighbor, weight] = edge;
            
            // 새로 계산된 거리가 현재 거리보다 짧을 경우 갱신한다.
            if(distances[node] + weight < distances[neighbor]) {
                distances[neighbor] = distances[node] + weight;
                pq.push({distances[neighbor], neighbor});
            }
        }
    }
    
    return distances;
}
