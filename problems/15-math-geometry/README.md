# 15. 수학 & 기하 (Math & Geometry)

## 📋 목차
1. [개념 설명](#-개념-설명)
2. [핵심 패턴 및 템플릿](#-핵심-패턴-및-템플릿)
3. [추천 문제 리스트](#-추천-문제-리스트)
4. [진행 상황](#-진행-상황)

---

## 📚 개념 설명

### 정수론 (Number Theory)
- **소수 판별**: 에라토스테네스의 체 O(n log log n)
- **최대공약수/최소공배수**: 유클리드 호제법 O(log n)
- **모듈러 연산**: 큰 수의 나머지 계산
- **확장 유클리드**: ax + by = gcd(a,b) 해 구하기

### 조합론 (Combinatorics)
- **순열/조합**: nPr, nCr
- **파스칼의 삼각형**: 동적 프로그래밍으로 nCr 계산
- **포함-배제 원리**: 합집합 크기 계산

### 기하 (Geometry)
- **CCW**: 세 점의 방향 판별
- **볼록 껍질**: 그레이엄 스캔 O(n log n)
- **선분 교차**: 두 선분이 교차하는지 판별

---

## 💡 핵심 패턴 및 템플릿

### 소수 관련
```python
# 소수 판별 O(√n)
def is_prime(n):
    if n < 2:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

# 에라토스테네스의 체 O(n log log n)
def sieve(n):
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(n**0.5) + 1):
        if is_prime[i]:
            for j in range(i*i, n+1, i):
                is_prime[j] = False
    return [i for i in range(2, n+1) if is_prime[i]]
```

### GCD/LCM
```python
from math import gcd

def lcm(a, b):
    return a * b // gcd(a, b)

# 확장 유클리드
def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    g, x, y = extended_gcd(b, a % b)
    return g, y, x - (a // b) * y
```

### 조합 (모듈러)
```python
MOD = 10**9 + 7

def combination(n, r, mod=MOD):
    if r > n:
        return 0
    numerator = 1
    denominator = 1
    for i in range(r):
        numerator = numerator * (n - i) % mod
        denominator = denominator * (i + 1) % mod
    return numerator * pow(denominator, mod - 2, mod) % mod  # 페르마 소정리
```

### CCW (Counter-Clock Wise)
```python
def ccw(p1, p2, p3):
    """양수: 반시계, 0: 직선, 음수: 시계"""
    return (p2[0]-p1[0])*(p3[1]-p1[1]) - (p2[1]-p1[1])*(p3[0]-p1[0])

def segments_intersect(p1, p2, p3, p4):
    d1 = ccw(p3, p4, p1)
    d2 = ccw(p3, p4, p2)
    d3 = ccw(p1, p2, p3)
    d4 = ccw(p1, p2, p4)
    if ((d1 > 0 and d2 < 0) or (d1 < 0 and d2 > 0)) and \
       ((d3 > 0 and d4 < 0) or (d3 < 0 and d4 > 0)):
        return True
    return False
```

---

## 📝 추천 문제 리스트

### 백준
| 문제 | 티어 | 핵심 기법 | 완료 |
|------|------|---------|------|
| [소수 구하기](https://www.acmicpc.net/problem/1929) | Silver | 에라토스테네스의 체 | [ ] |
| [최대공약수와 최소공배수](https://www.acmicpc.net/problem/2609) | Bronze | GCD/LCM | [ ] |
| [조합](https://www.acmicpc.net/problem/2407) | Silver | 조합 (큰 수) | [ ] |
| [이항 계수 3](https://www.acmicpc.net/problem/11401) | Gold | 모듈러 역원 | [ ] |
| [선분 교차 2](https://www.acmicpc.net/problem/17387) | Gold | CCW | [ ] |
| [볼록 껍질](https://www.acmicpc.net/problem/1708) | Platinum | 그레이엄 스캔 | [ ] |

### LeetCode
| 문제 | 난이도 | 핵심 기법 | 완료 |
|------|--------|---------|------|
| [Count Primes](https://leetcode.com/problems/count-primes/) | Medium | 에라토스테네스의 체 | [ ] |
| [Ugly Number II](https://leetcode.com/problems/ugly-number-ii/) | Medium | 수학 + DP | [ ] |
| [Happy Number](https://leetcode.com/problems/happy-number/) | Easy | 수학 | [ ] |
| [Sqrt(x)](https://leetcode.com/problems/sqrtx/) | Easy | 이진 탐색 | [ ] |

---

## ✅ 진행 상황

- [ ] 소수 판별 / 에라토스테네스의 체 구현
- [ ] GCD/LCM (유클리드 호제법) 구현
- [ ] 모듈러 연산 및 모듈러 역원 학습
- [ ] 조합론 (nCr mod p) 구현
- [ ] CCW 구현 및 선분 교차 판별
- [ ] 백준 추천 문제 6개 완료
- [ ] LeetCode 추천 문제 4개 완료
- [ ] 복습 완료 (1주 후)
