#include <string>
#include <vector>

// 아이디어1 : 부분 수열의 합은 대표적인 투포인터 알고리즘이다.
// - start, end가 존재
// - end를 증가시키고 합이 k 보다 클 경우 start를 증가시켜 배열을 감소시킨다.
// - k를 만족시키는 경우의 수가 나올 경우 그 때의 최소 길이를 기록

// sequence : 배열
// k : 부분 수열의 합

// while문 경계값 검증 : sum == k일 경우도 start를 증가시켜도 되는가?
// sum == k일 때 start를 증가시키지 않았다고 가정하자.
// 다음 루프에서 end가 증가되고 범위가 증가된다. 따라서 항상 sum > k가 성립하게 되고 반드시 start를 증가시켜야 한다.
// 그러므로 sum == k 인 경우에 미리 start를 증가시켜도 되고 루프는 while(sum >= k)로 처리해도 된다.

using namespace std;

vector<int> solution(vector<int> sequence, int k) {
    int start = 0;
    int sum = 0;
    int min_length = numeric_limits<int>::max();
    // 0-base, 배열 인덱스를 그대로 사용하면 된다. 항상 k를 만족시키는 부분 수열이 존재하므로 초기화 불필요
    pair<int, int> range;
    
    for(int end = 0; end < sequence.size(); end++) {
        sum += sequence[end];
        // start 범위 조정
        while(sum >= k) {
            // k일 때 최소 길이이면 갱신한다.
            if(sum == k && (end - start + 1) < min_length) {
                min_length = end - start + 1;
                range = {start, end};
            }
            sum -= sequence[start++];
        }
    }
    
    return {range.first, range.second};
}