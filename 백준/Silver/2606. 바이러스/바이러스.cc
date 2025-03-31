#include <iostream>
#include <vector>

// dfs를 이용해서 모든 접근 가능한 노드의 개수를 셀 수 있다.

using namespace std;

int count_connected_nodes(int node, vector<vector<int>>& graph, vector<bool>& visited);

int main() {
    int vertices;
    int edges;
    cin >> vertices;
    cin >> edges;

    // 0-base, input : 1-base
    vector<vector<int>> graph(vertices);
    for(int i = 0; i < edges; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        graph[v1 - 1].push_back(v2 - 1);
        graph[v2 - 1].push_back(v1 - 1);
    }

    vector<bool> visited(vertices, false);
    int connected_node_count = count_connected_nodes(0, graph, visited);
    cout << connected_node_count - 1; // start node는 포함하지 않는다.
    
    return 0;
}

int count_connected_nodes(int node, vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true;

    int count = 1;
    for(int neighbor : graph[node]) {
        if(!visited[neighbor]) {
            count += count_connected_nodes(neighbor, graph, visited);
        }
    }

    return count;
}