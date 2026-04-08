# 01. 배열 & 문자열 (Array & String)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

### 배열 (Array)
배열은 동일한 타입의 데이터를 연속된 메모리 공간에 저장하는 자료구조입니다.

- **시간 복잡도**: 접근 O(1), 탐색 O(n), 삽입/삭제 O(n)
- **공간 복잡도**: O(n)

### 핵심 기법

#### 투 포인터 (Two Pointer)
배열의 두 인덱스를 이용해 O(n)으로 문제를 해결하는 기법.
- 정렬된 배열에서 두 수의 합 찾기
- 부분 배열의 합 구하기
- 중복 제거

#### 슬라이딩 윈도우 (Sliding Window)
고정 크기 또는 가변 크기의 윈도우를 이동하며 최적값을 구하는 기법.
- 연속 부분 배열의 최대/최소 합
- 특정 조건을 만족하는 최장/최단 부분 배열

#### 누적 합 (Prefix Sum)
미리 누적 합을 계산해 구간 합을 O(1)에 구하는 기법.
- 2D 배열 누적 합
- 구간 합 쿼리

---

## 💡 핵심 패턴 및 템플릿

### 투 포인터
```python
def two_pointer(arr, target):
    left, right = 0, len(arr) - 1
    while left < right:
        curr_sum = arr[left] + arr[right]
        if curr_sum == target:
            return [left, right]
        elif curr_sum < target:
            left += 1
        else:
            right -= 1
    return []
```

### 슬라이딩 윈도우 (고정 크기)
```python
def sliding_window_fixed(arr, k):
    window_sum = sum(arr[:k])
    max_sum = window_sum
    for i in range(k, len(arr)):
        window_sum += arr[i] - arr[i - k]
        max_sum = max(max_sum, window_sum)
    return max_sum
```

### 누적 합
```python
def prefix_sum(arr):
    n = len(arr)
    prefix = [0] * (n + 1)
    for i in range(n):
        prefix[i + 1] = prefix[i] + arr[i]
    # 구간 [l, r] 합: prefix[r+1] - prefix[l]
    return prefix
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [두 개 뽑아서 더하기](https://programmers.co.kr/learn/courses/30/lessons/68644) | Level 1 | 배열 순회 | [ ] |
| [소수 만들기](https://programmers.co.kr/learn/courses/30/lessons/12977) | Level 1 | 조합 | [ ] |
| [전화번호 목록](https://programmers.co.kr/learn/courses/30/lessons/42577) | Level 2 | 정렬, 문자열 | [ ] |
| [가장 큰 수](https://programmers.co.kr/learn/courses/30/lessons/42746) | Level 2 | 커스텀 정렬 | [ ] |
| [연속 부분 수열 합의 개수](https://programmers.co.kr/learn/courses/30/lessons/131701) | Level 2 | 슬라이딩 윈도우 | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [수 정렬하기](https://www.acmicpc.net/problem/2750) | Bronze | 정렬 | [ ] |
| [두 수의 합](https://www.acmicpc.net/problem/3273) | Silver | 투 포인터 | [ ] |
| [부분합](https://www.acmicpc.net/problem/1806) | Gold | 투 포인터 | [ ] |
| [구간 합 구하기 4](https://www.acmicpc.net/problem/11659) | Silver | 누적 합 | [ ] |
| [배열 합치기](https://www.acmicpc.net/problem/11728) | Silver | 투 포인터 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Two Sum](https://leetcode.com/problems/two-sum/) | Easy | 해시 | [ ] |
| [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | Easy | 슬라이딩 윈도우 | [ ] |
| [Container With Most Water](https://leetcode.com/problems/container-with-most-water/) | Medium | 투 포인터 | [ ] |
| [Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) | Medium | 누적 합 | [ ] |
| [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) | Hard | 슬라이딩 윈도우, 덱 | [ ] |

---

## ✅ 진행 상황

- [ ] 투 포인터 개념 학습
- [ ] 슬라이딩 윈도우 개념 학습
- [ ] 누적 합 개념 학습
- [ ] 프로그래머스 추천 문제 5개 완료
- [ ] 백준 추천 문제 5개 완료
- [ ] LeetCode 추천 문제 5개 완료
- [ ] 복습 완료 (1주 후)
