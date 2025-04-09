#include <iostream>
#include <vector>

// 예제
// M : 10, N : 12
// 1  : 1, 1
// 2  : 2, 2
// 3  : 3, 3
// 4  : 4, 4
// 5  : 5, 5
// 6  : 6, 6
// 7  : 7, 7
// 8  : 8, 8
// 9  : 9, 9
// 10 : 10 , 10
// 11 : 1, 11
// 12 : 2, 12
// 13 : 3, 1
// ...
// 60 : 10, 12
// 60이 가장 마지막인 이유는 10, 12의 최소 공배수이기 때문이라 생각한다.
// 그리고 x, y는 어차피 서로 상관 없이 n번째에 결정되기 때문에 따로 계산하면 된다.

// 일단은 n번째를 찾아가는데 시간 초과가 발생햇다.
// n번째를 찾아가고 각각이 독립적으로 계산이 될 경우 이진 탐색을 이용할 수 있다.
// 문제는 왼쪽, 오른쪽을 판별해야 된다는 점이다.
// 지금보니까 바로 n번째 구할 수 있겠는데?
// 어차피 x가 고정이 되면 다음 y를 계산할 수가 있네
// m == 3일 경우
// 3, 13, 23, 33, 43, 53을 검사하면 된다.

using namespace std;

int calculate_n_th(int m, int n, int x, int y);
pair<int, int> get_n_th(int n_th, int m, int n);
int gcd(int m, int n);
int lcm(int m, int n);

int main() {
    int test_case_count = 0;
    cin >> test_case_count;

    for(int i = 0; i < test_case_count; i++) {
        int m, n, x, y;
        cin >> m >> n >> x >> y;
        cout << calculate_n_th(m, n, x, y);
        cout << endl;
    }
    
    return 0;
}

int calculate_n_th(int m, int n, int x, int y) {
    int max_element_count = lcm(m, n);
    int n_th = x;
    while(n_th <= max_element_count) {
        pair<int, int> element = get_n_th(n_th, m, n);
        if(element.first == x && element.second == y) {
            return n_th;
        }
        n_th += m;
    }

    return -1;
}

int gcd(int m, int n) {
    while(n != 0) {
        int r = m % n;
        m = n;
        n = r;
    }

    return m;
}

int lcm(int m, int n) {
    return m * n / gcd(m, n);
}

pair<int, int> get_n_th(int n_th, int m, int n) {
    int x = (n_th - 1) % m + 1;
    int y = (n_th - 1) % n + 1;
    return {x, y};
}
