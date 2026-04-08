# 07. 트리 (Tree)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

### 트리의 특성
- 노드(Node)와 엣지(Edge)로 구성된 비선형 자료구조
- 사이클 없는 연결 그래프
- N개의 노드를 가진 트리는 N-1개의 엣지를 가짐

### 주요 트리 유형

#### 이진 트리 (Binary Tree)
각 노드가 최대 2개의 자식을 가짐.
- **전위 순회**: 루트 → 왼쪽 → 오른쪽
- **중위 순회**: 왼쪽 → 루트 → 오른쪽 (BST에서 정렬된 결과)
- **후위 순회**: 왼쪽 → 오른쪽 → 루트
- **레벨 순회**: BFS를 이용한 너비 우선 탐색

#### 이진 탐색 트리 (BST)
왼쪽 < 루트 < 오른쪽 성질을 만족.
- 탐색/삽입/삭제: 평균 O(log n), 최악 O(n)

#### 최소 신장 트리 (MST)
그래프의 모든 노드를 최소 비용으로 연결.
- 프림(Prim), 크루스칼(Kruskal) 알고리즘

#### 최소 공통 조상 (LCA)
두 노드의 가장 가까운 공통 조상 찾기.

---

## 💡 핵심 패턴 및 템플릿

### 이진 트리 순회
```python
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 전위 순회 (재귀)
def preorder(root):
    if not root:
        return []
    return [root.val] + preorder(root.left) + preorder(root.right)

# 중위 순회 (반복)
def inorder_iterative(root):
    result, stack = [], []
    curr = root
    while curr or stack:
        while curr:
            stack.append(curr)
            curr = curr.left
        curr = stack.pop()
        result.append(curr.val)
        curr = curr.right
    return result

# 레벨 순회 (BFS)
from collections import deque

def level_order(root):
    if not root:
        return []
    result, queue = [], deque([root])
    while queue:
        level = []
        for _ in range(len(queue)):
            node = queue.popleft()
            level.append(node.val)
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        result.append(level)
    return result
```

### LCA (최소 공통 조상) - 기본
```python
def lca(root, p, q):
    if not root or root == p or root == q:
        return root
    left = lca(root.left, p, q)
    right = lca(root.right, p, q)
    if left and right:
        return root
    return left if left else right
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [길 찾기 게임](https://programmers.co.kr/learn/courses/30/lessons/42892) | Level 3 | 이진 트리 구성 + 순회 | [ ] |
| [표 편집](https://programmers.co.kr/learn/courses/30/lessons/81303) | Level 3 | 연결리스트 | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [트리 순회](https://www.acmicpc.net/problem/1991) | Silver | 전/중/후위 순회 | [ ] |
| [트리의 높이와 너비](https://www.acmicpc.net/problem/2250) | Gold | 트리 순회 응용 | [ ] |
| [LCA](https://www.acmicpc.net/problem/11437) | Gold | LCA 기본 | [ ] |
| [LCA 2](https://www.acmicpc.net/problem/11438) | Platinum | LCA 희소 테이블 | [ ] |
| [세그먼트 트리](https://www.acmicpc.net/problem/2042) | Gold | 세그먼트 트리 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/) | Easy | DFS/BFS | [ ] |
| [Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/) | Medium | BST 검증 | [ ] |
| [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) | Medium | BFS | [ ] |
| [Lowest Common Ancestor](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) | Medium | LCA | [ ] |
| [Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/) | Hard | 트리 DP | [ ] |

---

## ✅ 진행 상황

- [ ] 이진 트리 전/중/후위/레벨 순회 구현
- [ ] BST 삽입/탐색/삭제 구현
- [ ] LCA 기본 구현 학습
- [ ] 세그먼트 트리 개념 학습
- [ ] 프로그래머스 추천 문제 2개 완료
- [ ] 백준 추천 문제 5개 완료
- [ ] LeetCode 추천 문제 5개 완료
- [ ] 복습 완료 (1주 후)
