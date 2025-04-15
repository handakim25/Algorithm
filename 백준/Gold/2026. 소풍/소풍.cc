#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool backtracking(int node, int remaining, const vector<set<int>>& graph, vector<bool>& selected, vector<int>& result);
bool isCandidate(int next, const vector<set<int>>& graph, const vector<bool>& selected);

int main() {
    // K, N, F
    int target_count, node_count, edge_count;
    cin >> target_count >> node_count >> edge_count;

    // 1-base로 처리
    vector<set<int>> adj_list(node_count + 1);
    for(int i = 0; i < edge_count; i++) {
        int u, v;
        cin >> u >> v;
        adj_list[u].insert(v);
        adj_list[v].insert(u);
    }

    vector<bool> selected(node_count + 1, false);
    vector<int> result;

    // Handle edge case where K = 1
    if(target_count == 1) {
        cout << 1 << endl;
        return 0;
    }

    if(backtracking(0, target_count, adj_list, selected, result)) {
        sort(result.begin(), result.end());
        for(int i : result) {
            cout << i << endl;
        }
    } else {
        cout << -1;
    }
    
    return 0;
}

bool backtracking(int node, int remaining, const vector<set<int>>& graph, vector<bool>& selected, vector<int>& result) {
    // Base case - 모든 노드를 선택했을 때
    if(remaining == 0) {
        // 결과 수집
        result.clear();
        for(int i = 1; i < selected.size(); i++) {
            if(selected[i]) {
                result.push_back(i);
            }
        }
        return true;
    }

    // 최적화: 남은 노드가 부족하면 더 이상 탐색할 필요 없음
    if(graph.size() - 1 - node < remaining) {
        return false;
    }

    for(int next = node + 1; next < graph.size(); next++) {
        // 이 노드가 현재 선택된 모든 노드와 연결되었는지 확인
        if(isCandidate(next, graph, selected)) {
            selected[next] = true;
            if(backtracking(next, remaining - 1, graph, selected, result)) {
                return true;
            }
            selected[next] = false;
        }
    }

    return false;
}

bool isCandidate(int next, const vector<set<int>>& graph, const vector<bool>& selected) {
    for(int i = 1; i < selected.size(); i++) {
        if(selected[i] && graph[next].find(i) == graph[next].end()) {
            return false; // next는 i와 연결되지 않음
        }
    }
    return true;
}