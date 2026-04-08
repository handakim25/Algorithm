# 06. 재귀 (Recursion)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

재귀는 함수가 자기 자신을 호출하는 방법으로 문제를 해결하는 기법입니다.

### 핵심 원칙
1. **기저 조건 (Base Case)**: 재귀 종료 조건
2. **재귀 단계 (Recursive Case)**: 문제를 더 작은 문제로 분해
3. **진행 보장**: 각 호출은 반드시 기저 조건에 가까워져야 함

### 메모이제이션 (Memoization)
중복 계산을 방지하기 위해 이미 계산한 값을 저장하는 기법. 동적 프로그래밍의 Top-down 방식.

### 꼬리 재귀 최적화
Python은 기본적으로 꼬리 재귀 최적화를 지원하지 않으므로, 깊은 재귀는 반복문으로 변환 필요.
- Python 기본 재귀 한도: 1000
- `sys.setrecursionlimit(10**6)` 으로 조정 가능

---

## 💡 핵심 패턴 및 템플릿

### 기본 재귀 (피보나치)
```python
# 순수 재귀 - O(2^n)
def fib(n):
    if n <= 1:
        return n
    return fib(n-1) + fib(n-2)

# 메모이제이션 - O(n)
from functools import lru_cache

@lru_cache(maxsize=None)
def fib_memo(n):
    if n <= 1:
        return n
    return fib_memo(n-1) + fib_memo(n-2)
```

### 순열/조합 생성
```python
# 순열
def permutations(arr, r):
    if r == 0:
        return [[]]
    result = []
    for i, elem in enumerate(arr):
        rest = arr[:i] + arr[i+1:]
        for p in permutations(rest, r-1):
            result.append([elem] + p)
    return result

# 조합
def combinations(arr, r):
    if r == 0:
        return [[]]
    if not arr:
        return []
    result = []
    for p in combinations(arr[1:], r-1):
        result.append([arr[0]] + p)
    result.extend(combinations(arr[1:], r))
    return result
```

### 분할 정복 패턴
```python
def divide_and_conquer(arr, left, right):
    # 기저 조건
    if left >= right:
        return base_case(arr[left])
    
    mid = (left + right) // 2
    
    # 분할
    left_result = divide_and_conquer(arr, left, mid)
    right_result = divide_and_conquer(arr, mid + 1, right)
    
    # 정복 (합치기)
    return merge_results(left_result, right_result)
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [하노이의 탑](https://programmers.co.kr/learn/courses/30/lessons/12946) | Level 2 | 기본 재귀 | [ ] |
| [N-Queen](https://programmers.co.kr/learn/courses/30/lessons/12952) | Level 2 | 백트래킹 | [ ] |
| [피로도](https://programmers.co.kr/learn/courses/30/lessons/87946) | Level 2 | 순열/완전 탐색 | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [하노이 탑 이동 순서](https://www.acmicpc.net/problem/11729) | Silver | 재귀 | [ ] |
| [Z](https://www.acmicpc.net/problem/1074) | Silver | 분할 정복 | [ ] |
| [색종이 만들기](https://www.acmicpc.net/problem/2630) | Silver | 분할 정복 | [ ] |
| [피보나치 수 6](https://www.acmicpc.net/problem/11444) | Gold | 행렬 거듭제곱 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) | Easy | 메모이제이션 | [ ] |
| [Fibonacci Number](https://leetcode.com/problems/fibonacci-number/) | Easy | 재귀/DP | [ ] |
| [Pow(x, n)](https://leetcode.com/problems/powx-n/) | Medium | 분할 정복 | [ ] |
| [Permutations](https://leetcode.com/problems/permutations/) | Medium | 백트래킹 | [ ] |
| [Merge Sort / Sort an Array](https://leetcode.com/problems/sort-an-array/) | Medium | 합병 정렬 | [ ] |

---

## ✅ 진행 상황

- [ ] 재귀 기본 원칙 이해 (기저 조건, 재귀 단계)
- [ ] 메모이제이션 / `@lru_cache` 활용 학습
- [ ] 순열/조합 재귀 구현 숙지
- [ ] `sys.setrecursionlimit` 처리 방법 학습
- [ ] 프로그래머스 추천 문제 3개 완료
- [ ] 백준 추천 문제 4개 완료
- [ ] LeetCode 추천 문제 5개 완료
- [ ] 복습 완료 (1주 후)
