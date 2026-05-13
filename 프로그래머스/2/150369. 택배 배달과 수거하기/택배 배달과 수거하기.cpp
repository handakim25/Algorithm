#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// # Parameter
// - n : 집의 개수
// -- i 번째 집의 거리는 i
// cap : 트럭에 실을 수 있는 상자의 최대 개수
// 집 마다 배달을 하거나 회수를 해야 한다.
// # Result
// - 모든 배달, 수거 완료 후 원점 복귀할 때 최소 거리
// # Idea
// ## Brute Force
// result가 long long인 것을 봤을 때 완전 탐색은 불가능
// ## Greedy
// 문제를 간단하게 변형해서 배달만 한다면 이는 Greedy를 통해서 해결 할 수 있다.
// 가장 먼 거리부터 배달하는 것이 아니라 중간에 다른 경로를 선택하게 될 경우 언젠가 배달해야 하는 최대 거리를 중복으로 이동하게 되어서 거리가 증가하게 된다.
// 이를 다시 원래의 문제로 돌아가게 된다면 배달과 수거를 할 경우 어떠한 선택이 Greedy인지를 결정해야 한다.
// 배달 / 수거는 항상 끝부터 실행할 수 있다.
// 배달이 가장 멀 경우 돌아오면서 수거를 실행할 수 있고 수거가 가장 멀 경우 이동 중에 배달을 하고 수거를 실행할 수 있다.
// 즉, 한 번 출발할 경우 결정론적으로 다음 상황을 결정할 수 있다.
// ### Modeling
// - long long인 것을 볼 때 단순하게 순회를 할 경우 time complexity를 초과할 수 있다.
// 문제를 다시 한 번 간략화하자.
// 배달만을 하는 것을 고려한다면 한 번 배달을 할 때 최대 거리를 갱신하면서 진행을 하면 된다.
// 단순하게 생각하면 last element부터 index가 거리가 되고 last element를 capacity만큼 갱신을 하면서 진행하면 된다.
// O(n)의 알고리즘이 성립
// 이를 배달과 수거를 하게 된다면 매 라운드마다 배달과 수거를 진행하고 더 큰 거리가 해당 Round의 거리가 된다.
// 이 때 끝점을 기록하게 되면 매 번 시작점을 찾지 않아도 된다.

// # 문제
// 1. index 0 집까지의 거리는 1이므로 거리를 제대로 처리하지 못하고 있다.
// 2. index 0까지 0으로 처리하는 것이 필요하다.
// - distance 결과값에서 +1을 해서 처리
// - index 조건이 i >= 0으로 처리
// -- >= 0일 경우 다음 값 갱신 시에 -1이 되므로 값 조건에서 벗어나게 되고 종료된다.
// |- -1이 last index가 되는 것과 같다.

using namespace std;

int find_last_index(const vector<int>& arr);
int update_array(vector<int>& arr, int capacity, int index);

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    long long result = 0;
    
    int deliver_index = find_last_index(deliveries);
    int pickup_index = find_last_index(pickups);
    
    while(deliver_index >= 0 || pickup_index >= 0) {
        // fix2. 결과값을 명시적으로 표기
        int farthest = max(deliver_index, pickup_index);
        result += (long long)(farthest + 1) * 2;
        
        deliver_index = update_array(deliveries, cap, deliver_index);
        pickup_index = update_array(pickups, cap, pickup_index);
    }
    
    return result;
}

int find_last_index(const vector<int>& arr) {
    int index = arr.size() - 1;
    while(index >= 0 && arr[index] == 0) {
        index--;
    }
    
    return index;
}

int update_array(vector<int>& arr, int capacity, int index) {
    while(capacity > 0 && index >= 0) {
        // arr[index]--;
        // capacity--;
        // fix1. capacity를 한 번에 줄이는 것이 가능하다.
        int count = min(arr[index], capacity);
        arr[index] -= count;
        capacity -= count;
        
        
        while(index >= 0 && arr[index] == 0) {
            index--;
        }
    }
    
    return index;
}