# 13. 분할 정복 (Divide & Conquer)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

분할 정복은 문제를 더 작은 부분 문제로 **분할(Divide)**하고, 각 부분 문제를 **정복(Conquer)**한 후, 결과를 **합병(Combine)**하는 기법입니다.

### 핵심 단계
1. **분할**: 문제를 동일한 유형의 더 작은 부분 문제로 나눔
2. **정복**: 부분 문제를 재귀적으로 해결 (충분히 작으면 직접 해결)
3. **합병**: 부분 문제의 해를 합쳐 원래 문제의 해를 구성

### 주요 활용
- 합병 정렬 (Merge Sort)
- 퀵 정렬 (Quick Sort)
- 이진 탐색 (Binary Search)
- 거듭제곱 (Fast Exponentiation)
- 행렬 곱셈 (Strassen 알고리즘)
- 카라츠바 알고리즘 (빠른 곱셈)

---

## 💡 핵심 패턴 및 템플릿

### 빠른 거듭제곱
```python
def fast_pow(base, exp, mod=None):
    result = 1
    while exp > 0:
        if exp % 2 == 1:
            result = result * base if mod is None else result * base % mod
        base = base * base if mod is None else base * base % mod
        exp //= 2
    return result
```

### 행렬 거듭제곱 (피보나치 O(log n))
```python
def matrix_multiply(A, B, mod):
    n = len(A)
    C = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod
    return C

def matrix_pow(M, n, mod):
    size = len(M)
    result = [[1 if i == j else 0 for j in range(size)] for i in range(size)]
    while n > 0:
        if n % 2 == 1:
            result = matrix_multiply(result, M, mod)
        M = matrix_multiply(M, M, mod)
        n //= 2
    return result
```

### 병합 정렬 (역전 쌍 개수)
```python
def count_inversions(arr):
    if len(arr) <= 1:
        return arr, 0
    mid = len(arr) // 2
    left, left_inv = count_inversions(arr[:mid])
    right, right_inv = count_inversions(arr[mid:])
    merged, split_inv = merge_count(left, right)
    return merged, left_inv + right_inv + split_inv

def merge_count(left, right):
    result = []
    inversions = 0
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            inversions += len(left) - i
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result, inversions
```

---

## 📝 추천 문제 리스트

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [쿼드트리](https://www.acmicpc.net/problem/1992) | Silver | 분할 정복 | [ ] |
| [Z](https://www.acmicpc.net/problem/1074) | Silver | 분할 정복 | [ ] |
| [피보나치 수 6](https://www.acmicpc.net/problem/11444) | Gold | 행렬 거듭제곱 | [ ] |
| [행렬 제곱](https://www.acmicpc.net/problem/10830) | Gold | 행렬 거듭제곱 | [ ] |
| [버블 소트](https://www.acmicpc.net/problem/1517) | Gold | 병합 정렬 (역전 수) | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Pow(x, n)](https://leetcode.com/problems/powx-n/) | Medium | 빠른 거듭제곱 | [ ] |
| [Merge Sort / Sort an Array](https://leetcode.com/problems/sort-an-array/) | Medium | 병합 정렬 | [ ] |
| [Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) | Hard | 병합 정렬 응용 | [ ] |
| [Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/) | Hard | 분할 정복 | [ ] |

---

## ✅ 진행 상황

- [ ] 분할 정복 기본 원리 이해
- [ ] 빠른 거듭제곱 구현 숙지
- [ ] 행렬 거듭제곱 구현
- [ ] 병합 정렬 응용 (역전 쌍 개수) 학습
- [ ] 백준 추천 문제 5개 완료
- [ ] LeetCode 추천 문제 4개 완료
- [ ] 복습 완료 (1주 후)
