#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

// 어디서부터 시작하던 펄스 수열을 미리 곱해서 최종 계산을 할 수 있다.
// 이렇게 고정을 하게 된다면 연속된 부분 수열의 최대값을 계산하는 문제로 환원할 수 있다.
// 연속된 순열의 경우 i번째까지 구할 경우 최대값을 저장해서 해결할 수 있다.
// i-1까지의 최대값과 i번째 값을 더하거나 아니면 처음부터 구하는 과정을 통해서 max 값을 구할 수 있다.
// 모든 범위에 대해서 한 번만 구하면 되므로 DP를 완전히 활용할 필요 없이 한 번 루프를 순회하면 된다.

using namespace std;


long long find_largest_pulse_value(const vector<int>& sequence, int start_multiply);

long long solution(vector<int> sequence) {
    long long answer_from_negative = find_largest_pulse_value(sequence, -1);
    long long answer_from_positive = find_largest_pulse_value(sequence, 1);
    return max(answer_from_negative, answer_from_positive);
}

long long find_largest_pulse_value(const vector<int>& sequence, int start_multiply) {
    long long max_sequence_sum = numeric_limits<long long>::min();
    long long sequence_sum = 0;
    
    for(int num : sequence) {
        int current_num = num * start_multiply;
        sequence_sum = max(sequence_sum + current_num, (long long)current_num);
        max_sequence_sum = max(max_sequence_sum, sequence_sum);
        start_multiply *= -1; 
    }
    
    return max_sequence_sum;
}