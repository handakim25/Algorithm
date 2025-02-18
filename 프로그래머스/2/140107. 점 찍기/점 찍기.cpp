#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

// 해당 문제를 수식으로 표현하면 다음과 같다.
// ak * ak + bk * bk <= d * d
// (a^2 + b^2) * k^2 <= d ^2
// a ^ 2 + b ^ 2 <= k ^ 2 / d ^ 2
// 따라서 반지름이 d / k인 원 내부의 사분원에서의 점의 개수이다.
// k = 2, d = 4인 상황이라면 반지름이 2인 내부의 점이고
// (0, 2), (0, 1), (0, 0), (1, 1), (1, 0), (2, 0) 6개가 된다.

// 내부의 점의 개수를 파악한다고 하면 임의의 x = a에서 y ^ 2 = r ^ 2 - a ^ 2
// y = sqrt(r ^ 2 - a ^ 2)가 되고 해당 정점에서 가장 큰 정수값이 y의 가능값이다.
// 이 때 x의 값의 범위는 0~r의 범위가 된다.

// sqrt를 이용했으나 오차 이슈로 오답이 된 것으로 추정한다.
// sqrt를 이용하지 않을 경우는 점을 대입해서 확인해 나가면 된다.
// y의 범위를 생각하면 0~r의 범위가 되고 x가 증가하게 되면 항상 y의 값은 감소하게 된다.
// 따라서 이전 i에서의 r 값을 이용해서 그 부분부터 확인하면 된다.

// 문제점 : r의 범위를 정수로 단순하게 치환해서 쓸 수가 없다.
// 이는 원이 실제로 더 클 경우 다음 원에서 max_y의 계산에서 실질적으로 더 클 수도 있기 때문이다.
// 따라서 d, k를 나누어서 계산하는 것이 아니다.
// 다시 이 문제는 원래의 문제로 돌아가서 기존의 풀이로 계산하게 된다.
// a * a * k * k + b * b * k * k <= d * d

bool is_in_circle(long long x, long long y, long long d, long long k);

long long solution(int k, int d) {
    long long count = 0;
    
    // d / k : 축소된 원의 반지름
    long long max_y =  d / k;
    for(int i = 0; i <= d / k; i++) { // d / k는 항상 d 보다 작으므로 int 범위이다.
        // until max_y is not in range.
        while(!is_in_circle(i, max_y, d, k) && max_y >= 0) {
            max_y--;
        }
        
        count += (max_y + 1); // (x, 0)의 점도 포함해야 한다.
    }
    
    return count;
}

bool is_in_circle(long long x, long long y, long long d, long long k) {
    return (x * x + y * y) * k * k <= d * d;
}