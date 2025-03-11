#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

// r1, r2는 원의 방정식을 통해서 내부의 점을 구할 수 있다.
// 사분면은 대칭이므로 한 사분면만 구하고 이를 이용해서 전체 정점 개수를 확인 가능하다.
// 주의해야 할 점은 부동 소수점 오차이다.
// x^2 + y^2 <= r^2 의 범위 안에서 최대한 값들을 유지하도록 한다.
// 제곱 연산이 있으면 주의해야 할 점은 int 범위를 초과할 수 있는 것이다. 현재도 21억 범위를 넘어서는 것을 봐서는 long long을 이용해야 할 필요가 있다.

long long solution(int r1, int r2) {
    long long count = 0;
    // i = 0인 지점을 나누어서 풀이해야 한다.
    // 생각해보니 i == 0인 지점을 나누어서 풀다보면 y == 0인 지점을 예외처리해 버려야 한다.
    // 하지만, i == 0인 지점을 배제하고 수식을 풀면 1사분면과 y == 0인 지점이 포함되고
    // 이는 순수 사분면과 축 위의 점들을 하나 포함하게 되어서 * 4를 하면 전체 쌍을 구할 수 있다.
    
    for(int i = 1; i <= r2; i++) {
        // x * x + y * y <= r * r
        // y = sqrt(r * r - x * x);
        long long y2 = floor(sqrt((long long)r2 * r2 - (long long)i * i)); // 안의 점을 구해야 하니까 floor
        long long y1 = ceil(sqrt((long long)r1 * r1 - (long long)i * i)); // 밖의 점을 구해야 하니까 ceil
        count += y2 - y1 + 1; // 개수를 구하는 것이니까 +1
    }
    
    return count * 4;
}