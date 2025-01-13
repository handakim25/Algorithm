#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 대기실의 크기가 크지 않다. 충분히 브루트포스(완전 탐색)으로 문제를 풀이할 수 있다.
// 좌상부터 차례대로 오른쪽과 아래 방향으로 탐색하면 겹치는 것 없이 탐색할 수 있을 것으로 추측된다.
// 따라서 확인 칸은 다음과 같다.(T : Test)
// P T T
// T T X
// T X X

// 반례
// 이번에 반례가 생긴 이유는 대각선 연산에서 발생할 수 있기 때문이다.
// O P X X
// P O O O

bool ValidatePolicy(const vector<string>& place);
bool IsValidPosition(int row, int col, const vector<string>& place);

constexpr char kPerson = 'P';
constexpr char kPartition = 'X';
constexpr char kBlank = 'O';

vector<int> solution(vector<vector<string>> places) {
    vector<int> result;
    for(const vector<string>& place : places) {
        bool isValidPlace = ValidatePolicy(place);
        result.push_back(isValidPlace ? 1 : 0);
    }
    
    return result;
}

bool ValidatePolicy(const vector<string>& place) {
    int rows = place.size();
    int cols = place[0].length();
    
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(place[row][col] == kPerson
              && !IsValidPosition(row, col, place) ) {
                return false;
            }
        }
    }
    
    return true;
}

// Fix1. 거리가 1인 지점과 거리가 2인 지점은 파티션 처리 유무가 다르다.
// 따라서 같은 배열로 처리하는게 아니라 다른 배열로 처리한다.
// 리스코프 치환 법칙을 떠올려보자. 만약에 하위 객체로 치환했을 때 호환이 안 되면 그것은 잘못된 관계이다.
// 지금도 for 루프에서 다른 조건을 판별해서 작동하면 수정해야 되는 상황인 거라 생각한다.
constexpr pair<int, int> kDistanceOneOffset[] = { {0, 1}, {1, 0} };
constexpr int kDistanceOneSize = sizeof(kDistanceOneOffset) / sizeof(kDistanceOneOffset[0]);

constexpr pair<int, int> kDistanceTwoOffset[] = {{0, 2}, {2, 0}};
constexpr int kDistanceTwoSize = sizeof(kDistanceTwoOffset) / sizeof(kDistanceTwoOffset[0]);

constexpr pair<int, int> kDiagonalOffset[] = {{1, 1}, {1, -1}};
constexpr int kDistanceDiagonalOffset = sizeof(kDiagonalOffset) / sizeof(kDiagonalOffset[0]);

bool IsOutOfRange(int row, int col, int rows, int cols);

bool IsValidPosition(int row, int col, const vector<string>& place) {
    int rows = place.size();
    int cols = place[0].length();
    
    // 거리가 1인 위치 판정
    for(int i = 0; i < kDistanceOneSize; i++) {
        int nextRow = row + kDistanceOneOffset[i].first;
        int nextCol = col + kDistanceOneOffset[i].second;
        
        if(!IsOutOfRange(nextRow, nextCol, rows, cols)
          && place[nextRow][nextCol] == kPerson) {
            return false;
        }
    }
    
    // 거리가 2인 직선 위치 판정
    for(int i = 0; i < kDistanceTwoSize; i++) {
        int nextRow = row + kDistanceTwoOffset[i].first;
        int nextCol = col + kDistanceTwoOffset[i].second;
        
        if(!IsOutOfRange(nextRow, nextCol, rows, cols)
          && place[nextRow][nextCol] == kPerson) {
            // 파티션 체크
            int partition_row = row + kDistanceTwoOffset[i].first / 2;
            int partition_col = col + kDistanceTwoOffset[i].second / 2;
            
            // 파티션은 사이에 존재하므로 항상 접근 가능이 보장된다.
            if(place[partition_row][partition_col] != kPartition) {
                return false;
            }
        }
    }
    
    // 대각선 판정
    for(int i = 0; i < kDistanceDiagonalOffset; i++) {
        int nextRow = row + kDiagonalOffset[i].first;
        int nextCol = col + kDiagonalOffset[i].second;
        if(!IsOutOfRange(nextRow, nextCol, rows, cols)
          && place[nextRow][nextCol] == kPerson) {
            int mid1_row = row + kDiagonalOffset[i].first;
            int mid1_col = col;
            int mid2_row = row;
            int mid2_col = col + kDiagonalOffset[i].second;
            if(place[mid1_row][mid1_col] != kPartition || place[mid2_row][mid2_col] != kPartition ) {
                return false;
            }
        }
    }
    
    return true;
}

// Fix2. OutOfRange 논리 연산자가 잘못된 내용을 수정
// 태스트 검증을 차례로 했어야 했는데 해당 검증을 하지 않았던 것이 실수이다.
// 한 번에 완성하지 말고 나누어서 작성을 해야 한다.
bool IsOutOfRange(int row, int col, int rows, int cols) {
    return row < 0 || row >= rows || col < 0 || col >= cols;
}