#include <string>
#include <vector>
#include <iostream>

// n : 택배 상자 개수
// w : 가로열 개수
// num : 꺼낼 상자의 번호

// num이 주어졌을 때 세로열 위로 몇개가 있는지 판단해서 처리
// 1. 가장 간단한 방법은 배열에 기록하는 것이다. 배열에 기록하면 해당 위치에 몇개가 있는지 파악할 수 있다.
// 2. 하지만, num이 주어졌을 때 col, row를 구할 경우 위에 있는 col과 row를 계산할 수 있다.
// - 한 줄씩 계산되고 있지만 실질적으로는 2칸 짜리가 반복되는 구조로 생각하는 것이 더 수월하다.
// - 즉, 2w 단위로 자르고 그 안에 다시 w로 단위로 자르게 되면 최종 위치를 계산할 수 있다.
// num : 8, w : 6
// 8 % 2w(==12) = 0, 8 / 6 = 1 => 두번째 열, 8 % 6 = 2 => 위층 2번째 값
// 두번째 값을 구하면 위로와 아래로의 계산이 가능하다.
// 위로의 계산을 할 경우라면 위층에서 남은 것이므로 6 - 2 => 4가 되고 이를 이용하면 8칸을 넘어가야 한다. 거기에 원래 칸까지 가야하므로 + 1이 필요하다.
// 그 다음 칸 수는 나머지 칸 수를 더해야 하므로 2 - 1 칸을 2개 넘어가야 하고 그리고 + 1을 하면 된다.
// 요는 현재 칸수에 대해서 계산하고 그 다음 칸수를 계산하면 된다. 플립플롭 논리를 적용하면 된다.


using namespace std;

vector<vector<int>> build_arr(int n, int w, int num, int& out_row, int& out_col);

// 1-base
int solution(int n, int w, int num) {
    int target_row = 0;
    int target_col = 0;
    vector<vector<int>> arr = build_arr(n, w, num, target_row, target_col);
    
    int result = 0;
    int rows = (n - 1) / w;
    while(target_row <= rows) {
        if(arr[target_row][target_col] != 0) {
            result++;
        }
        target_row++;
    }
    
    return result;
}

vector<vector<int>> build_arr(int n, int w, int num, int& out_row, int& out_col) {
    int rows = (n - 1) / w + 1;
    vector<vector<int>> arr(rows, vector<int>(w, 0));
    
    int row = 0;
    int col = 0;
    int direction = 1;
    for(int i = 1; i <= n; i++) {
        if(i == num) {
            out_row = row;
            out_col = col;
        }
        
        arr[row][col] = i;
        int next_col = col + direction;
        if(next_col < 0 || next_col >= w) {
            row++;
            direction *= -1;
        } else {
            col = next_col;
        }
    }
    
    return arr;
}
