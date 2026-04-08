# 💻 알고리즘 코드 템플릿 모음 (Templates)

## 📋 목차
1. [템플릿 목록](#-템플릿-목록)
2. [사용 방법](#-사용-방법)

---

## 📁 템플릿 목록

| 파일 | 알고리즘 | 시간 복잡도 |
|------|---------|-----------|
| [binary-search.py](binary-search.py) | 이진 탐색, 파라메트릭 서치 | O(log n) |
| [dfs-bfs.py](dfs-bfs.py) | DFS, BFS, 그리드 탐색 | O(V+E) |
| [dijkstra.py](dijkstra.py) | 다익스트라, 플로이드-와샬, 벨만-포드 | O((V+E)log V) |
| [union-find.py](union-find.py) | 유니온-파인드, MST (크루스칼) | O(α(n)) |
| [segment-tree.py](segment-tree.py) | 세그먼트 트리, 펜윅 트리 | O(log n) |

---

## 🚀 사용 방법

### 새 문제 풀이 시작 시
1. 문제 유형에 맞는 템플릿 파일을 열기
2. 필요한 부분을 복사하여 풀이에 활용
3. 문제에 맞게 수정

### 템플릿 커스터마이징
각 템플릿은 기본 구조를 제공합니다. 실제 문제에 맞게:
- 입력 형식 수정
- 조건 추가/수정
- 반환값 조정

---

## 📝 자주 사용하는 Python 팁

### 입출력 최적화
```python
import sys
input = sys.stdin.readline

# 빠른 출력
import sys
print = sys.stdout.write

# 재귀 한도 설정
sys.setrecursionlimit(10**6)
```

### 자주 쓰는 모듈
```python
from collections import defaultdict, Counter, deque
from itertools import permutations, combinations, product
from functools import lru_cache, reduce
from heapq import heappush, heappop, heapify
from bisect import bisect_left, bisect_right, insort
import math
```

### 유용한 내장 함수
```python
# 최대공약수
from math import gcd
lcm = lambda a, b: a * b // gcd(a, b)

# 무한대
INF = float('inf')

# 2D 배열 초기화
grid = [[0] * cols for _ in range(rows)]

# 인접한 4방향
DIRS = [(0,1), (0,-1), (1,0), (-1,0)]

# 인접한 8방향
DIRS8 = [(0,1), (0,-1), (1,0), (-1,0), (1,1), (1,-1), (-1,1), (-1,-1)]
```
