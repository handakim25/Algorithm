# 04. 정렬 (Sorting)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

### 정렬 알고리즘 비교

| 알고리즘 | 평균 | 최악 | 공간 | 안정성 |
|---------|------|------|------|--------|
| 버블 정렬 | O(n²) | O(n²) | O(1) | ✅ |
| 선택 정렬 | O(n²) | O(n²) | O(1) | ❌ |
| 삽입 정렬 | O(n²) | O(n²) | O(1) | ✅ |
| 합병 정렬 | O(n log n) | O(n log n) | O(n) | ✅ |
| 퀵 정렬 | O(n log n) | O(n²) | O(log n) | ❌ |
| 힙 정렬 | O(n log n) | O(n log n) | O(1) | ❌ |
| 계수 정렬 | O(n+k) | O(n+k) | O(k) | ✅ |

### 심화 개념
- **커스텀 정렬**: 특정 기준으로 정렬 (다중 키, 역정렬)
- **안정 정렬**: 동일 키의 순서 보장 여부
- **부분 정렬**: 상위 k개만 정렬 (힙 활용)
- **외부 정렬**: 메모리보다 큰 데이터 정렬 (합병 정렬 활용)

---

## 💡 핵심 패턴 및 템플릿

### 커스텀 정렬 (Python)
```python
# 단일 키 정렬
arr.sort(key=lambda x: x[1])

# 다중 키 정렬 (첫 번째 오름차순, 두 번째 내림차순)
arr.sort(key=lambda x: (x[0], -x[1]))

# 문자열 길이로 정렬
arr.sort(key=len)

# functools.cmp_to_key 활용 (복잡한 비교)
from functools import cmp_to_key

def compare(a, b):
    if a + b > b + a:
        return -1
    return 1

arr.sort(key=cmp_to_key(compare))
```

### 합병 정렬 (직접 구현)
```python
def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    return merge(left, right)

def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result
```

### 힙을 이용한 상위 k개
```python
import heapq

def top_k(arr, k):
    # 최소 힙으로 k개 유지
    heap = []
    for num in arr:
        heapq.heappush(heap, num)
        if len(heap) > k:
            heapq.heappop(heap)
    return sorted(heap, reverse=True)
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [K번째수](https://programmers.co.kr/learn/courses/30/lessons/42748) | Level 1 | 배열 슬라이싱 + 정렬 | [ ] |
| [가장 큰 수](https://programmers.co.kr/learn/courses/30/lessons/42746) | Level 2 | 커스텀 정렬 | [ ] |
| [H-Index](https://programmers.co.kr/learn/courses/30/lessons/42747) | Level 2 | 정렬 + 이진탐색 | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [수 정렬하기 2](https://www.acmicpc.net/problem/2751) | Silver | 합병/힙 정렬 | [ ] |
| [좌표 정렬하기](https://www.acmicpc.net/problem/11650) | Silver | 다중 키 정렬 | [ ] |
| [나이순 정렬](https://www.acmicpc.net/problem/10814) | Silver | 안정 정렬 | [ ] |
| [버블 소트](https://www.acmicpc.net/problem/1517) | Gold | 병합 정렬 (역전 수) | [ ] |
| [수 정렬하기 3](https://www.acmicpc.net/problem/10989) | Bronze | 계수 정렬 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Sort Colors](https://leetcode.com/problems/sort-colors/) | Medium | 3-way 파티션 | [ ] |
| [Largest Number](https://leetcode.com/problems/largest-number/) | Medium | 커스텀 정렬 | [ ] |
| [Merge Intervals](https://leetcode.com/problems/merge-intervals/) | Medium | 정렬 후 병합 | [ ] |
| [Kth Largest Element](https://leetcode.com/problems/kth-largest-element-in-an-array/) | Medium | 퀵셀렉트/힙 | [ ] |

---

## ✅ 진행 상황

- [ ] 주요 정렬 알고리즘 시간/공간 복잡도 이해
- [ ] Python sort/sorted 커스텀 키 숙지
- [ ] 합병 정렬 직접 구현
- [ ] 역전 수 계산 (병합 정렬 응용) 학습
- [ ] 프로그래머스 추천 문제 3개 완료
- [ ] 백준 추천 문제 5개 완료
- [ ] LeetCode 추천 문제 4개 완료
- [ ] 복습 완료 (1주 후)
