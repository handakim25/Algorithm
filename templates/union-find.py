"""
유니온-파인드 (Union-Find / Disjoint Set) 템플릿
=================================================
- 기본 유니온-파인드
- 크루스칼 알고리즘 (MST)
- 프림 알고리즘 (MST)
"""

import sys
import heapq
input = sys.stdin.readline
INF = float('inf')


# ============================================================
# 1. 유니온-파인드 (Union-Find)
#    경로 압축 + 랭크 기반 합치기
#    시간 복잡도: 거의 O(1) (역 아커만 함수)
# ============================================================
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n + 1))
        self.rank = [0] * (n + 1)
        self.size = [1] * (n + 1)  # 각 집합의 크기
        self.num_components = n    # 연결 요소 수

    def find(self, x):
        """x의 루트 노드 반환 (경로 압축)"""
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        """x와 y가 속한 집합 합치기. 새로 합쳐지면 True 반환"""
        px, py = self.find(x), self.find(y)
        if px == py:
            return False
        # 랭크 기반 합치기
        if self.rank[px] < self.rank[py]:
            px, py = py, px
        self.parent[py] = px
        self.size[px] += self.size[py]
        if self.rank[px] == self.rank[py]:
            self.rank[px] += 1
        self.num_components -= 1
        return True

    def connected(self, x, y):
        """x와 y가 같은 집합에 속하는지 확인"""
        return self.find(x) == self.find(y)

    def get_size(self, x):
        """x가 속한 집합의 크기"""
        return self.size[self.find(x)]


# ============================================================
# 2. 크루스칼 알고리즘 (Kruskal's MST)
#    시간 복잡도: O(E log E)
#    간선 기반, 유니온-파인드 활용
# ============================================================
def kruskal(n, edges):
    """
    n: 노드 수
    edges: [(w, u, v), ...] 또는 [(u, v, w), ...]
    반환: (MST 비용, MST 간선 목록)
    """
    # 가중치 기준 정렬
    edges.sort()
    uf = UnionFind(n)
    mst_cost = 0
    mst_edges = []

    for w, u, v in edges:
        if uf.union(u, v):
            mst_cost += w
            mst_edges.append((u, v, w))
            if len(mst_edges) == n - 1:
                break  # MST 완성

    # MST가 완성되지 않으면 연결 그래프가 아님
    if len(mst_edges) < n - 1:
        return -1, []
    return mst_cost, mst_edges


# ============================================================
# 3. 프림 알고리즘 (Prim's MST)
#    시간 복잡도: O(E log V)
#    노드 기반, 힙 활용
# ============================================================
def prim(n, graph, start=1):
    """
    n: 노드 수
    graph: graph[u] = [(v, w), ...] 형태의 인접 리스트
    반환: MST 비용
    """
    visited = [False] * (n + 1)
    heap = [(0, start)]  # (가중치, 노드)
    mst_cost = 0
    mst_count = 0

    while heap and mst_count < n:
        w, u = heapq.heappop(heap)
        if visited[u]:
            continue
        visited[u] = True
        mst_cost += w
        mst_count += 1

        for v, weight in graph[u]:
            if not visited[v]:
                heapq.heappush(heap, (weight, v))

    return mst_cost if mst_count == n else -1


# ============================================================
# 사용 예시
# ============================================================
if __name__ == "__main__":
    # 유니온-파인드 예시
    uf = UnionFind(5)
    uf.union(1, 2)
    uf.union(3, 4)
    print("1,2 연결?", uf.connected(1, 2))  # True
    print("1,3 연결?", uf.connected(1, 3))  # False
    uf.union(2, 3)
    print("1,4 연결?", uf.connected(1, 4))  # True
    print("연결 요소 수:", uf.num_components)  # 2 (1-2-3-4, 5)

    # 크루스칼 예시
    # 노드 4개, 간선: (비용, u, v)
    edges = [(1,1,2), (2,1,3), (3,2,4), (4,3,4), (5,2,3)]
    cost, mst = kruskal(4, edges)
    print("MST 비용 (크루스칼):", cost)  # 1+2+3 = 6

    # 프림 예시
    graph = [[] for _ in range(5)]
    for w, u, v in [(1,1,2), (2,1,3), (3,2,4), (4,3,4), (5,2,3)]:
        graph[u].append((v, w))
        graph[v].append((u, w))
    cost_prim = prim(4, graph)
    print("MST 비용 (프림):", cost_prim)  # 6
