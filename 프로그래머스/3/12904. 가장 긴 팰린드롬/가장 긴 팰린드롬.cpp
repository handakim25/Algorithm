#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 아이디어
// 1. Substring의 나열이니까 이를 가지치기 하면 원하는 결과를 낼 수도 있을 것 같다.
// 2. 판단할 때 회문은 다른 회문의 부분 집합이므로 동적 계획법 형식으로 이용할 수도 있을 것 같다.
// - 문제는 어떻게 순회를 할지, 어떤식으로 부분 문제로 나눌 수 있을지에 관한 문제이다.
// 회문은 이후의 문자열도 확인을 해야하므로 단순하게 n번째까지의 상태로 표현할 수 없다.
// 따라서 F(i, j)를 정의하고 2차원 동적 계획법이 필요할 것 같다.
// F(i - 1, j + 1) = when F(i, j) is true and arr[i] == arr[j] 이런 느낌일듯?
// i - 1을 n번째라고 가정하고 현재 루프에서 step을 정해서 확인을 하면 가능할 것 같다. 문제는 O(n^2긴 한데 이 부분은 더 찾아봐야 할 듯 하다.)

int solution(string s)
{
    // dp 초기값 설정
    // 길이가 1인 경우는 회문이다.
    int len = s.length();
    vector<vector<bool>> dp(len, vector<bool>(len, false));
    for(int i = 0; i < len; i++) {
        dp[i][i] = true;
    }

    int longest = 1;
    
    // step 1일 경우 예외 처리(길이 2인 문자열)
    for(int i = 0; i < len - 1; i++) {
        if(s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            longest = 2;
        }
    }
    
    for(int step = 2; step < len; step++) {
        // [i, i + step] 회문 체크, [i + 1, i + step - 1]이 회문이고 i, i + step이 같아야 한다.
        // bounday check, step이 1일 경우 : dp[i + 1, i]라서 순서가 반전이 된다. step이 1일 경우에만 발생하니까 이것도 선조건으로 처리해야 한다.
        // 일단은 여기서 왜 Boundary 체크를 1을 실행했는지에 대해서 기록을 하자면
        // 이렇게 i + step - 1 같이 - 1이 되는 부분은 offset 처리에서 주의를 해야 된다.(경험적)
        // 그리고 i + 1, i + step - 1이 로직이 성립이 되는 것은 i + 1이 left, i + step - 1이 right가 되는 구조이고
        // left < right 조건이 코드의 전제조건이다. 퀵 정렬과 같은 상황에서 보면 left < right 조건이 존재하는 것과 같은 의미이다.
        // 즉, i + 1 < i + step - 1이 항상 성립해야 되고 이를 수식으로 표현하면
        // 2 < step 이어야 한다는 뜻이 된다.
        for(int i = 0; i + step < len; i++) {
            if(dp[i + 1][i + step - 1] && (s[i] == s[i + step])) {
                dp[i][i + step] = true;
                longest = step + 1;
            }
        }
    }
    
    return longest;
}