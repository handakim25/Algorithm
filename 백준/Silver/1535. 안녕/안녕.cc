#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 전형적인 탐욕법 문제라고 생각한다.
// i 번째를 포함했을 때 최대를 구하면 된다.
// 이전 값들을 기준으로 해야되니까 이중 배열을 쓰거나 아니면 체력을 기준으로 최적화를 할 수 있다.
// 복잡도를 생각하고 입력의 크기를 고려했을 때 체력을 기준으로 작성하면 금방 끝날 것으로 판단한다.
// 체력을 기준으로 해도 결국은 체력이 정해져야 되는데 이럴 경우는 이차원 탐욕법을 사용하면 해결할 수 있을 것 같다.
// F(remain health, n번째) : 
// 아니면 완전탐색? 백트랙킹을 이용해서 해결할 수 있을 것 같은데
// current health, i번째를 이용해서 해결 할 수 있을 것 같다.
void calculate_max_value(int i, int current_health, int joy, const vector<int>& cost, const vector<int>& gain, int& out_max_joy);

int main() {
    int n;
    cin >> n;
    vector<int> cost(n);
    for(int i = 0; i < n; i++) {
        cin >> cost[i];
    }
    vector<int> gain(n);
    for(int i = 0; i < n; i++) {
        cin >> gain[i];
    }

    int max_joy = 0;
    calculate_max_value(0, 100, 0, cost, gain, max_joy);
    cout << max_joy;
    
    return 0;
}

// i : 0, 1, ... n - 1
// pre condition : i - 1번째까지 처리되고 i번째를 처리해야 됨
void calculate_max_value(int i, int current_health, int joy, const vector<int>& cost, const vector<int>& gain, int& out_max_joy) {
    if(i == cost.size()) {
        out_max_joy = max(out_max_joy, joy);
        return;
    }

    if(current_health - cost[i] > 0) {
        calculate_max_value(i + 1, current_health - cost[i], joy + gain[i], cost, gain, out_max_joy);
    }
    calculate_max_value(i + 1, current_health, joy, cost, gain, out_max_joy);
}