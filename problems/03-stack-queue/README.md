# 03. 스택 & 큐 (Stack & Queue)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

### 스택 (Stack)
LIFO(Last In First Out) 구조. 나중에 삽입된 데이터가 먼저 삭제됩니다.

**활용 상황**:
- 괄호 유효성 검사
- 함수 호출 스택 (재귀)
- 모노토닉 스택 (다음 더 큰/작은 원소 찾기)
- 히스토그램에서 가장 큰 직사각형

### 큐 (Queue)
FIFO(First In First Out) 구조. 먼저 삽입된 데이터가 먼저 삭제됩니다.

**활용 상황**:
- BFS (너비 우선 탐색)
- 프로세스 스케줄링
- 슬라이딩 윈도우 최대/최소 (덱 활용)

### 덱 (Deque)
양쪽 끝에서 삽입/삭제가 가능한 자료구조.

### 모노토닉 스택 (Monotonic Stack)
스택에 원소가 단조 증가 또는 단조 감소 순서로 유지되는 스택.

---

## 💡 핵심 패턴 및 템플릿

### 괄호 유효성 검사
```python
def is_valid_brackets(s):
    stack = []
    mapping = {')': '(', '}': '{', ']': '['}
    for char in s:
        if char in mapping:
            top = stack.pop() if stack else '#'
            if mapping[char] != top:
                return False
        else:
            stack.append(char)
    return not stack
```

### 모노토닉 스택 (다음 더 큰 원소)
```python
def next_greater_element(arr):
    n = len(arr)
    result = [-1] * n
    stack = []  # 인덱스를 저장
    for i in range(n):
        while stack and arr[stack[-1]] < arr[i]:
            idx = stack.pop()
            result[idx] = arr[i]
        stack.append(i)
    return result
```

### BFS (큐 활용)
```python
from collections import deque

def bfs(graph, start):
    visited = set([start])
    queue = deque([start])
    result = []
    while queue:
        node = queue.popleft()
        result.append(node)
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    return result
```

### 슬라이딩 윈도우 최대값 (덱)
```python
from collections import deque

def max_sliding_window(nums, k):
    dq = deque()
    result = []
    for i, num in enumerate(nums):
        while dq and nums[dq[-1]] < num:
            dq.pop()
        dq.append(i)
        if dq[0] == i - k:
            dq.popleft()
        if i >= k - 1:
            result.append(nums[dq[0]])
    return result
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [같은 숫자는 싫어](https://programmers.co.kr/learn/courses/30/lessons/12906) | Level 1 | 스택 | [ ] |
| [기능개발](https://programmers.co.kr/learn/courses/30/lessons/42586) | Level 2 | 큐 | [ ] |
| [올바른 괄호](https://programmers.co.kr/learn/courses/30/lessons/12909) | Level 2 | 스택 | [ ] |
| [다리를 지나는 트럭](https://programmers.co.kr/learn/courses/30/lessons/42583) | Level 2 | 큐 시뮬레이션 | [ ] |
| [주식가격](https://programmers.co.kr/learn/courses/30/lessons/42584) | Level 2 | 스택 | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [스택](https://www.acmicpc.net/problem/10828) | Silver | 스택 구현 | [ ] |
| [괄호](https://www.acmicpc.net/problem/9012) | Silver | 괄호 유효성 | [ ] |
| [오큰수](https://www.acmicpc.net/problem/17298) | Gold | 모노토닉 스택 | [ ] |
| [히스토그램에서 가장 큰 직사각형](https://www.acmicpc.net/problem/6549) | Platinum | 모노토닉 스택 | [ ] |
| [카드2](https://www.acmicpc.net/problem/2164) | Silver | 큐 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) | Easy | 스택 | [ ] |
| [Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) | Medium | 모노토닉 스택 | [ ] |
| [Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/) | Easy | 모노토닉 스택 | [ ] |
| [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) | Hard | 모노토닉 스택 | [ ] |
| [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) | Hard | 덱 | [ ] |

---

## ✅ 진행 상황

- [ ] 스택 기본 개념 및 구현 학습
- [ ] 큐/덱 기본 개념 및 구현 학습
- [ ] 모노토닉 스택 패턴 학습
- [ ] BFS 템플릿 숙지
- [ ] 프로그래머스 추천 문제 5개 완료
- [ ] 백준 추천 문제 5개 완료
- [ ] LeetCode 추천 문제 5개 완료
- [ ] 복습 완료 (1주 후)
