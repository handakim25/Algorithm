#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

// 블록을 설치할 때 뒤에 것이 덮어씌워지는 구조이다.
// 딱히 생각나는 부분이 없는데 일단은 브루트 포스로 구하기로 한다.
// 브루트 포스를 사용할 경우 몇 번 블럭까지 설치해야 하는지를 구해야 한다.
// 1-base
// 0, 1, 1, 2, 1, 3, 1, 2, 3, 2
// 1은 2번
// 2는 4번
// 3은 6번에 나타난다.
// 따라서 begin / 2번까지 고려하면 된다.
// 홀수가 될 경우는?
// 5의 경우 4가 마지막 갱신 대상이다.
// 다시 생각해보니까 begin을 고려할 것이 아니라 end까지를 고려해야 한다.
// n번 블럭 저장
// begin / n = quotient -> n * (quotient + 1, 2, 3...)을 고려

// 숫자의 개수가 더 한정적이다. 문제 파악할 때 숫자가 더 적은 것을 파악하지 못햇다.
// 이러한 문제를 풀 때는 항상 변수들의 범위를 명시적으로 파악하는 절차를 추가하도록 한다.

using namespace std;

vector<int> solution(long long begin, long long end) {
    int last_block = end / 2;
    // Fix: Block은 10000000보다 커질 수 없으므로 조건 추가
    last_block = min(last_block,  10000000);
    vector<int> range(end - begin + 1, 0);
    for(long long i = 1; i <= last_block; i++) {
        long long start = (begin + i - 1) / i;
        start = max(start, 2LL);

        for(long long j = start; i * j <= end; j++) {
            long long prod = i * j;
            if(prod >= begin) {
                range[prod - begin] = max(range[prod - begin], (int)i);
            }
        }
    }
    
    
    
    return range;
}