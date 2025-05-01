#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

// Select Number(2 <= N <= 100)
// Collect Numbers(S includes 1 <= s <= N)
// Shuffle Numbers
// Select 1 Number K
// Open Kth Number and selct K2
// open k2th number and select k3
// ... if kth number is already selected
// k1, k2, k3... -> Group 1
// Do same and make Group 2
// (k1 + K2 + ...) * (k1` + k2` + ...) -> Score
// Shuufle Numers -> cards
// 즉, 말은 길게 했지만 Shuffle된 Cards를 제시하고 해당 Cards로 최대 득점을 만드는 문제이다.
// Keyword : 최대
// 1-base
// Think1. 최대를 구하므로 순간 탐욕법이 생각이 났다. 하지만, 탐욕법의 경우는 현재 무엇을 기준으로 탐욕을 선택할 수 있을지 모호하고 Group2의 issue가 있다.
// Think2. Cards의 길이가 충분히 적다. 또한, Group의 특성을 보면 1, 4, 7, 8 중의 어떠한 수를 골라도 이는 하나의 Group으로 나눌 수 있다.
// Think3. 하나의 원소는 하나의 그룹에 속하게 되고 이를 통해서 모든 그룹을 확인하는 것이 가능하다.
// 모든 Group을 찾는 것이 가능하다면 가장 큰 2개의 Group을 찾으면 최대 값을 구할 수 있다.
// Think4. 어떠한 값이 Group에 속하는지는 필요 없고 합만 구하면 된다.

using namespace std;

vector<int> calculate_group_scores(const vector<int>& cards);
int collect_group_score(int index, const vector<int>& cards, vector<bool>& visited);

int solution(vector<int> cards) {
    vector<int> group_scores = calculate_group_scores(cards);
    sort(group_scores.begin(), group_scores.end(), greater<int>());
    
    group_scores.resize(2);
    return group_scores[0] * group_scores[1];
}

vector<int> calculate_group_scores(const vector<int>& cards) {
    vector<int> group_scores;
    vector<bool> visited(cards.size(), false);
    
    for(int i = 0; i < cards.size(); i++) {
        if(!visited[i]) {
            int group_score = collect_group_score(i, cards, visited);   
            group_scores.push_back(group_score);
        }      
    }
    
    return group_scores;
}

// index : 0-base
// cards : 1-base
int collect_group_score(int index, const vector<int>& cards, vector<bool>& visited) {
    int score = 0;
    while(!visited[index]) {
        visited[index] = true;
        score++;
        index = cards[index] - 1;
    }
    
    return score;
}