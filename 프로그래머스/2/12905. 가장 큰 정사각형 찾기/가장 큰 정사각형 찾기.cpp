#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// 가장 큰 정사각형을 구하는 문제
// 일단은 브루트 포스를 이용해서 구현하도록 한다.

// 시도1. 시간 초과를 발생, 브루트 포스가 아니고 다른 풀이 필요
// 이러한 문제를 풀 수 있는 방법은 2가지가 존재한다.
// 1. DP
// 2. Divide and Conquer
// 정사각형은 다른 정사각형으로 겹치면서 풀이가 될 것이므로 겹치지 않는 분할 정복보다는 겹치는 문제를 풀이하는 DP의 가능성이 높다.
// DP의 경우라면 F(n)을 이전의 subproblem으로 표현이 가능해야 한다.
// F를 (row, col)에서의 최대 정사각형이라 가정하자.
// 2차원 DP의 경우는 최소 편집 거리 문제처럼 근처의 다른 요소들을 통해서 표현이 가능한 경우가 많다.
// 일단 잘 모를 경우는 작은 수에서 실질적인 값을 확인하는 확인하는 것이 유효하다.
// 문제 예시를 F(row, col) 태이블로 표현하면
// 0 1 1 1      0 1 1 1
// 1 1 1 1      1 1 2 2
// 1 1 1 1      1 2 2 3
// 0 0 1 0      0 0 1 0
// 값을 보고 유추하건데 근처 row, col 중에서 +1을 하는 구조인 것 같다. 2개의 f(row, col)을 합치는 것은 아니다.
// 결국은 정사각형을 구성을 하려면 정사각형 내부가 1로 채워져 있어야 한다.
// f(row - 1, col - 1)  f(row - 1, col)
// f(row, col - 1)      f(row, col)
// f(row, col - 1)이 밑변을 정의하게 되고 f(row - 1, col)이 높이를 정의하게 되고
// f(row - 1, col - 1)이 내부를 정의하게 된다.
// 밑변과 높이가 동일해야 하므로 min( f(row, col - 1), f(row -1, col) )이 가능한 정사각형의 최대 변의 길이이다.
// 이 상황에서 f(row - 1, col - 1)로 정사각형의 내부를 채워야 한다.
// 따라서 최소 변 side가 있을 경우 min( f(row - 1, col - 1), side)가 되고 수식을 나타내면
// f(row, col) = min [f(row - 1, col - 1), f(row - 1, col), f(row , col - 1)] + 1(기존 보다 하나 더 큰 정사각형이 생성되므로)
// 예외 케이스 처리를 하기 위해서는 정사각형을 새로 만들지 못할 경우를 체크해야 한다.
// 만약에 f(row - 1, col - 1), f(row -1, col), f(row, col - 1) 중에서 0이 있을 경우 정사각형을 생성하지 못하므로 1이 되어야 한다.
// 이는 min 조건에서 0이 되어서 자동으로 1이 된다. 따라서 통합된 수식으로 표현이 가능하다.

// Feedback
// 행/열에서 이미 matrix의 크기가 1000000(백만 단위)이고 이를 다시 n^2로 검사하면 백만 * 백만 단위이라 1조 단위 연산이다.
// 애초부터 브루트 포스로 접근하면 안 되는 문제였다.
// 그리고 생각보다 dp로 짜는게 훨씬 짧은 시간이 걸렸다. brute force가 항상 짧은 풀이 시간을 보장하는 것은 아니니까 문제를 접근할 때 다각적으로 접근해야 할 필요가 있다.

int solution(vector<vector<int>> board)
{
    int rows = board.size();
    int cols = board[0].size();
    
    int max_side = 0;
    vector<vector<int>> dp(rows, vector<int>(cols, 0));
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            // fix. 코드가 겹치는 부분이 존재한다. 이는 if board[row][col] == 0인 부분과 나머지가 분리되어야 하기 때문이다.
            // 다만, if else가 루프가 그렇게 이쁘지는 않다.
            if(board[row][col] == 0) {
                dp[row][col] = 0;
            }
            else {
                if(row == 0 || col == 0) {
                    dp[row][col] = 1;
                }
                else {
                    dp[row][col] = min({dp[row - 1][col - 1], dp[row - 1][col], dp[row][col - 1]}) + 1;
                }    
                max_side = max(max_side, dp[row][col]);
            }
        }
    }
    
    return max_side * max_side;
}
