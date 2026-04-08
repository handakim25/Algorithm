"""
DFS / BFS 템플릿
================
- 그래프 DFS (재귀/반복)
- 그래프 BFS
- 2D 그리드 DFS/BFS
- 다중 시작점 BFS
"""

import sys
from collections import deque
sys.setrecursionlimit(10**6)
input = sys.stdin.readline

# 인접한 4방향 (상하좌우)
DIRS4 = [(0, 1), (0, -1), (1, 0), (-1, 0)]
# 인접한 8방향
DIRS8 = [(0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,1),(-1,-1)]


# ============================================================
# 1. 그래프 DFS (재귀)
# ============================================================
def dfs_recursive(graph, start, visited=None):
    if visited is None:
        visited = set()
    visited.add(start)
    for neighbor in graph[start]:
        if neighbor not in visited:
            dfs_recursive(graph, neighbor, visited)
    return visited


# ============================================================
# 2. 그래프 DFS (반복 - 스택)
# ============================================================
def dfs_iterative(graph, start):
    visited = set()
    stack = [start]
    order = []
    while stack:
        node = stack.pop()
        if node not in visited:
            visited.add(node)
            order.append(node)
            for neighbor in reversed(graph[node]):  # 순서 유지 위해 reversed
                if neighbor not in visited:
                    stack.append(neighbor)
    return order


# ============================================================
# 3. 그래프 BFS (최단 거리)
# ============================================================
def bfs(graph, start):
    visited = {start}
    queue = deque([start])
    dist = {start: 0}
    while queue:
        node = queue.popleft()
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                dist[neighbor] = dist[node] + 1
                queue.append(neighbor)
    return dist


# ============================================================
# 4. 2D 그리드 BFS (최단 경로)
# ============================================================
def grid_bfs(grid, start_r, start_c, end_r, end_c):
    """2D 그리드에서 시작점에서 끝점까지의 최단 거리"""
    rows, cols = len(grid), len(grid[0])
    if grid[start_r][start_c] == 1 or grid[end_r][end_c] == 1:
        return -1

    visited = [[False] * cols for _ in range(rows)]
    visited[start_r][start_c] = True
    queue = deque([(start_r, start_c, 0)])  # (row, col, distance)

    while queue:
        r, c, d = queue.popleft()
        if r == end_r and c == end_c:
            return d
        for dr, dc in DIRS4:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols and \
               not visited[nr][nc] and grid[nr][nc] == 0:
                visited[nr][nc] = True
                queue.append((nr, nc, d + 1))
    return -1


# ============================================================
# 5. 2D 그리드 DFS (연결 요소 찾기)
# ============================================================
def grid_dfs(grid, r, c, visited):
    """(r, c)에서 시작하는 연결 영역 탐색"""
    rows, cols = len(grid), len(grid[0])
    if r < 0 or r >= rows or c < 0 or c >= cols:
        return
    if visited[r][c] or grid[r][c] == 0:
        return
    visited[r][c] = True
    for dr, dc in DIRS4:
        grid_dfs(grid, r + dr, c + dc, visited)


def count_islands(grid):
    """연결 요소(섬)의 개수 세기"""
    if not grid:
        return 0
    rows, cols = len(grid), len(grid[0])
    visited = [[False] * cols for _ in range(rows)]
    count = 0
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 1 and not visited[r][c]:
                grid_dfs(grid, r, c, visited)
                count += 1
    return count


# ============================================================
# 6. 다중 시작점 BFS (Multi-source BFS)
# ============================================================
def multi_source_bfs(grid, sources):
    """여러 시작점에서 동시에 BFS"""
    rows, cols = len(grid), len(grid[0])
    dist = [[float('inf')] * cols for _ in range(rows)]
    queue = deque()
    for r, c in sources:
        dist[r][c] = 0
        queue.append((r, c))

    while queue:
        r, c = queue.popleft()
        for dr, dc in DIRS4:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols and \
               dist[nr][nc] == float('inf'):
                dist[nr][nc] = dist[r][c] + 1
                queue.append((nr, nc))
    return dist


# ============================================================
# 사용 예시
# ============================================================
if __name__ == "__main__":
    # 그래프 예시
    graph = {
        1: [2, 3],
        2: [1, 4],
        3: [1],
        4: [2]
    }
    print("DFS 재귀:", dfs_recursive(graph, 1))
    print("DFS 반복:", dfs_iterative(graph, 1))
    print("BFS 거리:", bfs(graph, 1))

    # 그리드 예시 (0: 이동 가능, 1: 벽)
    grid = [
        [0, 0, 1, 0],
        [0, 0, 0, 1],
        [1, 0, 0, 0],
        [0, 0, 1, 0]
    ]
    print("그리드 최단 거리:", grid_bfs(grid, 0, 0, 3, 3))

    # 섬 개수 예시
    island_grid = [
        [1, 1, 0, 0],
        [1, 0, 0, 1],
        [0, 0, 1, 1],
        [0, 0, 0, 0]
    ]
    print("섬의 개수:", count_islands(island_grid))  # 3
