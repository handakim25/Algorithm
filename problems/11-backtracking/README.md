# 11. 백트래킹 (Backtracking)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

백트래킹은 가능한 모든 경우의 수를 탐색하되, **가지치기(Pruning)**를 통해 불필요한 탐색을 제거하는 기법입니다.

### 핵심 개념
- **완전 탐색**보다 효율적 (가지치기)
- DFS 기반 탐색
- **선택 → 탐색 → 취소** 패턴

### 적용 유형
1. **순열**: 모든 순서 조합
2. **조합**: 순서 없는 선택
3. **부분집합**: 포함/미포함
4. **N-Queen**: 제약 조건 하의 배치
5. **스도쿠**: 제약 조건 충족

---

## 💡 핵심 패턴 및 템플릿

### 기본 백트래킹 템플릿
```python
def backtrack(state, choices):
    # 기저 조건 (목표 달성)
    if is_goal(state):
        process_solution(state)
        return
    
    for choice in choices:
        if is_valid(state, choice):
            # 선택
            make_choice(state, choice)
            # 탐색
            backtrack(state, next_choices(choices, choice))
            # 취소
            undo_choice(state, choice)
```

### 순열 생성
```python
def permutations(nums):
    result = []
    def backtrack(path, remaining):
        if not remaining:
            result.append(path[:])
            return
        for i, num in enumerate(remaining):
            path.append(num)
            backtrack(path, remaining[:i] + remaining[i+1:])
            path.pop()
    backtrack([], nums)
    return result
```

### 조합 생성
```python
def combinations(nums, k):
    result = []
    def backtrack(start, path):
        if len(path) == k:
            result.append(path[:])
            return
        for i in range(start, len(nums)):
            path.append(nums[i])
            backtrack(i + 1, path)
            path.pop()
    backtrack(0, [])
    return result
```

### N-Queen
```python
def solve_n_queens(n):
    result = []
    cols = set()
    diag1 = set()  # row - col
    diag2 = set()  # row + col
    
    def backtrack(row, queens):
        if row == n:
            result.append(queens[:])
            return
        for col in range(n):
            if col in cols or (row - col) in diag1 or (row + col) in diag2:
                continue
            cols.add(col)
            diag1.add(row - col)
            diag2.add(row + col)
            queens.append(col)
            backtrack(row + 1, queens)
            queens.pop()
            cols.remove(col)
            diag1.remove(row - col)
            diag2.remove(row + col)
    
    backtrack(0, [])
    return result
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [N-Queen](https://programmers.co.kr/learn/courses/30/lessons/12952) | Level 2 | 백트래킹 | [ ] |
| [피로도](https://programmers.co.kr/learn/courses/30/lessons/87946) | Level 2 | 순열 + 백트래킹 | [ ] |
| [전력망을 둘로 나누기](https://programmers.co.kr/learn/courses/30/lessons/86971) | Level 2 | DFS + 완전 탐색 | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [N-Queen](https://www.acmicpc.net/problem/9663) | Gold | 백트래킹 | [ ] |
| [N과 M (1)](https://www.acmicpc.net/problem/15649) | Silver | 순열 백트래킹 | [ ] |
| [N과 M (2)](https://www.acmicpc.net/problem/15650) | Silver | 조합 백트래킹 | [ ] |
| [스도쿠](https://www.acmicpc.net/problem/2580) | Gold | 백트래킹 | [ ] |
| [암호 만들기](https://www.acmicpc.net/problem/1759) | Gold | 조합 + 제약 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Subsets](https://leetcode.com/problems/subsets/) | Medium | 부분집합 | [ ] |
| [Permutations](https://leetcode.com/problems/permutations/) | Medium | 순열 | [ ] |
| [Combination Sum](https://leetcode.com/problems/combination-sum/) | Medium | 조합 + 재사용 | [ ] |
| [N-Queens](https://leetcode.com/problems/n-queens/) | Hard | N-Queen | [ ] |
| [Word Search](https://leetcode.com/problems/word-search/) | Medium | 그리드 백트래킹 | [ ] |

---

## ✅ 진행 상황

- [ ] 백트래킹 기본 템플릿 이해
- [ ] 순열/조합/부분집합 구현 숙지
- [ ] 가지치기 최적화 기법 학습
- [ ] N-Queen 구현
- [ ] 프로그래머스 추천 문제 3개 완료
- [ ] 백준 추천 문제 5개 완료
- [ ] LeetCode 추천 문제 5개 완료
- [ ] 복습 완료 (1주 후)
