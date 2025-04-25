#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// 어파치 n -> 라이언 n
// 점수 0~10
// k 점수에 a, b 를 맞췄을 경우, 더 많은 화살을 맞춘 사람이 k 점수를 가져간다.
// tie break
// a == b일 경우 어파치가 점수 획득

// goal : 가장 큰 점수 차이로 이기기
// 1. 우선적으로 비어 있는 곳에 한 발씩 넣으면 점수를 획득 가능
// 2. 이미 있는 곳에 더 많은 화살을 사용할 경우 점수 무력화 가능
// 3. 여러 방법이 있을 경우 가장 낮은 점수를 더 많이 맞힌 경우를 return

// 아이디어
// 1. n을 배치할 수 있는 경우의 수가 굉장히 많고 케이스 나열하기가 어려움
// 하지만, n의 개수가 작음, 따라서 brute force를 이용해서 풀이할 수 있을 것이라 생각한다.
// 평소와 다른 점은 n을 여러개 배분이 가능한 점이다.
// 화살이 독립적으로 설정 가능하니까 일단은 2가지 방법으로 할 수 있을 것 같다.
// 첫번째는 slot 별로 작동하는 방법이다.
// slot 별로 작동하면 0번째에 a0개, 1번째에 a1개 이런 식으로 할 수 있다.
// 두번째는 화살 별로 작동하는 방법이다.
// 화살을 임의의 slot에 배분을 하고 모든 화살을 배분하고 카운팅을 한다.
// 이렇게 하는 것은 0, .... 0을 10, .... 10까지 나열하는 방법과 같다.
// 근데 이렇게 하면 10^10이 필요하지 않나? 10000000000, 100억 연산 정도인데 불가능 범위라 생각한다.
// 따라서 첫번째 방법으로 돌아간다.

using namespace std;

void generate_win(int remain, int index, vector<int>& arrows, const vector<int>& other, vector<vector<int>>& result, int& score);
// 점수차를 반환
int calculate_score(const vector<int>& arrows, const vector<int>& other);

// info : 화살의 개수, 0~10이므로 11 길이
// i 번째 원소 : 10 - i 점을 획득
// 0 번째 원소 : 10점을 획득

vector<int> solution(int n, vector<int> info) {
    vector<int> arrows(11, 0);
    vector<vector<int>> result;
    int score = 0;
    generate_win(n, 0, arrows, info, result, score);
    
    sort(result.begin(), result.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
        // fix4 : index는 10까지 있으므로 10으로 변경
        for(int i = 10; i >= 0; i--) {
            if(lhs[i] != rhs[i]) {
                return lhs[i] > rhs[i];
            }
        }
        return false;
    });
    
    // fix1: 삼항 연산자일 경우 {-1} 형식으로 반환할 수 없다.
    // 초기화 리스트의 경우 타입에 대해서 명확하지 않기 때문이고 이럴 경우는 명시적으로 작성해야 한다.
    return !result.empty() ? result.front() : std::vector<int>{-1};
}

// index : 현재 배치할 slot index
void generate_win(int remain, int index, vector<int>& arrows, const vector<int>& other, vector<vector<int>>& result, int& score) {
    // base case : 모든 화살을 사용했거나 모든 slot을 사용
    // fix2 : remain == 0, index >= 11일 경우를 같이 처리하고 안에서 다시 처리하는 것은 구조적으로 좋지 않다.
    // 각각 따로 처리하도록 해서 중첩된 조건문, 중복 체크를 방지한다.
    if(remain == 0) {
        int cur_score = calculate_score(arrows, other);
        
        if(cur_score > score) {
            score = cur_score;
            // fix3 : clear하고 push_back을 할 필요 없이 바로 대입을 하면 된다.
            result = {arrows};
        }
        // fix7: tie일 경우를 처리해야 한다.
        // 문제를 풀이해서 설계를 할 때 base case에서 어떻게 처리할 지에 대해 구체적으로 작성했어야 한다.
        else if(cur_score == score && cur_score != 0) {
            result.push_back(arrows);
        }
        
        return;
    }
    if(index >= 11) {
        return;
    }
    
    for(int i = 0; i <= remain; i++) {
        arrows[index] = i;
        generate_win(remain - i,index + 1, arrows, other, result, score);
        arrows[index] = 0;
    }
}

int calculate_score(const vector<int>& arrows, const vector<int>& other) {
    // i 번째 index : 10 - i 점수의 인덱스
    // 0 번째 index : 10 점수의 인덱스
    
    int score = 0;
    for(int i = 0; i < 11; i++) {
        // fix5 : arrows[i] > other[i]일 경우 arrows[i] > 0이 항상 성립하므로 arrows[i] 조건이 필요 없다.
        // other[i]의 최소값이 0이기 때문
        if(arrows[i] > other[i]) {
            score += 10 - i;
        }
        // fix6 : 마찮가지로 arrows[i] > other[i]가 false일 경우 arrows[i] <= other[i]가 되므로 other[i]만 확인하면 된다.
        else if(other[i] > 0) {
            score -= 10 - i;
        }
    }
    
    return score;
}