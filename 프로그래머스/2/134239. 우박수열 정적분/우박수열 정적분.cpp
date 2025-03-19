#include <string>
#include <vector>
#include <iostream>

using namespace std;

// k : 초항 -> 수열을 생성해 낼 수 있다.
// f(0) : x는 0일 때, f(1) : x는 1일 때, ...
// ranges
// 0, 0 : 전체 구간
// 1, -2 : [1, 3]

// 정적분 계산
// [xn, xn+1]의 범위에서 f(xn) = a, f(xn+1) = b일 경우 정적분 결과는 a + b / 2가 된다.
// 이를 일반화하면 [xa, xb]일 경우 [f(xa) + f(xa + 1) + f(xa + 1) + f(xa + 1 + 1) + f(xa + 1 + 1) +... f(xb)]/ 2

// 우박 순열을 생성, 말항의 경우 1이 된다.
vector<unsigned int> generate_collatz(unsigned int k);
unsigned int next_collatz(unsigned int k);
double calculate_integral(const vector<unsigned int>& collatz, int start, int end);

vector<double> solution(int k, vector<vector<int>> ranges) {
    vector<unsigned int> collatz = generate_collatz(k);
    // fix1. n은 문제 조건에서 n이긴 하지만 그래도 모호한 부분이 있긴 해서 변수명을 last_index로 변경
    size_t last_index = collatz.size() - 1;

    vector<double> result;
    for(const vector<int>& range : ranges) {
        int start = range[0];
        int end = last_index + (size_t)range[1];
        
        // fix : start, end의 조건을 잘못 설정했다.
        // [0, 0]이 되면 모든 범위 정적분이다.
        // 문제를 정확하게 이해를 하지 못해서 생긴 문제이다.
        // 정확히 이해하지 못한 부분에 대해서는 넘어가지 않고 확인하는 습관이 필요하다.
        if(end < start) {
            result.push_back(-1);
            continue;
        }
        
        double integral = calculate_integral(collatz, start, end);
        result.push_back(integral);
    }
    
    return result;
}

vector<unsigned int> generate_collatz(unsigned int k) {
    vector<unsigned int> collatz;
    while(k != 1) {
        collatz.push_back(k);
        k = next_collatz(k);
    }
    collatz.push_back(k); // push 1
    
    return collatz;
}

unsigned int next_collatz(unsigned int k) {
    return k % 2 == 0 ? k / 2 : k * 3 + 1;
}

double calculate_integral(const vector<unsigned int>& collatz, int start, int end) {
    if(start == end) {
        return 0;
    }
    if(end >= collatz.size()) {
        end = collatz.size() - 1;
    }
    
    // fix2. 나중에 빼는 것 보다는 start, end에서의 값을 예외로 분리하고 나머지 부분에 대해서 연산을 하는 것이 의도를 더 잘 나타낸 것 같다.
    // 기존 코드에서의 문제점은 start, end에서의 처리가 특이 케이스란 것을 제대로 보여주지 못 했다.
    double integral = (double)collatz[start] / 2 + (double)collatz[end] / 2;
    for(int i = start + 1; i < end; i++) {
        integral += collatz[i];
    }
    return integral;
}