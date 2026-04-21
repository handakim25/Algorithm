#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

// Solution
// 모든 경우의 수를 확인해야 하므로 이 문제는 완전탐색이다.
// 이 문제의 경우 일정 금액 이상을 넘어가면 경우의 수를 만족할 수 없으므로 가지치기가 성립한다.
// 따라서 이 문제의 유형은 백트랙킹이다.

// Idea
// 모든 경우의 수를 카운팅할 때 가장 큰 동전부터 탐색하면 경우의 수를 줄일 수 있다.

// 문제1. 효율성 테스트 실패
// 나머지를 통해서 값을 반환하는 경우가 존재한다는 것은 함수 스택이 그 정도로 존재한다는 것이다.
// 더 효율적인 방법으로 가지치기를 성립시킬 수는 없으므로 완전 탐색을 통해서 풀이할 수 없다.

// Idea
// 금액 n에 대해서 최적의 값을 구하는 것이다. n을 다른 금액의 조합을 이용해서 정의할 경우 이는 dp를 통해서 풀이할 수 있다.

// dp[0] = 1
// dp[1] = 1 (1)
// dp[2] = 2 (1 + 1, 2)
// dp[3] = 2 (1 + 1 + 1, 2 + 1)
// dp[4] = 3 (1 + 1 + 1 + 1, 2 + 1 + 1, 2 + 2)
// dp[5] = 4 (1 + 1 + 1 + 1, 2 + 1 + 1 + 1, 2 + 2 + 1, 5)

// 문제2
// dp[n] += dp[n - coin]을 할 때 동전의 개수를 그대로 더하면 중복된 수를 더하게 된다.
// 가령, dp[4]에서 dp[4 - 1] + dp[4- 2]를 한다고 가정하자ㅏ.
// dp[3]에서 1 + 1 + 1, 2 + 1 이 들어오고
// dp[2]에서 1 + 1, 2 가 들어오게 되는데 이는 dp[3]이 dp[2]와 동일한 경로를 통해서 오게 된다.
// 이는 subproblem을 제대로 분리하지 못한 것이 문제이다.

// dp[3]이 dp[2]를 통해서만 재정의 되고 있다.(1 + 1 -> 1 + 1 + 1, 2 -> 2 + 1)
// 동전의 사용 순서가 반영이 되어야 한다.
// dp[i][j]를 통해서 i번째까지의 동전을 통해서 j원을 만들어서 이전 상황에서의 동전 조합을 강제한다.
// dp[i][j] = dp[i - 1][j] + dp[i][j - coin]
// 그러니까 2, 2, 1과 2, 1, 2를 서로 같게 카운팅이 되도록 한다.

using namespace std;

const int MOD = 1000000007;

// int combinations(int target, int index, vector<int>& combs, int sum, vector<int>& money);

int solution(int n, vector<int> money) {
     // 1. back tracking solution : 시간 초과
//     sort(money.begin(), money.end(), greater<int>());
//     vector<int> combs(money.size());
    
//     int result = combinations(n, 0, combs, 0, money);
//     return result;
   
    // 2. dp : 1차원 배열을 이용했을 때는 중복을 카운팅하는 문제가 있다.
//     vector<int> dp(n + 1);
//     dp[0] = 1;
    
//     for(int i = 1; i <= n; i++) {
//         for(int j = 0; j < money.size(); j++) {
//             int coin = money[j];
//             if(i - coin >= 0) {
//                 dp[i] += dp[i - coin];
//             }
//         }
//     }
    
//     return dp[n];
    // 3. 2차원 dp
    // dp[i][j] : i개의 동전을 통해 j원을 만드는 조합
    // 결과값 dp[m][n] 형식을 위해서 index-1으로 구성
    int m = money.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // 초기값 설정
    for(int i = 0; i <= m; i++) {
        dp[i][0] = 1;
    }
    
    // dp[i][j] = dp[i - 1][j] + dp[i][j - coin]
    for(int i = 1; i <= m; i++) {
        int coin = money[i - 1];
        
        for(int j = 0; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            
            // 현재 coin을 사용할 수 있을 경우
            if(j >= coin) {
                dp[i][j] = (dp[i][j] + dp[i][j - coin]) % MOD;
            }
        }
    }
    
    return dp[m][n];
}

// int combinations(int target, int index, vector<int>& combs, int sum, vector<int>& money) {
//     if(sum == target) {
//         return 1;
//     }
//     if(index >= money.size()) {
//         return 0;
//     }

//     int coin = money[index];
    
//     // 1. 현재 동전으로 가장 큰 수를 구함 : largest
//     int largest = (target - sum) / coin;
    
//     // for i : 0 - largest를 대입하고 처리
//     int combination_count = 0;
//     for(int i = 0; i <= largest; i++) {
//         combs[index] = i;
//         int next_sum = sum + coin * i;
        
//         // combinations의 결과는 이미 MOD되어 있기 때문에 MOD를 다시 적용할 필요가 없다.
//         int count_from_subtree = combinations(target, index + 1, combs, next_sum, money);
//         combination_count = (combination_count + count_from_subtree) % MOD;
//     }
    
//     return combination_count;
// }
