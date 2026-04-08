# 08. 그래프 기초 (Graph Basics)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

### 그래프 표현 방식

| 방식 | 공간 | 엣지 확인 | 인접 노드 | 적합한 경우 |
|------|------|---------|---------|------------|
| 인접 행렬 | O(V²) | O(1) | O(V) | 밀집 그래프 |
| 인접 리스트 | O(V+E) | O(degree) | O(degree) | 희소 그래프 |

### DFS (깊이 우선 탐색)
- 스택 또는 재귀 사용
- 활용: 사이클 탐지, 위상 정렬, 연결 요소 찾기

### BFS (너비 우선 탐색)
- 큐 사용
- 활용: **최단 경로** (가중치 없는 그래프), 레벨 탐색

### 유니온-파인드 (Union-Find)
서로소 집합을 효율적으로 관리하는 자료구조.
- 활용: 연결 요소, MST (크루스칼)

---

## 💡 핵심 패턴 및 템플릿

### DFS (재귀)
```python
def dfs(graph, node, visited=None):
    if visited is None:
        visited = set()
    visited.add(node)
    for neighbor in graph[node]:
        if neighbor not in visited:
            dfs(graph, neighbor, visited)
    return visited
```

### BFS
```python
from collections import deque

def bfs(graph, start):
    visited = {start}
    queue = deque([start])
    distances = {start: 0}
    while queue:
        node = queue.popleft()
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                distances[neighbor] = distances[node] + 1
                queue.append(neighbor)
    return distances
```

### 2D 그리드 DFS/BFS
```python
def grid_bfs(grid, start_r, start_c):
    rows, cols = len(grid), len(grid[0])
    visited = [[False] * cols for _ in range(rows)]
    queue = deque([(start_r, start_c)])
    visited[start_r][start_c] = True
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    while queue:
        r, c = queue.popleft()
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols and not visited[nr][nc]:
                visited[nr][nc] = True
                queue.append((nr, nc))
```

### 유니온-파인드
```python
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # 경로 압축
        return self.parent[x]
    
    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px == py:
            return False
        if self.rank[px] < self.rank[py]:
            px, py = py, px
        self.parent[py] = px
        if self.rank[px] == self.rank[py]:
            self.rank[px] += 1
        return True
    
    def connected(self, x, y):
        return self.find(x) == self.find(y)
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [타겟 넘버](https://programmers.co.kr/learn/courses/30/lessons/43165) | Level 2 | DFS/BFS | [ ] |
| [네트워크](https://programmers.co.kr/learn/courses/30/lessons/43162) | Level 3 | DFS/BFS, Union-Find | [ ] |
| [게임 맵 최단거리](https://programmers.co.kr/learn/courses/30/lessons/1844) | Level 2 | BFS | [ ] |
| [단어 변환](https://programmers.co.kr/learn/courses/30/lessons/43163) | Level 3 | BFS | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [DFS와 BFS](https://www.acmicpc.net/problem/1260) | Silver | DFS, BFS 기본 | [ ] |
| [연결 요소의 개수](https://www.acmicpc.net/problem/11724) | Silver | DFS/BFS | [ ] |
| [미로 탐색](https://www.acmicpc.net/problem/2178) | Silver | BFS 최단경로 | [ ] |
| [섬의 개수](https://www.acmicpc.net/problem/4963) | Silver | DFS/BFS 그리드 | [ ] |
| [집합의 표현](https://www.acmicpc.net/problem/1717) | Gold | 유니온-파인드 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Number of Islands](https://leetcode.com/problems/number-of-islands/) | Medium | DFS/BFS 그리드 | [ ] |
| [Course Schedule](https://leetcode.com/problems/course-schedule/) | Medium | DFS 사이클 탐지 | [ ] |
| [Clone Graph](https://leetcode.com/problems/clone-graph/) | Medium | DFS/BFS | [ ] |
| [Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/) | Medium | DFS 멀티 소스 | [ ] |

---

## ✅ 진행 상황

- [ ] 인접 리스트/행렬로 그래프 표현 학습
- [ ] DFS 재귀/반복 구현 숙지
- [ ] BFS 구현 및 최단경로 활용 학습
- [ ] 2D 그리드 탐색 패턴 숙지
- [ ] 유니온-파인드 구현 학습
- [ ] 프로그래머스 추천 문제 4개 완료
- [ ] 백준 추천 문제 5개 완료
- [ ] LeetCode 추천 문제 4개 완료
- [ ] 복습 완료 (1주 후)
