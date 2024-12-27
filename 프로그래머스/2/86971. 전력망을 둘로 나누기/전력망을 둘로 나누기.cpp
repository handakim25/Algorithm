#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <map>

using namespace std;

// n이 [2, 100]의 충분히 작은 숫자이고 wire이 n -1이므로 충분히 작은 숫자이다. 따라서 완전 탐색으로 문제를 풀어본다.
// wire에서 하나가 빠진다면 그것은 전선을 하나 끊은 것이다.
// 트리가 문제 조건인 이유는 하나를 끊었을 경우 반드시 2개로 나뉘기 때문이라 생각한다.
// 송전탑의 개수 차이를 계산할려면 일단은 2가지 방법이 생각난다.
// 첫번째는 간선 리스트를 인접 리스트로 변환하고 DFS / BFS 등의 알고리즘을 사용해서 visited를 탐색하는 것이다. 전체 개수는 정해져 있으므로 visited를 counting하면 나머지 개수가 나온다.
// 두번째는 union-find 알고리즘을 활용하는 것이다.
// 일단은 저번 경험을 토대로 생각해보면 알고리즘 단계를 줄이는 것이 복잡도를 줄이는데 유효했으므로 union-find 알고리즘을 이용해 구현하도록 한다.

class UnionFind {
public:
    vector<int> parent, rank;
    UnionFind(int n) : parent(n), rank(n) {
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if(parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if(rootX == rootY) return false;
        
        if(rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        }
        else if(rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        }
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        
        return true;
    }
    
    vector<int> GetParents() {
        vector<int> updated_parents(parent.size());
        for(int k = 0; k < parent.size(); k++) {
            updated_parents[k] = find(k);
        }
        
        return updated_parents;
    }
};

// fix3: GetGroupCount에서 GetGroupSizes로 변경
// Group의 개수를 구하는 것이 아니라 Group의 요소들의 개수들을 구하는 것이므로 sizes가 더 명확하다.
vector<int> GetGroupSizes(const vector<int>& uf_arr);

// 정점 인덱스는 1-base이므로 0-base로 매칭해줘야 한다.
int solution(int n, vector<vector<int>> wires) {
    int min_val = numeric_limits<int>::max();
    for(int i = 0; i < wires.size(); i++) {
        UnionFind uf(n);
        for(int j = 0; j < wires.size(); j++) {
            if(j == i) {
                continue;
            }
            int v1 = wires[j][0] - 1;
            int v2 = wires[j][1] - 1;
            uf.unite(v1, v2);
        }
        
        // Fix1. UnionFind의 Parent의 경우 최종적으로 Update가 안 되어 있을 수도 있다.
        // 따라서 parent의 값을 직접 사용하는 것이 아니라 find를 해서 각각의 루트 노드를 구해야 한다.
        // 그리고 구현적으로도 private으로 구현됬을 parent에 직접 접근하지 않고 find를 통해서 새로운 배열을 생성하는 것이 타당하다.
        // Fix4. parent를 직접 구하는 것이 아니고 uf로 옮겼다. parents가 어떻게 관리되고 있는지는 uf가 관리해야 할 일이다.
        vector<int> parents = uf.GetParents();        
        // 각각의 집합의 수를 센다.
        vector<int> group_count = GetGroupSizes(parents);
        min_val = min(min_val, abs(group_count[0] - group_count[1]));
    }
    
    return min_val;
}

// fix2. pair<int, int>로 반환해도 되지만 범용적으로 작성했다.
vector<int> GetGroupSizes(const vector<int>& uf_arr) {
    // key : group, value : freq
    unordered_map<int, int> freq;
    for(int i : uf_arr) {
        freq[i]++;
    }
    
    vector<int> group_sizes;
    for(auto [group, count] : freq) {
        group_sizes.push_back(count);
    }
    return group_sizes;
}