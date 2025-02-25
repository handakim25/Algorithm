#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

// 최단 거리 문제이긴 한데 일단은 단순하게 구현하면 A, B, S의 최단 거리 리스트를 구한 다음에
// min(S->R + R->A + R->B) for all edges in R 이런 느낌?
// 최단거리가 아마 O(V + E), 모든 거리를 계산하면 O(E) 정도니까 문제 없지 않을까?

// fares가 간선리스트니까 이거는 인접리스트로 변환할 필요는 있겠네

// 일단은 생각보다 오타가 많아서 vector<vector<pair<int, int>>>를 typedef를 하는 방향도 생각해 둘 것

// fares node는 1-base이니까 이거를 0-base로 변경
// pair : first : node, second : weight / edge_list : [v1, v2, w]
vector<vector<pair<int, int>>> convert_edge_list_to_adj_list(const vector<vector<int>>& edge_list, int n);
// pair : first : node, second : weight / return : vector<int> : distances from start node
vector<int> shortest_path(int start, const vector<vector<pair<int, int>>>& adj_list);

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    vector<vector<pair<int, int>>> adj_list = convert_edge_list_to_adj_list(fares, n);
    
    vector<int> shortest_path_from_a = shortest_path(a - 1, adj_list);
    vector<int> shortest_path_from_b = shortest_path(b - 1, adj_list);
    vector<int> shortest_path_from_s = shortest_path(s - 1, adj_list);
    
    int min_cost = numeric_limits<int>::max();
    for(int i = 0; i < n; i++) {
        // i == s일 경우 합승하지 않는 경우
        int min_cost_from_i = shortest_path_from_s[i] + shortest_path_from_a[i] + shortest_path_from_b[i];
        min_cost = min(min_cost, min_cost_from_i);
    }
    
    return min_cost;
}

vector<vector<pair<int, int>>> convert_edge_list_to_adj_list(const vector<vector<int>>& edge_list, int n) {
    vector<vector<pair<int, int>>> adj_list(n);
    
    // edge : v1, v2, w
    for(const vector<int>& edge : edge_list) {
        int v1 = edge[0] - 1;
        int v2 = edge[1] - 1;
        int w = edge[2];
        
        adj_list[v2].emplace_back(v1, w);
        adj_list[v1].emplace_back(v2, w);
    }

    return adj_list;
}

// 다이직스트라 알고리즘 이용, 다이직스트라는 priority queue를 이용해서 후보군 중에서 가장 짧은 값을 가져와서 이어나가면 된다.
vector<int> shortest_path(int start, const vector<vector<pair<int, int>>>& adj_list) {
    int n = adj_list.size();
    vector<int> distances(n, numeric_limits<int>::max());
    // first : dist, second : node, min heap : 후보군까지의 현재 계산된 거리
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    
    distances[start] = 0;
    pq.push({0, start});
    
    while(!pq.empty()) {
        auto [node_dist, node] = pq.top();
        pq.pop();
        
        if(node_dist > distances[node]) continue;
        
        for(auto& neighbor : adj_list[node]) {
            auto [neighbor_node, neighbor_weight] = neighbor;
            
            if(distances[node] + neighbor_weight < distances[neighbor_node]) {
                distances[neighbor_node] = distances[node] + neighbor_weight;
                pq.push({distances[neighbor_node], neighbor_node});
            }
        }
    }
    
    return distances;
}