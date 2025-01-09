#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 단순 구현 문제로 생각된다.
// 각 회전마다 최솟값을 반환하고 회전을 실행시키면 된다.

// 아이디어1
// 회전의 경우는 1차원 배열에서 우선적으로 생각해 본다.
// [1, 2, 3, 4]가 있을 때 i = 0, 1, 2에서 swap을 하면
// [2, 1, 3, 4]
// [2, 3, 1, 4]
// [2, 3, 4, 1]
// 왼쪽 회전이 구현이 된다.
// 역방향으로 진행하면
// [1, 2, 4, 3]
// [1, 4, 2, 3]
// [4, 1, 2, 3]
// 오른쪽 회전이 구현된다.
// 오른쪽 행렬이 문제에서 요구하는 것이므로 역방향으로 swap을 반복해 나가면 오른쪽이 구현된다.

// 아이디어2
// 그러면 범위 내의 배열을 순차적으로 접근할 수 있는 방법이 필요하다.
// 이 문제는 회오리 수열? 달팽이 수열? 에서의 접근하고 같다.
// https://school.programmers.co.kr/learn/courses/30/lessons/68645
// https://school.programmers.co.kr/learn/courses/30/lessons/181832
// 요점은 결국 범위를 벗어나게 되면 방향을 전환하는 것이다.

class OutlineTraverse {
private:
    // 좌상단
    pair<int, int> p1;
    // 우하단
    pair<int, int> p2;
    pair<int, int> pos;
    int dir_index = 0;
    static constexpr pair<int, int> dirs[] = {
        {0, 1}, // right
        {1, 0}, // down
        {0, -1}, // left
        {-1, 0}, // up
    };
    static constexpr pair<int, int> reverse_dirs[] = {
        {1, 0}, // down
        {0, 1}, // right
        {-1, 0}, // up
        {0, -1}, // left
    };
    // fix2. constexpr은 계산 가능하다.
    static constexpr int reverse_dir_size = sizeof(reverse_dirs) / sizeof(reverse_dirs[0]);
public:
    OutlineTraverse(pair<int, int> p1, pair<int, int> p2)
        : p1(p1), p2(p2), pos(p1) {
            
    }
    
    // fix3. GetNextPos -> AdvancePosition으로 변경
    // Get은 단순하게 Getter처럼 보여서 내부의 값이 변하지 않는 것처럼 보인다.
    // 실질적으로는 내부의 위치를 갱신하고 반환하기 때문에 Advance란 단어를 이용해서 표현한다.
    pair<int,int> AdvancePosition() {
        pair<int, int> next_pos = {pos.first + reverse_dirs[dir_index].first, pos.second + reverse_dirs[dir_index].second};
        if(is_out_of_bounds(next_pos)) {
            dir_index = (dir_index + 1) % reverse_dir_size;
            next_pos = {pos.first + reverse_dirs[dir_index].first, pos.second + reverse_dirs[dir_index].second};
        }
        
        pos = next_pos;
        return next_pos;
    }
    
    int GetOutlineCount() const {
        int width = p2.first - p1.first + 1;
        int height = p2.second - p1.second + 1;
        return 2 * width + 2 * height - 4; // 2 * width + 2 * height - 꼭지점 4군데
    }
    
private:    
    // fix1. 값을 변경하지 않는 함수는 const를 붙이자.
    // fix2. out_of_rage -> is_out_of_bounds : bool 반환 함수를 명확하게 하기 위해서는 is 같은 의문문 형태로 해야 한다.
    // 또한, 1차원 범위는 range로 표현하지만 2차원 격자에서는 bounds란 표현이 더 어울린다.
    bool is_out_of_bounds(pair<int, int> pos) const {
        return pos.first < p1.first || pos.first > p2.first || pos.second < p1.second || pos.second > p2.second;
    }
};

vector<vector<int>> build_mat(int rows, int cols);
void print_mat(const vector<vector<int>>& mat);

// return : 바뀐 숫자들 중에서 가장 작은 수
vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<vector<int>> mat = build_mat(rows, columns);
    
    vector<int> result;
    for(const vector<int>& query : queries) {
        // matrix은 0-base
        OutlineTraverse ot({query[0] - 1, query[1] - 1}, {query[2] - 1, query[3] - 1});
        
        int count = ot.GetOutlineCount() - 1;
        pair<int, int> prev_pos = ot.AdvancePosition();
        int min_val = mat[prev_pos.first][prev_pos.second];
        for(int i = 0; i < count; i++) {
            pair<int, int> new_pos = ot.AdvancePosition();
            min_val = min(min_val, mat[new_pos.first][new_pos.second]);

            swap(mat[prev_pos.first][prev_pos.second], mat[new_pos.first][new_pos.second]);
            prev_pos = new_pos;
        }
        
        result.push_back(min_val);
    }
    
    return result;
}

vector<vector<int>> build_mat(int rows, int cols) {
    vector<vector<int>> result(rows, vector<int>(cols));
    int count = 1;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            result[row][col] = count++;
        }
    }
    
    return result;
}

void print_mat(const vector<vector<int>>& mat) {
    int rows = mat.size();
    int cols = mat[0].size();
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            cout << mat[row][col] << ' ';
        }
        cout << endl;
    }
}