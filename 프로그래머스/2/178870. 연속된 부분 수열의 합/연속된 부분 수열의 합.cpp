#include <string>
#include <vector>

// 아이디어1 : 부분 수열의 합은 대표적인 투포인터 알고리즘이다.
// - start, end가 존재
// - end를 증가시키고 합이 k 보다 클 경우 start를 증가시켜 배열을 감소시킨다.
// - k를 만족시키는 경우의 수가 나올 경우 그 때의 최소 길이를 기록

// sequence : 배열
// k : 부분 수열의 합

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