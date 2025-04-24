#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

// 문제 자체는 과속 카메라와 유사한 문제라고 생각한다.
// 과속 카메라 문제는 탐욕법 문제로 풀이를 한다.
// 차이점은 과속 카메라는 폐구간이었고 정수 단위였고 이 문제는 개구간이고 실수 단위이다.
// 하지만, 실수 구간 어디에 있던 같은 상황이므로 이를 고려하면 문제를 단순화할 수 있다.


using namespace std;

int solution(vector<vector<int>> targets) {
    // 종료 시점을 기준으로 정렬한다.
    // 종료 시점을 기준으로 정렬하고 시작점을 확인하면 overlap 되는 모든 Task를 확인할 수 있다.
    sort(targets.begin(), targets.end(), [](const auto& lhs, const auto& rhs) {
        return lhs[1] < rhs[1];
    });
    
    // 알 수 없는 이유로 태스트 케이스 통과가 안 됬다.
    // 개구간이므로 이를 하나 작은 값이라 간주하고 풀이할 수 있을 것이라 생각한다.
    // 시작 구간도 개구간이므로 등호를 붙이지 않는다.
    int intercept = -1;
    int count = 0;
    for(auto& target : targets) {
        int start = target[0];
        int end = target[1];
        
        if(intercept < start) {
            count++;
            intercept = end - 1;
        }
    }
    
    return count;
}