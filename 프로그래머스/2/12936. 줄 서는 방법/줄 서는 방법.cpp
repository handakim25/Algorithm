#include <string>
#include <vector>
#include <iostream>

// n : 5, k = 67 예시 다시 생각해 볼 것

using namespace std;

// n : 사람의  수
// long long k : k번째 방법, 경우의 수를 셀 때 long long을 사용할 것.

// long long이 주어진 것을 봤을 때 brute force를 이용해서 풀이하기에는 힘들어 보인다.
// 사전식 정렬에서 [a, b, c, d]일 경우 [b, c, d]와 같이 3개를 나열할 수 있는 방법(==6)을 한 번에 뛰어넘길 수 있다.
// 이를 재귀 혹은 반복으로 사용한다면 대략적인 위치를 파악할 수 있다.
// 가령 3, 1, 2가 있다면 몇 번째인지 역으로 가정하면 1, 2를 지나갔으므로 4개가 앞에 있고 1, 2는 첫번째이므로 1이 되서 5가 된다.
// 아무튼 이 과정의 역과정인데 앞에서 숫자 몇개를 썼는지를 알아야 숫자를 확정 지을 수 있다.
// 일단은 재귀로 한 번 풀어보기로 한다.

// 생각해보니까 이러한 나열은 백트랙킹 부분과 동일하다.
// 나열을 할 때 pruning을 통해서 가지를 치는 것과 동일하다.
// 백트랙킹을 생각해보면 재귀를 이용해서 푸는 것이 맞다고 생각한다.

// 이거 생각해보니까 매 번 문제가 작은 문제로 선택이 되는 것이 아닌가 생각이 드네
// 가령, 처음은 [1, 2, 3]에서 2!씩 넘기면 이 중에서 3번째 것을 선택하는 것이고
// 그 다음 문제도 [1, 2] 중에서 1!씩 넘기면서 이 중에서 1번째 것을 선택하는 것이고
// 같은 문제가 재귀적으로 풀이되는 상황이라서 반복문 보다는 일단은 재귀쪽이 조금 더 괜찮아 보인다.

// 반례 : 4, 24 -> [4, 3, 2, 1], [1, 2, 3, 4]으로 오답
// 로직의 처음 설계부터 전제가 잘못됬었다.
// 가령, 6개씩 넘겨서 24개가 됬다면 마지막 숫자를 선택해야 한다.
// 즉, 24개를 선택할려면 23개를 넘겨서 24번째의 값을 선택하면 된다.
// 이 문제는 문제의 이해를 충분히 못했던 것이 실패라고 생각한다.
// 예제를 차라리 작은 범위에서 모든 경우의 수를 나열했던 것이 더 좋은 접근이 됬을 것 같다.

// DecideNumber가 호출될 때마다 가장 앞 자리 수가 갱신된다.
// remains가 있으니까 현재 개수가 필요 없다.
void DecideNumber(long long k, vector<int>& remains, vector<int>& result);
long long factorial(long long num);

// 문제 풀이 전략 수정
// 무작정 코드에 달려들지 말고 문제를 풀고 코드를 작성하자.
// 한 단계, 한 단계 반복하면 충분히 문제를 풀이할 수 있다.

vector<int> solution(int n, long long k) {
    // 남아 있는 숫자
    vector<int> nums(n);
    for(int i = 0; i < n; i++) {
        nums[i] = i + 1;
    }
    
    vector<int> result;
    DecideNumber(k, nums, result);
    
    return result;
}

void DecideNumber(long long k, vector<int>& remains, vector<int>& result) {
    // 모든 숫자를 선택했으면 반환한다.
    if(remains.size() == 0) {
        return;
    }
    
    int n = remains.size();
    long long skip = factorial(n - 1);
    
    // Fix1. k번째를 선택해야 하니까 k - 1개를 넘기고 k번째를 선택한다.
    long long skip_count = (k - 1) / skip;
    long long remain_k = (k - 1) % skip + 1; // k -1개를 skip하고 k번째를 선택하니까 +1을 해야한다.
    
    // 로직이 정확해지니까 코드도 간결하게 된다.
    // 배열은 0-base이니까 skip_count번째를 고르면 현재 가능한 숫자이다.
    result.push_back(remains[skip_count]);
    remains.erase(remains.begin() + skip_count);
    
    DecideNumber(remain_k, remains, result);
}

long long factorial(long long n) {
    if(n == 1 || n == 2) {
        return n;
    }
    else if(n <= 0) {
        return 1;
    }
    return n * factorial(n - 1);
}