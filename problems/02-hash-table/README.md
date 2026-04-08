# 02. 해시테이블 (Hash Table)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

해시테이블은 키-값 쌍을 저장하며, 해시 함수를 이용해 O(1) 평균 시간에 검색/삽입/삭제가 가능한 자료구조입니다.

### 핵심 특성
- **평균 시간 복잡도**: 삽입/삭제/탐색 모두 O(1)
- **최악 시간 복잡도**: O(n) (해시 충돌 시)
- **공간 복잡도**: O(n)

### 활용 상황
1. **빈도 수 계산**: 문자/단어의 등장 횟수 카운팅
2. **중복 탐지**: 이미 방문/처리한 요소 확인
3. **두 합 문제**: 목표값 - 현재값의 존재 여부 확인
4. **그룹핑**: 애너그램, 같은 특성을 가진 원소 묶기
5. **캐싱**: 메모이제이션

---

## 💡 핵심 패턴 및 템플릿

### 빈도 수 계산
```python
from collections import Counter

def count_frequency(arr):
    # Counter 활용
    freq = Counter(arr)
    
    # 직접 구현
    freq_manual = {}
    for item in arr:
        freq_manual[item] = freq_manual.get(item, 0) + 1
    
    return freq
```

### 두 합 (Two Sum)
```python
def two_sum(nums, target):
    seen = {}
    for i, num in enumerate(nums):
        complement = target - num
        if complement in seen:
            return [seen[complement], i]
        seen[num] = i
    return []
```

### 애너그램 그룹핑
```python
from collections import defaultdict

def group_anagrams(strs):
    groups = defaultdict(list)
    for s in strs:
        key = tuple(sorted(s))
        groups[key].append(s)
    return list(groups.values())
```

### 슬라이딩 윈도우 + 해시
```python
def longest_substring_without_repeating(s):
    char_index = {}
    max_len = 0
    left = 0
    for right, char in enumerate(s):
        if char in char_index and char_index[char] >= left:
            left = char_index[char] + 1
        char_index[char] = right
        max_len = max(max_len, right - left + 1)
    return max_len
```

---

## 📝 추천 문제 리스트

### 프로그래머스
| 문제 | 레벨 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [완주하지 못한 선수](https://programmers.co.kr/learn/courses/30/lessons/42576) | Level 1 | 해시맵 | [ ] |
| [전화번호 목록](https://programmers.co.kr/learn/courses/30/lessons/42577) | Level 2 | 해시셋 | [ ] |
| [위장](https://programmers.co.kr/learn/courses/30/lessons/42578) | Level 2 | 해시맵 카운팅 | [ ] |
| [베스트앨범](https://programmers.co.kr/learn/courses/30/lessons/42579) | Level 3 | 해시맵 정렬 | [ ] |

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [나는야 포켓몬 마스터 이다솜](https://www.acmicpc.net/problem/1620) | Silver | 해시맵 | [ ] |
| [수 찾기](https://www.acmicpc.net/problem/1920) | Silver | 해시셋 | [ ] |
| [두 수의 합](https://www.acmicpc.net/problem/3273) | Silver | 해시셋 | [ ] |
| [소수&팰린드롬](https://www.acmicpc.net/problem/1747) | Gold | 해시셋 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Two Sum](https://leetcode.com/problems/two-sum/) | Easy | 해시맵 | [ ] |
| [Valid Anagram](https://leetcode.com/problems/valid-anagram/) | Easy | 해시맵 | [ ] |
| [Group Anagrams](https://leetcode.com/problems/group-anagrams/) | Medium | 해시맵 그룹핑 | [ ] |
| [Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) | Medium | 해시맵 + 정렬 | [ ] |
| [LRU Cache](https://leetcode.com/problems/lru-cache/) | Medium | 해시맵 + 연결리스트 | [ ] |

---

## ✅ 진행 상황

- [ ] 해시테이블 기본 개념 학습
- [ ] Python dict/Counter/defaultdict 숙지
- [ ] 빈도 수 계산 패턴 학습
- [ ] 투 포인터 + 해시 조합 학습
- [ ] 프로그래머스 추천 문제 4개 완료
- [ ] 백준 추천 문제 4개 완료
- [ ] LeetCode 추천 문제 5개 완료
- [ ] 복습 완료 (1주 후)
