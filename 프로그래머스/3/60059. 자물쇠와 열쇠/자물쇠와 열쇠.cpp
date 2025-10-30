#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 자물쇠 : N x N
// 열쇠 : M x M
// 열쇠는 회전 및 이동이 가능
// 돌기 부분과 자물쇠 홈이 정확히 일치해야하고 열쇠 돌기와 자물쇠 돌기가 겹치면 안 된다.
// 모든 홈을 채워야 자물쇠를 열 수 있다. 즉, 빈 칸을 전부 매울 수 있으면 열 수 있다.
// 자물쇠 영역을 벗어난 부분은 고려하지 않는다.
// 20 X 20 배열이기 때문에 400개의 칸이 존재
// 400개의 lock이 존재하고 이것을 400번 확인한다고 가정하면
// 400 X 400 X 400 = 64000000, 6400만 번의 시행회수로 풀이가 가능
// 회전까지 고려한다면 4배가 되어서 4억 6400만 번의 시행회수로 풀이가 가능

// 틀린 이유 메모
// 자물쇠와 열쇠 문제에서 주의할 점은, 시작점이 항상 lock 안에 존재하지 않는다는 점이다.
// 음수 부분에서부터 시작해야 되서 실제로는 더 넓은 범위를 태스트해야 한다.

bool check_key(const vector<vector<int>>& lock, const vector<vector<int>>& key);
bool is_match_key(const vector<vector<int>>& lock, const vector<vector<int>>& key, int row, int col);
vector<vector<int>> rotate_mat(const vector<vector<int>>& mat);
void print_mat(const vector<vector<int>>& mat);
    
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    for(int i = 0; i < 4; i++) {
        if(check_key(lock, key)) {
            return true;
        }
        
        key = rotate_mat(key);
    }
    
    return false;
}

// key의 위치를 변경하면서 조건을 만족하는지 확인한다.
bool check_key(const vector<vector<int>>& lock, const vector<vector<int>>& key) {
    // fix6. 정사각행렬이므로 size로 변수를 변경
    int lock_size = lock.size();
    int key_size = key.size();
    
    // fix5. key를 가능하면 가장 멀리 떨어뜨려서 넣는 것부터 가장 끝으머리에 넣는 것까지 하면 된다.
    for(int row = -key_size + 1; row < lock_size; row++) {
        for(int col = -key_size + 1; col < lock_size; col++) {
            if(is_match_key(lock, key, row, col)) {
                return true;
            }
        }
    }
    
    return false;
}

// fix4. row, col은 의도가 명확하지 않다.
// start_row, start_col로 수정한다.
bool is_match_key(const vector<vector<int>>& lock, const vector<vector<int>>& key, int start_row, int start_col) {
    // fix3. lock을 매개변수에서 copy를 이용하는 것도 괜찮지만 코드를 읽는 부분에서 의도를 누락할 수 있다.
    // 복사는 내부에서 명시적으로 진행한다.
    vector<vector<int>> test_lock = lock;
    int lock_size = lock.size();
    int key_size = key.size();
    
    // fix4. start_row, start_col이 음수가 될 수 있는 것에 따라서 항상 범위를 확인해야 한다.    
    // 이런 2개의 mat를 쓸 경우 index가 0에서 시작하는 것이 이해하기 편하다.
    for(int key_row = 0; key_row < key_size; key_row++) {
        for(int key_col = 0; key_col < key_size; key_col++) {
            int lock_row = start_row + key_row;
            int lock_col = start_col + key_col;
            if(lock_row >= 0 && lock_row < lock_size && lock_col >= 0 && lock_col < lock_size) {
                test_lock[lock_row][lock_col] += key[key_row][key_col];
            }
        }
    }
    
    for(int lock_row = 0; lock_row < lock_size; lock_row++) {
        for(int lock_col = 0; lock_col < lock_size; lock_col++) {
            if(test_lock[lock_row][lock_col] != 1) {
                return false;
            }
        }
    }
    
    return true;
}

// 1 2 3 -> 7 4 1
// 4 5 6 -> 8 5 2
// 7 8 9 -> 9 6 3

// (0, 0), (0, 1), (0, 2)
// (1, 0), (1, 1), (1, 2)
// (2, 0), (2, 1), (2, 2)

// (2, 0), (1, 0), (0, 0)
// (2, 1), (1, 1), (0, 1)
// (2, 2), (1, 2), (0, 2)

// 역순으로 채워 나가야 하므로 width - row열에서 채워나간다.
// col이 row가 된다.

// 1 2 3 4
// 5 6 7 8
//
// 5 1
// 6 2
// 7 3
// 8 4

// row를 끝에서부터 채워나가면 된다.

vector<vector<int>> rotate_mat(const vector<vector<int>>& mat) {
    // fix2. 정사각행렬이기 때문에 width 보다는 명확한 이름을 사용할 필요가 있다.
    // 짧게는 n, 길게는 size 정도로 표현할 수 있다.
    int size = mat.size();
    vector<vector<int>> rotated_mat(size, vector<int>(size, 0));
    for(int row = 0; row < size; row++) {
        int rotated_col = size - row - 1;
        for(int col = 0; col < size; col++) {
            int rotated_row = col;
            rotated_mat[rotated_row][rotated_col] = mat[row][col];
        }
    }
    
    return rotated_mat;
}

void print_mat(const vector<vector<int>>& mat) {
    // int rows = mat.size();
    // int cols = mat[0].size();
    // for(int row = 0; row < rows; row++) {
    //     for(int col = 0; col < cols; col++) {
    //         cout << mat[row][col] << " ";
    //     }
    //     cout << endl;
    // }
    
    // fix1. 알고리즘 태스트에서는 시간이 모자르다. 따라서 auto를 이용해서 간결하게 타이핑할 수 있다.
    for(auto& row : mat) {
        for(auto v : row) cout << v << ' ';
        cout << endl;
    }
}