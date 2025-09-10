#include <string>
#include <vector>
#include <iostream>

// 정수 5개의 조합으로 이루어지고 오름차순으로 정렬되어 있다. 정수 5개가 정해지면 그 순서는 하나로 유일하다.
// 입력한 정수를 받아서 몇 개의 정답이 있는지 파악할 수 있다.
// 또한, 입력의 개수가 10개 정도이므로 완전 탐색으로 문제를 해결할 수 있다.

// n : 정수 조합을 결정할 정수 개수
// m : m번 시도
// q : 입력을 시도한 2차원 배열
// q[i] : i번째 시도
// and[i] : i번째 시도 정답

// 가장 간단한 경우의 수는 모든 경우의 수를 생성하는 것이다.
// 모든 경우의 수를 생성하는 경우의 수는 최대 n인 30에서 5개를 선택하는 경우의 수이다.
// 30C5이고 이를 근사해서 계산하면 30^5 / 5가 되어서 4860000가 된다.
// 이는 500만의 경우의 수가 되고 이를 m개(10개)와 비교하게 되면 5000만 루프가 된다.

// 다른 방법으로는 각각의 정답을 기준으로 정답 개수 만큼 선택하고 이를 조합하는 방식이다.
// 다만, 이는 공통 조합을 찾는 것이 필요하다.

using namespace std;

int count_all_combinations(vector<int>& nums, int current, int num, const vector<vector<int>>& q, const vector<int>& ans);
bool is_met_condition(const vector<int>& nums, const vector<vector<int>>& q, const vector<int>& ans);
int count_intersection(const vector<int>& arrA, const vector<int>& arrB);

int solution(int n, vector<vector<int>> q, vector<int> ans) {
    vector<int> nums;
    return count_all_combinations(nums, 1, n, q, ans);
}

int count_all_combinations(vector<int>& nums, int current, int num, const vector<vector<int>>& q, const vector<int>& ans) {
    // base case: 5개까지 카운트
    if(nums.size() == 5) {
        return is_met_condition(nums, q, ans) ? 1 : 0;
    }
    if(current > num) {
        return 0;
    } 
    
    // current를 선택
    nums.push_back(current);
    int select_current = count_all_combinations(nums, current + 1, num, q, ans);
    nums.pop_back();
    
    // current를 선택하지 않음
    int not_select_current = count_all_combinations(nums, current + 1, num, q, ans);
    
    return select_current + not_select_current;
}

bool is_met_condition(const vector<int>& nums, const vector<vector<int>>& q, const vector<int>& ans) {
    for(int i = 0; i < q.size(); i++) {
        const int intersection_count = count_intersection(nums, q[i]);
        if(intersection_count != ans[i]) {
            return false;
        }
    }
    
    return true;
}

int count_intersection(const vector<int>& arrA, const vector<int>& arrB) {
    int i = 0, j = 0, count = 0;
    
    while(i < arrA.size() && j < arrB.size()) {
        if(arrA[i] == arrB[j]) {
            count++;
            i++;
            j++;
        }else if(arrA[i] < arrB[j]) {
            i++;
        }else {
            j++;
        }
    }
    
    return count;
}