# 10. 그리디 (Greedy)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

그리디 알고리즘은 매 순간 **지역적으로 최적인 선택**을 하여 전체 최적해를 구하는 방법입니다.

### 그리디 적용 조건
1. **탐욕적 선택 속성**: 지역 최적 선택이 전체 최적해에 포함됨
2. **최적 부분 구조**: 전체 문제의 최적해가 하위 문제의 최적해로 구성됨

### DP vs 그리디
| | 그리디 | DP |
|--|-------|-----|
| 접근 | 지역 최적 | 전체 최적 |
| 속도 | 보통 빠름 | 보통 느림 |
| 정확성 | 특정 조건 필요 | 항상 최적 |
| 난이도 | 증명이 어려움 | 점화식이 어려움 |

---

## 💡 핵심 패턴 및 템플릿

### 활동 선택 문제 (Interval Scheduling)
```python
def activity_selection(intervals):
    """종료 시간 기준 정렬 후 겹치지 않는 최대 활동 수 선택"""
    intervals.sort(key=lambda x: x[1])
    count = 0
    last_end = -1
    for start, end in intervals:
        if start >= last_end:
            count += 1
            last_end = end
    return count
```

### 거스름돈 문제
```python
def make_change(coins, amount):
    """큰 동전부터 사용 (동전이 배수 관계일 때만 그리디 가능)"""
    coins.sort(reverse=True)
    count = 0
    for coin in coins:
        count += amount // coin
        amount %= coin
    return count if amount == 0 else -1
```

### 허프만 코딩 패턴 (최소 비용 연결)
```python
import heapq

def huffman_cost(arr):
    """최소 비용으로 모든 원소 합치기"""
    heapq.heapify(arr)
    total_cost = 0
    while len(arr) > 1:
        a = heapq.heappop(arr)
        b = heapq.heappop(arr)
        cost = a + b
        total_cost += cost
        heapq.heappush(arr, cost)
    return total_cost
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [체육복](https://programmers.co.kr/learn/courses/30/lessons/42862) | Level 1 | 그리디 | [ ] |
| [조이스틱](https://programmers.co.kr/learn/courses/30/lessons/42860) | Level 2 | 그리디 | [ ] |
| [큰 수 만들기](https://programmers.co.kr/learn/courses/30/lessons/42883) | Level 2 | 그리디 + 스택 | [ ] |
| [구명보트](https://programmers.co.kr/learn/courses/30/lessons/42885) | Level 2 | 그리디 + 투 포인터 | [ ] |
| [섬 연결하기](https://programmers.co.kr/learn/courses/30/lessons/42861) | Level 3 | 그리디 + MST | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [회의실 배정](https://www.acmicpc.net/problem/1931) | Silver | 활동 선택 | [ ] |
| [거스름돈](https://www.acmicpc.net/problem/5585) | Bronze | 그리디 | [ ] |
| [주유소](https://www.acmicpc.net/problem/13305) | Silver | 그리디 | [ ] |
| [강의실 배정](https://www.acmicpc.net/problem/11000) | Gold | 그리디 + 힙 | [ ] |
| [행렬](https://www.acmicpc.net/problem/1080) | Silver | 그리디 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Assign Cookies](https://leetcode.com/problems/assign-cookies/) | Easy | 그리디 | [ ] |
| [Jump Game](https://leetcode.com/problems/jump-game/) | Medium | 그리디 | [ ] |
| [Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/) | Medium | 활동 선택 | [ ] |
| [Gas Station](https://leetcode.com/problems/gas-station/) | Medium | 그리디 | [ ] |
| [Task Scheduler](https://leetcode.com/problems/task-scheduler/) | Medium | 그리디 + 힙 | [ ] |

---

## ✅ 진행 상황

- [ ] 그리디 적용 조건 이해 (탐욕적 선택 속성)
- [ ] 활동 선택 문제 패턴 학습
- [ ] 구간 스케줄링 문제 패턴 학습
- [ ] 그리디 증명 방법 학습 (교환 논증)
- [ ] 프로그래머스 추천 문제 5개 완료
- [ ] 백준 추천 문제 5개 완료
- [ ] LeetCode 추천 문제 5개 완료
- [ ] 복습 완료 (1주 후)
