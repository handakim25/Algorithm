"""
세그먼트 트리 / 펜윅 트리 템플릿
==================================
- 세그먼트 트리 (구간 합, 최솟값, 최댓값)
- 레이지 프로파게이션 (범위 갱신)
- 펜윅 트리 (Binary Indexed Tree)
"""

import sys
input = sys.stdin.readline
INF = float('inf')


# ============================================================
# 1. 세그먼트 트리 - 구간 합
#    쿼리/갱신: O(log n)
# ============================================================
class SegmentTreeSum:
    def __init__(self, data):
        self.n = len(data)
        self.tree = [0] * (4 * self.n)
        self._build(data, 1, 0, self.n - 1)

    def _build(self, data, node, start, end):
        if start == end:
            self.tree[node] = data[start]
        else:
            mid = (start + end) // 2
            self._build(data, 2*node, start, mid)
            self._build(data, 2*node+1, mid+1, end)
            self.tree[node] = self.tree[2*node] + self.tree[2*node+1]

    def query(self, l, r, node=1, start=None, end=None):
        """[l, r] 구간의 합"""
        if start is None:
            start, end = 0, self.n - 1
        if r < start or end < l:
            return 0
        if l <= start and end <= r:
            return self.tree[node]
        mid = (start + end) // 2
        return self.query(l, r, 2*node, start, mid) + \
               self.query(l, r, 2*node+1, mid+1, end)

    def update(self, idx, val, node=1, start=None, end=None):
        """index idx의 값을 val로 변경"""
        if start is None:
            start, end = 0, self.n - 1
        if start == end:
            self.tree[node] = val
        else:
            mid = (start + end) // 2
            if idx <= mid:
                self.update(idx, val, 2*node, start, mid)
            else:
                self.update(idx, val, 2*node+1, mid+1, end)
            self.tree[node] = self.tree[2*node] + self.tree[2*node+1]


# ============================================================
# 2. 세그먼트 트리 - 구간 최솟값
# ============================================================
class SegmentTreeMin:
    def __init__(self, data):
        self.n = len(data)
        self.tree = [INF] * (4 * self.n)
        self._build(data, 1, 0, self.n - 1)

    def _build(self, data, node, start, end):
        if start == end:
            self.tree[node] = data[start]
        else:
            mid = (start + end) // 2
            self._build(data, 2*node, start, mid)
            self._build(data, 2*node+1, mid+1, end)
            self.tree[node] = min(self.tree[2*node], self.tree[2*node+1])

    def query(self, l, r, node=1, start=None, end=None):
        if start is None:
            start, end = 0, self.n - 1
        if r < start or end < l:
            return INF
        if l <= start and end <= r:
            return self.tree[node]
        mid = (start + end) // 2
        return min(self.query(l, r, 2*node, start, mid),
                   self.query(l, r, 2*node+1, mid+1, end))

    def update(self, idx, val, node=1, start=None, end=None):
        if start is None:
            start, end = 0, self.n - 1
        if start == end:
            self.tree[node] = val
        else:
            mid = (start + end) // 2
            if idx <= mid:
                self.update(idx, val, 2*node, start, mid)
            else:
                self.update(idx, val, 2*node+1, mid+1, end)
            self.tree[node] = min(self.tree[2*node], self.tree[2*node+1])


# ============================================================
# 3. 펜윅 트리 (BIT - Binary Indexed Tree)
#    구간 합 + 점 갱신: O(log n)
#    세그먼트 트리보다 구현 간단, 상수 배 빠름
# ============================================================
class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)  # 1-indexed

    def update(self, i, delta):
        """index i (1-indexed)에 delta 더하기"""
        while i <= self.n:
            self.tree[i] += delta
            i += i & (-i)  # 가장 낮은 비트 더하기

    def query(self, i):
        """[1, i] 구간의 합"""
        total = 0
        while i > 0:
            total += self.tree[i]
            i -= i & (-i)  # 가장 낮은 비트 빼기
        return total

    def range_query(self, l, r):
        """[l, r] 구간의 합 (1-indexed)"""
        return self.query(r) - self.query(l - 1)

    def build(self, data):
        """배열로 초기화 O(n log n)"""
        for i, val in enumerate(data, 1):
            self.update(i, val)


# ============================================================
# 4. 2D 펜윅 트리
# ============================================================
class FenwickTree2D:
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.tree = [[0] * (cols + 1) for _ in range(rows + 1)]

    def update(self, r, c, delta):
        i = r
        while i <= self.rows:
            j = c
            while j <= self.cols:
                self.tree[i][j] += delta
                j += j & (-j)
            i += i & (-i)

    def query(self, r, c):
        total = 0
        i = r
        while i > 0:
            j = c
            while j > 0:
                total += self.tree[i][j]
                j -= j & (-j)
            i -= i & (-i)
        return total

    def range_query(self, r1, c1, r2, c2):
        return (self.query(r2, c2) - self.query(r1-1, c2)
                - self.query(r2, c1-1) + self.query(r1-1, c1-1))


# ============================================================
# 사용 예시
# ============================================================
if __name__ == "__main__":
    data = [1, 3, 5, 7, 9, 11]

    # 세그먼트 트리 (구간 합)
    st = SegmentTreeSum(data)
    print("구간 합 [1,4]:", st.query(1, 4))   # 3+5+7+9 = 24
    st.update(2, 10)  # data[2] = 10 (5 -> 10)
    print("갱신 후 [1,4]:", st.query(1, 4))   # 3+10+7+9 = 29

    # 세그먼트 트리 (최솟값)
    st_min = SegmentTreeMin(data)
    print("구간 최솟값 [2,5]:", st_min.query(2, 5))  # 5

    # 펜윅 트리
    ft = FenwickTree(len(data))
    ft.build(data)
    print("펜윅 [1,4]:", ft.range_query(2, 5))   # 3+5+7+9 = 24
    ft.update(3, 5)   # data[2] += 5 (5 -> 10)
    print("갱신 후 [1,4]:", ft.range_query(2, 5)) # 3+10+7+9 = 29
