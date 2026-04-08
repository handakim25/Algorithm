"""
다익스트라 / 최단 경로 템플릿
==============================
- 다익스트라 (단일 출발 최단 경로)
- 플로이드-와샬 (모든 쌍 최단 경로)
- 벨만-포드 (음수 간선 허용)
"""

import sys
import heapq
input = sys.stdin.readline
INF = float('inf')


# ============================================================
# 1. 다익스트라 (Dijkstra)
#    시간 복잡도: O((V+E) log V)
#    음수 간선 불가
# ============================================================
def dijkstra(graph, start, n):
    """
    graph: graph[u] = [(v, w), ...] 형태의 인접 리스트
    start: 시작 노드
    n: 노드 수 (1-indexed이면 n+1 크기로)
    반환: dist[i] = start에서 i까지의 최단 거리
    """
    dist = [INF] * (n + 1)
    dist[start] = 0
    heap = [(0, start)]  # (거리, 노드)

    while heap:
        d, u = heapq.heappop(heap)
        if d > dist[u]:
            continue  # 이미 더 짧은 경로로 처리됨
        for v, w in graph[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                heapq.heappush(heap, (dist[v], v))
    return dist


# 경로 복원이 필요한 경우
def dijkstra_with_path(graph, start, n):
    dist = [INF] * (n + 1)
    dist[start] = 0
    prev = [-1] * (n + 1)
    heap = [(0, start)]

    while heap:
        d, u = heapq.heappop(heap)
        if d > dist[u]:
            continue
        for v, w in graph[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                prev[v] = u
                heapq.heappush(heap, (dist[v], v))

    def get_path(end):
        path = []
        node = end
        while node != -1:
            path.append(node)
            node = prev[node]
        return path[::-1]

    return dist, get_path


# ============================================================
# 2. 플로이드-와샬 (Floyd-Warshall)
#    시간 복잡도: O(V³)
#    음수 간선 허용 (음수 사이클 탐지 가능)
#    모든 쌍 최단 경로
# ============================================================
def floyd_warshall(n, edges):
    """
    n: 노드 수 (1-indexed)
    edges: [(u, v, w), ...] 형태
    반환: dist[i][j] = i에서 j까지의 최단 거리
    """
    dist = [[INF] * (n + 1) for _ in range(n + 1)]
    for i in range(n + 1):
        dist[i][i] = 0
    for u, v, w in edges:
        dist[u][v] = min(dist[u][v], w)

    for k in range(1, n + 1):      # 경유 노드
        for i in range(1, n + 1):  # 출발 노드
            for j in range(1, n + 1):  # 도착 노드
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]

    # 음수 사이클 탐지: dist[i][i] < 0인 노드 존재 시
    return dist


# ============================================================
# 3. 벨만-포드 (Bellman-Ford)
#    시간 복잡도: O(VE)
#    음수 간선 허용, 음수 사이클 탐지 가능
# ============================================================
def bellman_ford(n, edges, start):
    """
    n: 노드 수
    edges: [(u, v, w), ...] 형태
    start: 시작 노드
    반환: (dist, has_negative_cycle)
    """
    dist = [INF] * (n + 1)
    dist[start] = 0

    for _ in range(n - 1):  # V-1번 반복
        for u, v, w in edges:
            if dist[u] != INF and dist[u] + w < dist[v]:
                dist[v] = dist[u] + w

    # 음수 사이클 탐지
    has_negative_cycle = False
    for u, v, w in edges:
        if dist[u] != INF and dist[u] + w < dist[v]:
            has_negative_cycle = True
            break

    return dist, has_negative_cycle


# ============================================================
# 사용 예시
# ============================================================
if __name__ == "__main__":
    # 다익스트라 예시
    # 노드 4개, 간선: 1-2(2), 1-3(5), 2-3(1), 2-4(3), 3-4(2)
    n = 4
    graph = [[] for _ in range(n + 1)]
    edges_list = [(1,2,2), (1,3,5), (2,3,1), (2,4,3), (3,4,2)]
    for u, v, w in edges_list:
        graph[u].append((v, w))
        graph[v].append((u, w))

    dist = dijkstra(graph, 1, n)
    print("다익스트라:", dist[1:])  # [0, 2, 3, 5]

    # 플로이드-와샬 예시
    dist_fw = floyd_warshall(n, edges_list + [(v,u,w) for u,v,w in edges_list])
    print("플로이드:", dist_fw[1][1:n+1])  # [0, 2, 3, 5]

    # 벨만-포드 예시
    dist_bf, neg_cycle = bellman_ford(n, edges_list + [(v,u,w) for u,v,w in edges_list], 1)
    print("벨만-포드:", dist_bf[1:], "음수사이클:", neg_cycle)
