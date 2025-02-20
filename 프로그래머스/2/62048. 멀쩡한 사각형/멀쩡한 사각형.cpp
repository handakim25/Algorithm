#include <iostream>
#include <cmath>

using namespace std;

// 높이와 넓이로 인해서 직선이 정의된다.
// 문제에서 주의해야 할 점은 부동소수점 오류로 잘못된 값을 건드렸을 경우이다.
// 일정한 기울기에서 작동하므로 구간을 잡으면 동일한 값들을 제외할 수 있을 것 같다.
// 가령 예제로 보면 높이 3, 밑변 2의 직선이 반복이 되는 구조이다.
// 이는 최소 공약수를 이용해서 구할 수 있을 것이다.
// 내부의 점을 세는 경우도 고려를 해야 한다.
// 더 이상 쪼갤 수 없는 직선으로 쪼개면 완벽하게 점을 통과할 수 없어서 일괄적으로 계산을 할 수 있을 것 같다.

// 이러한 접근의 장점은 지나가는 직선은 정수 지점을 지나가지 않기 때문에 부동 소수점 오차를 해결할 수 있다.
// 하지만 실수를 최대한 사용 안 한다고 해도 일단은 실수 영역을 건드릴 수 밖에 없다.

// Graph는 굳이 y절편이 존재하는 함수가 아니라 원점을 지나는 선으로 나타낼 수 있다.
// 그러하면 그래프의 함수식은 h x - w y = 0, y = h x / w
// 잘리는 종이의 개수는 y값을 비교하면 된다.
// 예시의 x = 1, x = 2일 때의 y값을 비교하게 되면
// y1 = 10.xxx, y2 = 9, 이전 값에 ceil, 이후 값에 floor를 하게 되면
// 11, 9 -> 11 - 9 = 2의 종이가 잘린다.

// 첫번째 시도 이후에 float을 double로 교체하니까 점수가 올랐다.
// 이를 토대로 유추하건데 이는 부동 소수점 오차 이슈이다.
// 일단은 최대한 소수점 부분을 제거하도록 노력한다.

int gcd(int a, int b);
long long calculate_square_counts(int w, int h);

long long solution(int w,int h) {
    int gcd_value = gcd(w, h);
    int w_trim = w / gcd_value;
    int h_trim = h / gcd_value;
    long long removed = calculate_square_counts(w_trim, h_trim);
    long long total = (long long)w * h;
    
    return total - removed * gcd_value;
}

int gcd(int a, int b) {
    while(b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    
    return a;
}

// w >= 1, h >= 1
// y = (h / w) * x
// floor(y_i), ceil(y_i_1)
long long calculate_square_counts(int w, int h) {
    long long count = 0;
    // 수정1. 부동 소수점 오차가 있기 때문에 최대한 정수를 사용한다.
    int prev_y = 0;

    // To-Do : i == w일 때 ceil 오류 수정
    for(int i = 1; i < w; i++) {
        // 수정1. 정수 연산은 ceil이 기본이고 정확한 정수를 지나가지 않으므로 무조건 + 1을 하는 것으로 ceil을 수행 가능
        int y_i = (h * i) / w;
        // 수정1. 현재 값은 ceil을 해야 되고 이전 값은 floor를 해야한다.
        int square_count = (y_i + 1) - prev_y;
        count += square_count;
                
        prev_y = y_i;
    }
    
    // 수정2
    // 마지막 점은 정수를 지나기 때문에 올림 처리를 할 때 + 1을 하지 않아야 한다.
    int y_w = h;
    count += y_w - prev_y;
    
    return count;
}