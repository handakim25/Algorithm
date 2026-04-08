# 14. 고급 자료구조 (Advanced Data Structures)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

### 세그먼트 트리 (Segment Tree)
구간 쿼리(합, 최솟값, 최댓값 등)를 O(log n)에 처리하고, 점 갱신도 O(log n)에 수행.

### 펜윅 트리 (Fenwick Tree / BIT)
세그먼트 트리보다 구현이 간단하며, 구간 합 쿼리와 점 갱신을 O(log n)에 처리.

### 트라이 (Trie)
문자열 검색에 특화된 트리 자료구조. 문자열 삽입/검색 O(L) (L: 문자열 길이).

### 희소 테이블 (Sparse Table)
불변 배열에서 구간 최솟값/최댓값 쿼리를 O(1)에, 전처리 O(n log n)에 처리.

---

## 💡 핵심 패턴 및 템플릿

### 세그먼트 트리
```python
class SegmentTree:
    def __init__(self, data):
        self.n = len(data)
        self.tree = [0] * (4 * self.n)
        self.build(data, 1, 0, self.n - 1)
    
    def build(self, data, node, start, end):
        if start == end:
            self.tree[node] = data[start]
        else:
            mid = (start + end) // 2
            self.build(data, 2*node, start, mid)
            self.build(data, 2*node+1, mid+1, end)
            self.tree[node] = self.tree[2*node] + self.tree[2*node+1]
    
    def query(self, node, start, end, l, r):
        if r < start or end < l:
            return 0
        if l <= start and end <= r:
            return self.tree[node]
        mid = (start + end) // 2
        return self.query(2*node, start, mid, l, r) + \
               self.query(2*node+1, mid+1, end, l, r)
    
    def update(self, node, start, end, idx, val):
        if start == end:
            self.tree[node] = val
        else:
            mid = (start + end) // 2
            if idx <= mid:
                self.update(2*node, start, mid, idx, val)
            else:
                self.update(2*node+1, mid+1, end, idx, val)
            self.tree[node] = self.tree[2*node] + self.tree[2*node+1]
```

### 펜윅 트리
```python
class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)
    
    def update(self, i, delta):
        while i <= self.n:
            self.tree[i] += delta
            i += i & (-i)
    
    def query(self, i):
        total = 0
        while i > 0:
            total += self.tree[i]
            i -= i & (-i)
        return total
    
    def range_query(self, l, r):
        return self.query(r) - self.query(l - 1)
```

### 트라이
```python
class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False

class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word):
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.is_end = True
    
    def search(self, word):
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end
    
    def starts_with(self, prefix):
        node = self.root
        for char in prefix:
            if char not in node.children:
                return False
            node = node.children[char]
        return True
```

---

## 📝 추천 문제 리스트

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [구간 합 구하기](https://www.acmicpc.net/problem/2042) | Gold | 세그먼트 트리 | [ ] |
| [구간 합 구하기 3](https://www.acmicpc.net/problem/11505) | Gold | 세그먼트 트리 (곱) | [ ] |
| [최솟값과 최댓값](https://www.acmicpc.net/problem/2357) | Gold | 세그먼트 트리 | [ ] |
| [전화번호 목록](https://www.acmicpc.net/problem/5052) | Gold | 트라이 | [ ] |
| [개미굴](https://www.acmicpc.net/problem/14725) | Gold | 트라이 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Implement Trie](https://leetcode.com/problems/implement-trie-prefix-tree/) | Medium | 트라이 구현 | [ ] |
| [Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/) | Medium | 세그먼트 트리/BIT | [ ] |
| [Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) | Hard | BIT/세그먼트 트리 | [ ] |
| [Maximum XOR of Two Numbers](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/) | Medium | 트라이 | [ ] |

---

## ✅ 진행 상황

- [ ] 세그먼트 트리 구현 및 쿼리/갱신 이해
- [ ] 펜윅 트리 구현
- [ ] 트라이 구현
- [ ] 레이지 프로파게이션 학습 (세그먼트 트리 범위 갱신)
- [ ] 백준 추천 문제 5개 완료
- [ ] LeetCode 추천 문제 4개 완료
- [ ] 복습 완료 (1주 후)
