# 🚀 Algorithm Learning Management System

> 프로그래머스 Level 3 수준의 중급 알고리즘 학습자를 위한 체계적 학습 관리 시스템

이 저장소는 [BaekjoonHub](https://github.com/BaekjoonHub/BaekjoonHub)를 통한 백준 자동 푸시와 함께, 체계적인 알고리즘 학습 관리를 위한 시스템을 포함합니다.

---

## 📋 목차 (Table of Contents)

1. [학습 시간 가이드](#-학습-시간-가이드)
2. [문제당 권장 시간](#-문제당-권장-시간)
3. [알고리즘 15개 분야](#-알고리즘-15개-분야)
4. [단계별 로드맵](#-단계별-로드맵-3-6개월)
5. [저장소 구조](#-저장소-구조)
6. [중급자 맞춤 설정](#-중급자level-3-맞춤-설정)
7. [대회 및 성취도](#-대회-및-성취도)

---

## ⏰ 학습 시간 가이드

### 일일 권장 학습 시간: **2-3시간**

| 시간 구성 | 비율 | 내용 |
|----------|------|------|
| 개념 학습 | 20% | 새 알고리즘 개념 이해 |
| 새 문제 풀이 | 50% | 실전 문제 도전 |
| 복습 & 정리 | 20% | 이전 문제 재풀이 |
| 코드 리뷰 | 10% | 더 나은 풀이 탐색 |

### 주간 스케줄 (중급자 기준)
```
평일 (월-금): 매일 2-3시간
  - 새 문제 2-3개
  - 복습 1개

주말 (토-일): 매일 3-4시간
  - 주말 Contest 참여 (2시간)
  - Contest 문제 복습 (1시간)
  - 자유 문제 풀이 (1시간)
```

---

## ⏱️ 문제당 권장 시간

| 난이도 | 권장 시간 | 기준 |
|--------|---------|------|
| **Easy** | 10-20분 | 프로그래머스 Level 1-2, LeetCode Easy |
| **Medium** | 30-45분 | 프로그래머스 Level 3, LeetCode Medium |
| **Hard** | 60-90분 | 프로그래머스 Level 4-5, LeetCode Hard |

### 🎯 30분 룰
1. **30분** 고민 후 진전 없으면 → 힌트 확인
2. **1시간** 후에도 막히면 → 솔루션 일부 참고
3. 풀이 후 반드시 → 다른 방법 탐색 및 복습 일정 등록

---

## 📊 알고리즘 15개 분야

### 1️⃣ 기초 단계 (필수)
| # | 분야 | 핵심 개념 | 학습 우선순위 |
|---|------|---------|------------|
| 01 | [배열 & 문자열](problems/01-array-string/) | 투 포인터, 슬라이딩 윈도우 | ⭐⭐⭐⭐⭐ |
| 02 | [해시테이블](problems/02-hash-table/) | HashMap, HashSet | ⭐⭐⭐⭐⭐ |
| 03 | [스택 & 큐](problems/03-stack-queue/) | LIFO, FIFO, 모노토닉 스택 | ⭐⭐⭐⭐⭐ |

### 2️⃣ 중급 단계
| # | 분야 | 핵심 개념 | 학습 우선순위 |
|---|------|---------|------------|
| 04 | [정렬](problems/04-sorting/) | 퀵소트, 머지소트, 커스텀 정렬 | ⭐⭐⭐⭐ |
| 05 | [이진 탐색](problems/05-binary-search/) | 파라메트릭 서치, lower/upper bound | ⭐⭐⭐⭐ |
| 06 | [재귀](problems/06-recursion/) | 메모이제이션, 백트래킹 기초 | ⭐⭐⭐⭐ |
| 07 | [트리](problems/07-tree/) | BST, 세그먼트 트리, LCA | ⭐⭐⭐⭐ |
| 08 | [그래프 기초](problems/08-graph-basics/) | DFS, BFS, 인접 리스트 | ⭐⭐⭐⭐⭐ |

### 3️⃣ 고급 단계
| # | 분야 | 핵심 개념 | 학습 우선순위 |
|---|------|---------|------------|
| 09 | [동적 프로그래밍](problems/09-dynamic-programming/) | Top-down, Bottom-up, 최적 부분 구조 | ⭐⭐⭐⭐⭐ |
| 10 | [그리디](problems/10-greedy/) | 탐욕적 선택 속성, 교환 논증 | ⭐⭐⭐⭐ |
| 11 | [백트래킹](problems/11-backtracking/) | 가지치기, 순열/조합/부분집합 | ⭐⭐⭐⭐ |
| 12 | [그래프 심화](problems/12-graph-advanced/) | 최단경로, MST, 위상정렬 | ⭐⭐⭐⭐⭐ |
| 13 | [분할 정복](problems/13-divide-conquer/) | 병합 정렬, 거듭제곱, 카라츠바 | ⭐⭐⭐ |

### 4️⃣ 심화 단계
| # | 분야 | 핵심 개념 | 학습 우선순위 |
|---|------|---------|------------|
| 14 | [고급 자료구조](problems/14-advanced-datastructures/) | 세그먼트 트리, 펜윅 트리, 트라이 | ⭐⭐⭐ |
| 15 | [수학 & 기하](problems/15-math-geometry/) | 정수론, 조합론, 기하 | ⭐⭐⭐ |

---

## 🗺️ 단계별 로드맵 (3-6개월)

### Phase 1: 기초 강화 (1-2개월)
```
Week 1-2  : 배열, 문자열, 해시테이블 심화
Week 3-4  : 스택, 큐, 정렬
Week 5-6  : 이진 탐색, 재귀
Week 7-8  : 트리 기초, BST

목표: 프로그래머스 Level 3 전체 통과율 70% 이상
문제 비율: Medium 70% + Hard 30%
```

### Phase 2: 핵심 알고리즘 (2-3개월)
```
Week 9-11 : 그래프 (DFS/BFS) 심화
Week 12-15: 동적 프로그래밍 (DP)
Week 16-18: 그리디, 백트래킹

목표: 백준 골드 3-5, LeetCode Medium 안정적 풀이
문제 비율: Medium 60% + Hard 40%
```

### Phase 3: 심화 학습 (1-2개월)
```
Week 19-22: 그래프 심화 (최단경로, MST, 위상정렬)
Week 23-26: 고급 자료구조, 수학

목표: 백준 플래티넘 진입, 주간 콘테스트 상위 30%
문제 비율: Medium 40% + Hard 60%
```

---

## 📁 저장소 구조

```
Algorithm/
├── README.md                    # 학습 가이드 (현재 파일)
├── problems/                    # 알고리즘 분야별 문제 풀이
│   ├── 01-array-string/
│   ├── 02-hash-table/
│   ├── 03-stack-queue/
│   ├── 04-sorting/
│   ├── 05-binary-search/
│   ├── 06-recursion/
│   ├── 07-tree/
│   ├── 08-graph-basics/
│   ├── 09-dynamic-programming/
│   ├── 10-greedy/
│   ├── 11-backtracking/
│   ├── 12-graph-advanced/
│   ├── 13-divide-conquer/
│   ├── 14-advanced-datastructures/
│   └── 15-math-geometry/
├── contests/                    # 대회 참여 기록
│   ├── programmers/
│   ├── baekjoon/
│   ├── leetcode/
│   ├── codeforces/
│   └── atcoder/
├── logs/                        # 학습 기록
│   ├── daily/
│   ├── weekly/
│   └── monthly/
├── templates/                   # 알고리즘 코드 템플릿
└── review/                      # 복습 시스템
    ├── mistakes/
    └── revisit/
```

---

## 🎯 중급자(Level 3) 맞춤 설정

### 플랫폼별 목표
| 플랫폼 | 현재 수준 | 목표 | 문제 비율 |
|--------|---------|------|---------|
| **프로그래머스** | Level 3 일부 | Level 3 완전 정복 + Level 4 도전 | Level 3 70% + Level 4 30% |
| **백준** | - | 골드 3-5 | 골드 문제 중심 |
| **LeetCode** | - | Contest Rating 1600+ | Medium 70% + Hard 30% |

### 우선 학습 분야
1. 🔥 **동적 프로그래밍** - Level 3의 핵심
2. 🔥 **그래프 심화** - 다익스트라, 플로이드, MST
3. 🔥 **이진 탐색** - 파라메트릭 서치
4. ⚡ **백트래킹** - 가지치기 최적화
5. ⚡ **세그먼트 트리** - 구간 쿼리

---

## 🏆 대회 및 성취도

자세한 내용은 [contests/README.md](contests/README.md)를 참고하세요.

### 주요 대회 일정
| 대회 | 주기 | 추천 여부 |
|------|------|---------|
| AtCoder ABC | 주 1회 | ⭐ 강력 추천 |
| Codeforces Div.2 | 주 2-3회 | ⭐ 추천 |
| 프로그래머스 코딩테스트 | 비정기 | 취업 대비 |
| 백준 온라인 저지 | 상시 | 일일 문제 |

---

## 📝 학습 기록

- 📅 [일일 학습 기록](logs/daily/)
- 📊 [주간 회고](logs/weekly/)
- 🎯 [월간 목표](logs/monthly/)
- 🔄 [복습 시스템](review/)

---

*마지막 업데이트: 2026년 4월*
