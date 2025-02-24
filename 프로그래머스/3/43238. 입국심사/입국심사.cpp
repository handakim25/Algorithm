#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <numeric>

// 접근 자체는 항상 비어있는 것을 고르는 탐욕법이다. 항상 가장 짧은 것을 고른다면 그것은 우선순위 큐를 이용할 수도 있다.
// 탐욕법을 이용해서 해결하려고 했는데 기다리는 것을 고려하지 못했다.
// 그러면 기다리는 것까지 고려해서 로직을 우선순위 큐를 만들 필요가 있다.

// 여전히 고민되는 것은 시간을 진행할려면 n번 진행하게 된다는 것이고 그러면 연산이 많다는 것이다.
// 그러면 문제 카테고리인 이분탐색에 포커스를 맞춰서 문제 풀이를 변환할 필요가 있다.
// 처음에는 동적 계획법에서 n 시간에서 몇 명을 처리할 수 있는지를 생각했다.
// 문제는 그래도 여전히 많은 루프가 필요한 것이고 그렇다하면 이를 확장하게 된다면 n 시간 자체를 이진 탐색으로 찾는 것이 가능하다는 것이다.

// 일단 로직 자체는 타당하다고 생각해. 문제는 어떨 때 이러한 로직을 적용할 수 있는지를 정확히 모르겠다는 것이다. 이를 좀 더 검증하자면,
// 1. 이진 탐색 문제라면 일단 범위가 존재한다. 여기서는 left, right가 있고 이것을 이용해 찾는 것이다.
// 2. n에서의 처리 가능 인원을 구할 때 이를 동적 계획법 등으로 이전 상태에서 구하기 어려우나 n에서의 값을 새로 구하는 것이 쉬울 경우 즉, 하위 문제로 쪼개서 푸는 것이 더 어려울 경우 이진 탐색으로 범위를 찾아서 풀이가 가능하다.

using namespace std;

long long get_availables(long long time, const vector<int>& times);

long long solution(int n, vector<int> times) {
    auto max_iter = max_element(times.begin(), times.end());
    long long left = 0;
    long long right = (long long)(*max_iter) * n;
    
    while(left <= right) {
        long long mid = left + (right - left) / 2;
        long long availables = get_availables(mid, times);
        // 현재 처리 가능 인원이 더 많으므로 상한을 줄인다.
        if(availables >= n) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    
    // left가 허용 가능 최소 시간이므로 left를 반환한다.
    return left;
}

long long get_availables(long long time, const vector<int>& times) {
    return accumulate(times.begin(), times.end(), 0LL, [time](long long x, long long y) {
        return x +  time / y;
    });
}