#include <string>
#include <vector>
#include <algorithm>

// 그래프 문제는 그래프 알고리즘으로 치환하는 문제가 많다. 이 문제는 MST로 치환되는 문제이다.
// MST의 알고리즘은 크루스칼, 프림 알고리즘 2개가 존재하고 둘 다 탐욕법을 기반으로 작성된다.
// 2개의 알고리즘 중에서 프림 알고리즘은 인접 리스트를 이용하고 크루스칼은 간선 리스트를 기반으로 동작한다.
// 문제에서 간선 리스트로 주어지므로 크루스칼 알고리즘을 이용하도록 한다.

// 크루스칼 알고리즘
// 간선을 가중치 기반으로 정렬하고 가장 짧은 순으로 연결한다.
// 이 때 사이클이 생기면 안 되므로 서로소 알고리즘을 이용해서 사이클이 생기지 않도록 한다.

// n : 섬의 개수
// costs : 0, 1 : node index, 2 : cost

using namespace std;

class UnionFind {
private:
    vector<int> parent, rank;
public:
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
        
        // 랭크가 작은 그룹을 큰 그룹의 밑으로 연결한다.
        // 랭크가 같을 경우는 X에 Y를 연결하고 rank를 1 증가한다.
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
};

// cost : 0, 1 : node, 2 : cost
int solution(int n, vector<vector<int>> costs) {
    // 간선 정렬
    sort(costs.begin(), costs.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2];
    });
    UnionFind uf(n);
    int mst_cost = 0;
    
    for(const vector<int>& edge : costs) {
        int u = edge[0];
        int v = edge[1];
        int cost = edge[2];
        
        if(uf.unite(u, v)) {
            mst_cost += cost;
        }
    }
    
    return mst_cost;
}