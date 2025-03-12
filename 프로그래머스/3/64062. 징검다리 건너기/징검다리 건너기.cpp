#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 문제가 복잡해지므로 다시 풀이한다.
// 일단은 명확한 점은 매 번 한 사람씩 건너게 하면 n^2라서 시간 효율성을 만족시키지 못한다.
// 개선해야 할 부분은 2가지가 있다.
// 첫째는 can traverse를 개선해야 한다. 여기서 한 명씩 건너게 하면서 징검다리를 하나씩 빼 나가는 것은 O(n^2) 로직이 된다.
// 이 부분은 한 번에 n명이 있을 때 건널 수 있는지 없는지로 조건을 제한하면 바꿀 수 있다.
// 근본적으로 이 문제가 이진 탐색이란 것을 인지해야 되는데 이러한 문제는 최대 혹은 최소란 조건이 있다.
// 그리고 각각의 n번째가 기존의 다른 상태와 연관이 없는 상황이다. 즉, 부분 문제로 표현하지 않는다.
// 아무튼 다시 원래대로 돌아가면 can traverse에서 n명이 존재할 때 n명이 건널 수 있는 지를 확인하면 된다.
// 이는 n명에 대해서 디딤돌을 뺐을 때 음수가 되는 즉, 발판이 없어지는 것이 k만큼 벌어지지 않으면 통과 가능이고 벌어지면 통과할 수 없다.
// 이를 계산하는 방법은 연속된 공백의 개수를 세어서 k만큼 떨어지는지 확인하면 된다.
// 두번째 부분은 위에서 말한 것 같이 문제를 이진 탐색로 변형해야 된다. 최대 혹은 최소 문제이고 부분 문제가 없을 경우 이를 이진 탐색을 이용해서 문제를 풀이할 수 있다.
// 이 때 하나의 연산이 O(n)이 된다면 이진 탐색이 O(log N)이 되므로 O(n log N)으로 풀이가 된다.
// 즉, 이진 탐색을 위한 조건은 최대 혹은 최소 그리고 특정 상태 n에서 검증 알고리즘이 O(n) 정도로 풀이되는 알고리즘이 있어야 한다.
// 이진 탐색 범위를 구해야 되는데 범위 자체는 1명부터 징검다리 숫자의 최대값까지이다.

// stones : 디딤돌, n : n명, k : k까지 점프 가능
bool can_traverse(const vector<int> stones, int n, int k);

int solution(vector<int> stones, int k) {
    // 1. 이진 탐색 범위 결정
    int left = 1;
    int right = *max_element(stones.begin(), stones.end());
    
    // 2. 이진 탐색에서의 조건 결정
    // left < right
    // left <= right
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        if(can_traverse(stones, mid, k)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    
    // 3. 이진 탐색에서 결과 값 선정
    return right;
}

bool can_traverse(const vector<int> stones, int n, int k) {
    int zero_count = 0; // 연속된 건널 수 없는 돌의 개수
    for(int stone : stones) {
        // stone - n == 0인 지점까지는 건널 수 있는 것이다. n명이 밟은 순간 발판이 사라지기 때문.
        // 즉, n명이 건너고 그 다음이 건너지 못하는 순간을 찾는 것이다.
        if(stone - n < 0) {
            zero_count++;
        }
        else {
            zero_count = 0;
        }
        
        if(zero_count >= k) return false;
    }
    
    return true;
}