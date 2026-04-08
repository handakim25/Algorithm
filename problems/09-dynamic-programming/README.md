# 09. 동적 프로그래밍 (Dynamic Programming)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

동적 프로그래밍(DP)은 복잡한 문제를 더 작은 하위 문제로 분해하고, **중복되는 하위 문제의 결과를 저장(메모이제이션)**하여 효율적으로 해결하는 기법입니다.

### DP 적용 조건
1. **최적 부분 구조**: 전체 문제의 최적해가 하위 문제의 최적해로 구성
2. **겹치는 부분 문제**: 동일한 하위 문제가 반복 등장

### DP 접근 방식
- **Top-down**: 재귀 + 메모이제이션 (직관적)
- **Bottom-up**: 반복문으로 작은 문제부터 해결 (공간 최적화 용이)

### 주요 DP 유형
1. **1D DP**: 피보나치, 계단, LIS
2. **2D DP**: 최장 공통 부분 수열(LCS), 배낭 문제
3. **구간 DP**: 행렬 연쇄 곱셈, 팰린드롬 파티션
4. **비트마스크 DP**: 외판원 순회 (TSP)
5. **트리 DP**: 트리의 독립 집합

---

## 💡 핵심 패턴 및 템플릿

### 1D DP - LIS (최장 증가 부분 수열)
```python
def lis(arr):
    n = len(arr)
    dp = [1] * n
    for i in range(1, n):
        for j in range(i):
            if arr[j] < arr[i]:
                dp[i] = max(dp[i], dp[j] + 1)
    return max(dp)

# O(n log n) 풀이
from bisect import bisect_left

def lis_nlogn(arr):
    tails = []
    for num in arr:
        pos = bisect_left(tails, num)
        if pos == len(tails):
            tails.append(num)
        else:
            tails[pos] = num
    return len(tails)
```

### 2D DP - LCS (최장 공통 부분 수열)
```python
def lcs(s1, s2):
    m, n = len(s1), len(s2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s1[i-1] == s2[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
    return dp[m][n]
```

### 배낭 문제 (0/1 Knapsack)
```python
def knapsack(weights, values, capacity):
    n = len(weights)
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for w in range(capacity + 1):
            dp[i][w] = dp[i-1][w]
            if weights[i-1] <= w:
                dp[i][w] = max(dp[i][w], dp[i-1][w - weights[i-1]] + values[i-1])
    return dp[n][capacity]
```

### 구간 DP
```python
def interval_dp(arr):
    n = len(arr)
    dp = [[0] * n for _ in range(n)]
    # 길이 1부터 시작
    for length in range(2, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            dp[i][j] = float('inf')
            for k in range(i, j):
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + cost(i, k, j))
    return dp[0][n-1]
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [N으로 표현](https://programmers.co.kr/learn/courses/30/lessons/42895) | Level 3 | DP | [ ] |
| [정수 삼각형](https://programmers.co.kr/learn/courses/30/lessons/43105) | Level 3 | 2D DP | [ ] |
| [등굣길](https://programmers.co.kr/learn/courses/30/lessons/42898) | Level 3 | 2D DP | [ ] |
| [도둑질](https://programmers.co.kr/learn/courses/30/lessons/42897) | Level 4 | 원형 DP | [ ] |
| [가장 긴 팰린드롬](https://programmers.co.kr/learn/courses/30/lessons/12904) | Level 3 | 구간 DP | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [계단 오르기](https://www.acmicpc.net/problem/2579) | Silver | 1D DP | [ ] |
| [가장 긴 증가하는 부분 수열](https://www.acmicpc.net/problem/11053) | Silver | LIS | [ ] |
| [가장 긴 공통 부분 수열](https://www.acmicpc.net/problem/9251) | Gold | LCS | [ ] |
| [배낭 문제](https://www.acmicpc.net/problem/12865) | Gold | 0/1 Knapsack | [ ] |
| [외판원 순회](https://www.acmicpc.net/problem/2098) | Gold | 비트마스크 DP | [ ] |
| [행렬 곱셈 순서](https://www.acmicpc.net/problem/11049) | Gold | 구간 DP | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) | Easy | 1D DP | [ ] |
| [Coin Change](https://leetcode.com/problems/coin-change/) | Medium | DP | [ ] |
| [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) | Medium | LIS | [ ] |
| [Edit Distance](https://leetcode.com/problems/edit-distance/) | Medium | 2D DP | [ ] |
| [Burst Balloons](https://leetcode.com/problems/burst-balloons/) | Hard | 구간 DP | [ ] |

---

## ✅ 진행 상황

- [ ] DP 기본 원칙 이해 (최적 부분 구조, 겹치는 부분 문제)
- [ ] Top-down (메모이제이션) 구현 숙지
- [ ] Bottom-up (타뷸레이션) 구현 숙지
- [ ] LIS O(n²) / O(n log n) 구현
- [ ] LCS 구현
- [ ] 배낭 문제 구현
- [ ] 프로그래머스 추천 문제 5개 완료
- [ ] 백준 추천 문제 6개 완료
- [ ] LeetCode 추천 문제 5개 완료
- [ ] 복습 완료 (1주 후)
