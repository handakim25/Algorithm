#include <string>
#include <vector>

using namespace std;

// 가장 큰 원판을 3번으로 옮기기 위해서는 n - 1개의 원판을 전부 2로 옮기고 n번째를 3으로 옮기면 해결이 가능하다.
// 이를 반복적으로 생각하면 n - 1개의 원판을 전부 2로 옮긴 것을 같은 방식으로 n - 2개를 다시 1로 옮기고 n - 1번째를 3으로 쌓으면 될 것 같다.
// 점화식적으로 생각해보면 F(n + 1) = 2 * F(n) + 1, (An을 2로 한 번, 3으로 한 번 옮기고 n + 1을 1로 옮기기)
// 이를 옮기는 방식으로 생각해 보면 F(n + 1) = n개를 2번으로 옮기는 경우의 수 + n을 3으로 옮기는 경우의 수 + n개를 2번에서 3번으로 옮기는 경우의 수
// 즉, n개에 대해서 다른 곳으로 옮길 수 있는 경우의 수를 생성하는 함수를 만들 필요가 있다.
// 파라미터적으로 생각해보면 옮겨야 할 것의 개수 n개, 옮겨야할 인덱스 1개, 재귀면 출력해야할 배열이 필요할 것 같기도 하고
// 출발지를 기록해야 될 것 같은데? 1->2로 옮기는 경우랑 1->3으로 옮길 때, 2->1, 2->3 시나리오가 많아
// 기저 조건은? 하나만 옮길 때일듯?
// f(n + 1개, from, to, output : vector), blank : from, to가 아닌 나머지 칸
// 기저 조건 if n == 1
// f(n + 1) = f(n, from, blank) + [from, to] + f(n, blank, to)

void Hanoi(int n, int from, int to, vector<vector<int>>& output);

vector<vector<int>> solution(int n) {
    vector<vector<int>> result;
    Hanoi(n, 1, 3, result);
    return result;
}

void Hanoi(int n, int from, int to, vector<vector<int>>& output) {
    if(n == 1) {
        output.push_back({from, to});
        return;
    }
    
    int blank = 6 - (from + to); // 1, 2, 3 중에서 빠진 것을 하나 선택
    Hanoi(n - 1, from, blank, output);
    Hanoi(1, from, to, output);
    Hanoi(n - 1, blank, to, output);
}