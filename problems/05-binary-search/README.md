# 05. 이진 탐색 (Binary Search)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

이진 탐색은 **정렬된 배열**에서 탐색 범위를 반씩 줄여가며 O(log n) 시간에 원소를 찾는 알고리즘입니다.

### 핵심 개념
- **기본 이진 탐색**: 정렬된 배열에서 특정 값 탐색
- **Lower Bound**: 특정 값 이상인 첫 번째 위치
- **Upper Bound**: 특정 값 초과인 첫 번째 위치
- **파라메트릭 서치**: 최적화 문제를 결정 문제로 변환

### 파라메트릭 서치 (Parametric Search)
"특정 조건을 만족하는 최솟값/최댓값 찾기" 유형에 사용합니다.

**판별 조건**: `f(mid)`가 단조 증가/감소여야 합니다.

---

## 💡 핵심 패턴 및 템플릿

### 기본 이진 탐색
```python
def binary_search(arr, target):
    left, right = 0, len(arr) - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1
```

### Lower Bound (target 이상인 첫 번째 위치)
```python
def lower_bound(arr, target):
    left, right = 0, len(arr)
    while left < right:
        mid = (left + right) // 2
        if arr[mid] < target:
            left = mid + 1
        else:
            right = mid
    return left
```

### Upper Bound (target 초과인 첫 번째 위치)
```python
def upper_bound(arr, target):
    left, right = 0, len(arr)
    while left < right:
        mid = (left + right) // 2
        if arr[mid] <= target:
            left = mid + 1
        else:
            right = mid
    return left
```

### 파라메트릭 서치 템플릿
```python
def parametric_search(arr, condition):
    """
    condition(mid)이 True인 최솟값 찾기
    단조성: False, False, ..., True, True, ...
    """
    left, right = 0, max_value  # 탐색 범위
    while left < right:
        mid = (left + right) // 2
        if condition(mid):
            right = mid  # True이면 범위 좁히기
        else:
            left = mid + 1
    return left
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [입국심사](https://programmers.co.kr/learn/courses/30/lessons/43238) | Level 3 | 파라메트릭 서치 | [ ] |
| [징검다리](https://programmers.co.kr/learn/courses/30/lessons/43236) | Level 4 | 파라메트릭 서치 | [ ] |
| [가장 긴 팰린드롬](https://programmers.co.kr/learn/courses/30/lessons/12904) | Level 3 | 이진 탐색 응용 | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [이분 탐색](https://www.acmicpc.net/problem/1920) | Silver | 기본 이진 탐색 | [ ] |
| [나무 자르기](https://www.acmicpc.net/problem/2805) | Silver | 파라메트릭 서치 | [ ] |
| [랜선 자르기](https://www.acmicpc.net/problem/1654) | Silver | 파라메트릭 서치 | [ ] |
| [공유기 설치](https://www.acmicpc.net/problem/2110) | Gold | 파라메트릭 서치 | [ ] |
| [K번째 수](https://www.acmicpc.net/problem/1300) | Gold | 이진 탐색 심화 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Binary Search](https://leetcode.com/problems/binary-search/) | Easy | 기본 이진 탐색 | [ ] |
| [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) | Medium | 변형 이진 탐색 | [ ] |
| [Find First and Last Position](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) | Medium | lower/upper bound | [ ] |
| [Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) | Medium | 파라메트릭 서치 | [ ] |
| [Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/) | Hard | 이진 탐색 응용 | [ ] |

---

## ✅ 진행 상황

- [ ] 기본 이진 탐색 구현 숙지
- [ ] Lower/Upper Bound 구현 숙지
- [ ] 파라메트릭 서치 개념 학습
- [ ] `bisect` 모듈 활용 학습
- [ ] 프로그래머스 추천 문제 3개 완료
- [ ] 백준 추천 문제 5개 완료
- [ ] LeetCode 추천 문제 5개 완료
- [ ] 복습 완료 (1주 후)
