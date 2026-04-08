# 12. 그래프 심화 (Advanced Graph)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

### 최단 경로 알고리즘

| 알고리즘 | 시간 복잡도 | 음수 간선 | 단일/전체 | 적용 |
|---------|-----------|---------|---------|------|
| 다익스트라 | O((V+E) log V) | ❌ | 단일 출발 | 양수 가중치 그래프 |
| 벨만-포드 | O(VE) | ✅ | 단일 출발 | 음수 간선 존재 |
| 플로이드-와샬 | O(V³) | ✅ | 모든 쌍 | 노드 수 적은 경우 |

### 최소 신장 트리 (MST)

| 알고리즘 | 시간 복잡도 | 방식 |
|---------|-----------|------|
| 크루스칼 | O(E log E) | 간선 중심 (Union-Find) |
| 프림 | O(E log V) | 노드 중심 (힙) |

### 위상 정렬 (Topological Sort)
방향 그래프에서 사이클 없이 선후 관계를 정렬.
- **카한 알고리즘**: 진입 차수 0인 노드부터 처리

---

## 💡 핵심 패턴 및 템플릿

### 다익스트라
```python
import heapq

def dijkstra(graph, start, n):
    dist = [float('inf')] * (n + 1)
    dist[start] = 0
    heap = [(0, start)]  # (거리, 노드)
    while heap:
        d, u = heapq.heappop(heap)
        if d > dist[u]:
            continue
        for v, w in graph[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                heapq.heappush(heap, (dist[v], v))
    return dist
```

### 플로이드-와샬
```python
def floyd_warshall(n, edges):
    INF = float('inf')
    dist = [[INF] * (n + 1) for _ in range(n + 1)]
    for i in range(n + 1):
        dist[i][i] = 0
    for u, v, w in edges:
        dist[u][v] = w
    for k in range(1, n + 1):
        for i in range(1, n + 1):
            for j in range(1, n + 1):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    return dist
```

### 크루스칼 (MST)
```python
def kruskal(n, edges):
    edges.sort(key=lambda x: x[2])
    uf = UnionFind(n + 1)
    mst_cost = 0
    mst_edges = 0
    for u, v, w in edges:
        if uf.union(u, v):
            mst_cost += w
            mst_edges += 1
            if mst_edges == n - 1:
                break
    return mst_cost
```

### 위상 정렬 (카한)
```python
from collections import deque

def topological_sort(n, edges):
    graph = [[] for _ in range(n + 1)]
    in_degree = [0] * (n + 1)
    for u, v in edges:
        graph[u].append(v)
        in_degree[v] += 1
    queue = deque([i for i in range(1, n + 1) if in_degree[i] == 0])
    order = []
    while queue:
        node = queue.popleft()
        order.append(node)
        for neighbor in graph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)
    return order if len(order) == n else []  # 빈 리스트면 사이클 존재
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [가장 먼 노드](https://programmers.co.kr/learn/courses/30/lessons/49189) | Level 3 | BFS 최단경로 | [ ] |
| [순위](https://programmers.co.kr/learn/courses/30/lessons/49191) | Level 3 | 플로이드-와샬 | [ ] |
| [섬 연결하기](https://programmers.co.kr/learn/courses/30/lessons/42861) | Level 3 | 크루스칼 (MST) | [ ] |
| [방의 개수](https://programmers.co.kr/learn/courses/30/lessons/49190) | Level 5 | 그래프 응용 | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [최단경로](https://www.acmicpc.net/problem/1753) | Gold | 다익스트라 | [ ] |
| [플로이드](https://www.acmicpc.net/problem/11404) | Gold | 플로이드-와샬 | [ ] |
| [최소 스패닝 트리](https://www.acmicpc.net/problem/1197) | Gold | 크루스칼/프림 | [ ] |
| [줄 세우기](https://www.acmicpc.net/problem/2252) | Gold | 위상 정렬 | [ ] |
| [타임머신](https://www.acmicpc.net/problem/11657) | Gold | 벨만-포드 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Network Delay Time](https://leetcode.com/problems/network-delay-time/) | Medium | 다익스트라 | [ ] |
| [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) | Medium | 위상 정렬 | [ ] |
| [Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/) | Medium | MST (프림/크루스칼) | [ ] |
| [Find the City With the Smallest Number of Neighbors](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/) | Medium | 플로이드-와샬 | [ ] |
| [Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/) | Medium | 다익스트라 변형 | [ ] |

---

## ✅ 진행 상황

- [ ] 다익스트라 알고리즘 구현 숙지
- [ ] 플로이드-와샬 알고리즘 구현
- [ ] 벨만-포드 알고리즘 학습
- [ ] 크루스칼/프림 MST 구현
- [ ] 위상 정렬 구현
- [ ] 프로그래머스 추천 문제 4개 완료
- [ ] 백준 추천 문제 5개 완료
- [ ] LeetCode 추천 문제 5개 완료
- [ ] 복습 완료 (1주 후)
