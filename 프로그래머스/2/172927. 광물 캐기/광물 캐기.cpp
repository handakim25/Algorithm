#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

// 아이디어1. 경우의 수가 적으니까 모든 경우를 다 셀 수 있지 않을까?
// 그리고 결국은 뒤의 값을 알 수가 없으니까 현재 시점에서의 값을 확인할 수가 없다.
// 곡괭이를 그러면 다 모으고 이거를 나열하면 될 것 같다.

using namespace std;

vector<int> permuate_pick(const vector<int>& picks);
int calculate_cost(const vector<int>& pick_permutation, const vector<string>& minerals);
int pick_cost(string mineral, int pick);

int solution(vector<int> picks, vector<string> minerals) {
    vector<int> pick_permutation = permuate_pick(picks);
    sort(pick_permutation.begin(), pick_permutation.end());
    
    int min_cost = numeric_limits<int>::max();
    do {
        int cost = calculate_cost(pick_permutation, minerals);
        min_cost = min(min_cost, cost);
    }while(next_permutation(pick_permutation.begin(), pick_permutation.end()));
    
    return min_cost;
}

vector<int> permuate_pick(const vector<int>& picks) {
    vector<int> pick_permutation;
    
    // picks[0] == 0, picks[1] == 1, picks[2] == 2, diamond, iron, stone
    for(int i = 0; i < picks.size(); i++) {
        pick_permutation.insert(pick_permutation.end(), picks[i], i);
    }
    
    return pick_permutation;
}

int calculate_cost(const vector<int>& pick_permutation, const vector<string>& minerals) {
    int cost = 0;
    // 0~4 : pick_permutation[0]
    // 5~9 : pick_permutation[1]
    // ...
    
    // fix1: 최대 범위를 미리 계산한다. for 안의 루프를 매번 계산하지 않고 안의 루프를 간결하게 유지한다.
    int max_index = min(minerals.size(), pick_permutation.size() * 5);
    for(int i = 0; i < max_index; i++) {
        int pick_index = i / 5;
        cost += pick_cost(minerals[i], pick_permutation[pick_index]);
    }
    
    return cost;
}

int pick_cost(string mineral, int pick) {
    // key : mineral, value : pick cost
    static std::unordered_map<string, vector<int>> mineral_pick_cost_map = {
        {"diamond", {1, 5, 25}},
        {"iron", {1, 1, 5}},
        {"stone", {1, 1, 1,}},
    };
    return mineral_pick_cost_map[mineral][pick];
}