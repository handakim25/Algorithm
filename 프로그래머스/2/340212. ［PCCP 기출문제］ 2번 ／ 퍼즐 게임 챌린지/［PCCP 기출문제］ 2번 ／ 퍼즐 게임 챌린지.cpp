#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 최소 시간을 구하는 문제이고 문제가 부분 문제로 정의되지 않을 경우 이진 탐색을 고려할 수 있다.
// 이진 탐색에서 문제를 해결할 때는 O(n) 정도로 풀릴 경우 탐색이 O(logN)이 되므로 O(n Log N) 복작도로 해결할 수 있다.
// diff : 난이도
// time_cur : 현재 퍼즐 소요 시간 
// time_prev : 이전 퍼즐 소요 시간 
// level : 숙련도
// limit : 제한 시간

// 시간 소모
// diff <= level : time
// diff > level : (total prev time) * (diff - level)

// Boundary 결정 : 최대 숙련도를 계산하면 가장 높은 난이도가 최대 숙련도로 할 수 있다.

long long solve_time(int level, const vector<int>& diffs, const vector<int>& times);

int solution(vector<int> diffs, vector<int> times, long long limit) {
    // Boundary 결정
    int low = 1;
    int high = 100000;
    
    while(low <= high) {
        int mid = low + (high - low) / 2;
        
        if(solve_time(mid, diffs, times) <= limit) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    
    return low;
}

long long solve_time(int level, const vector<int>& diffs, const vector<int>& times) {
    long long total_time = 0;
    long long prev_time = 0;
    
    for(int i = 0; i < diffs.size(); i++) {
        if(diffs[i] <= level) {
            total_time += times[i];
        }
        else {
            // fix: 공식을 잘못 이해했다. 실질적으로 예제를 확인해봤어야 했는데 검증 과정이 부족했다.
            // fix2: 횟수 * value 구조가 이해하기 쉽다. diffs[i] - level을 앞으로 변경
            total_time += (diffs[i] -level) * (prev_time + times[i]) + times[i];
        }
        prev_time = times[i];
    }
    return total_time;
}