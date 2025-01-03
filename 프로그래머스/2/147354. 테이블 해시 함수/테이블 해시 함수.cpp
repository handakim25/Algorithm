#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

// 단순 구현 문제이다. 3가지 부분으로 나눌 수 있을 것 같다.
// 첫번째는, col번째 칼럼을 기준으로 tuple을 정렬하는 부분이다.
// 두번째는, row_begin, row_end 구간의 s_i를 구하는 부분이다.
// 세번째는, s_i의 bitwise 값들을 구하는 것이다.
// 정렬을 굳이 전체적으로 할 필요 없이 인덱스를 기준으로 정렬하도록 한다.
// 인덱스를 기준으로 정렬하게 되면 row_begin, row_end로 해당 범위로 값들을 다시 찾아서 s_i 값들을 구할 수 있다.

// 주의할 부분
// 1. Col, Row가 1-base이다.
// 2. [row_begin, row_end]라 row_end가 포함된다.

// return : col을 기준으로 정렬된 tuple 인덱스들의 집합. 0-base로 반환, col : 0-base
vector<int> SortByCol(const vector<vector<int>>& data, int col);

int solution(vector<vector<int>> data, int col, int row_begin, int row_end) {
    vector<int> sorted_index = SortByCol(data, col - 1);
    
    vector<int> s_i;
    for(int i = row_begin - 1; i < row_end; i++) {
        vector<int>& tuple = data[sorted_index[i]];
        int sum = 0;
        for(int n : tuple) {
            sum += n % (i + 1); // 내부적으로는 0-base이지만 실질적 값은 1-base이다. 따라서 1을 더해준다.
        }
        
        s_i.push_back(sum);
    }
    
    // bitwise
    int result = 0;
    for(int s : s_i) {
        result ^= s;
    }
    
    return result;
}

vector<int> SortByCol(const vector<vector<int>>& data, int col) {
    int rows = data.size();
    vector<int> index(rows);
    iota(index.begin(), index.end(), 0);
    
    // col 기준 오름차순
    // 동일할 경우 unique key(col 0) 기준 내림차순으로 정렬
    sort(index.begin(), index.end(), [&data, col](int a, int b) {
       if(data[a][col] == data[b][col]) {
           return data[a][0] > data[b][0];
       }
        else {
            return data[a][col] < data[b][col];
        }
    });
    
    return index;
}