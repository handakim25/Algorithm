"""
이진 탐색 (Binary Search) 템플릿
=================================
- 기본 이진 탐색
- Lower Bound / Upper Bound
- 파라메트릭 서치
"""

import sys
from bisect import bisect_left, bisect_right
input = sys.stdin.readline


# ============================================================
# 1. 기본 이진 탐색
# ============================================================
def binary_search(arr, target):
    """정렬된 배열에서 target의 인덱스 반환, 없으면 -1"""
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


# ============================================================
# 2. Lower Bound - target 이상인 첫 번째 위치
# ============================================================
def lower_bound(arr, target):
    """arr[result] >= target을 만족하는 최소 인덱스"""
    left, right = 0, len(arr)
    while left < right:
        mid = (left + right) // 2
        if arr[mid] < target:
            left = mid + 1
        else:
            right = mid
    return left
    # bisect_left(arr, target) 과 동일


# ============================================================
# 3. Upper Bound - target 초과인 첫 번째 위치
# ============================================================
def upper_bound(arr, target):
    """arr[result] > target을 만족하는 최소 인덱스"""
    left, right = 0, len(arr)
    while left < right:
        mid = (left + right) // 2
        if arr[mid] <= target:
            left = mid + 1
        else:
            right = mid
    return left
    # bisect_right(arr, target) 과 동일


# ============================================================
# 4. 파라메트릭 서치 - 최솟값 찾기
#    "condition(mid)이 True인 최솟값"
#    단조성: False, False, ..., True, True, ...
# ============================================================
def parametric_search_min(lo, hi, condition):
    """
    condition(x)가 True인 x의 최솟값 반환
    lo: 탐색 범위 하한
    hi: 탐색 범위 상한
    """
    while lo < hi:
        mid = (lo + hi) // 2
        if condition(mid):
            hi = mid
        else:
            lo = mid + 1
    return lo


# ============================================================
# 5. 파라메트릭 서치 - 최댓값 찾기
#    "condition(mid)이 True인 최댓값"
#    단조성: True, True, ..., False, False, ...
# ============================================================
def parametric_search_max(lo, hi, condition):
    """
    condition(x)가 True인 x의 최댓값 반환
    """
    while lo < hi:
        mid = (lo + hi + 1) // 2  # 올림 (무한 루프 방지)
        if condition(mid):
            lo = mid
        else:
            hi = mid - 1
    return lo


# ============================================================
# 사용 예시
# ============================================================
if __name__ == "__main__":
    # 기본 이진 탐색 예시
    arr = [1, 3, 5, 7, 9, 11]
    print(binary_search(arr, 7))   # 3
    print(binary_search(arr, 6))   # -1

    # Lower/Upper Bound 예시
    arr = [1, 2, 2, 3, 3, 3, 4]
    print(lower_bound(arr, 3))     # 3 (3이 처음 등장하는 인덱스)
    print(upper_bound(arr, 3))     # 6 (3 다음의 인덱스)

    # 파라메트릭 서치 예시: 나무 자르기
    # heights = [20, 15, 10, 17], 필요한 나무 = 7
    # 최대 높이 H를 구하라
    heights = [20, 15, 10, 17]
    need = 7

    def can_cut(h):
        return sum(max(0, x - h) for x in heights) >= need

    # condition이 True인 최댓값 = H의 최댓값
    result = parametric_search_max(0, max(heights), can_cut)
    print(result)  # 15
