#include <iostream>
#include <vector>

using namespace std;

vector<int> solution(const vector<int> answers);
int calculate_score(const vector<int>& answers, const vector<int>& pattern);

int main() {
    vector<int> answers = {1, 2, 3, 4, 5};
    
    vector<int> result = solution(answers);
    for(int highest_score_person : result) {
        cout << highest_score_person << endl;
    }
    return 0;
}

vector<int> solution(const vector<int> answers) {
    vector<vector<int>> patterns = {
        {1, 2, 3, 4, 5},
        {2, 1, 2, 3, 2, 4, 2, 5},
        {3, 3, 1, 1, 2, 2, 4, 4, 5, 5},
    };

    int highest_score = -1;
    vector<int> scores(patterns.size(), 0);
    for(int i = 0; i < patterns.size(); i++) {
        scores[i] = calculate_score(answers, patterns[i]);
        highest_score = max(highest_score, scores[i]);
    }

    vector<int> result;
    for(int i = 0; i < patterns.size(); i++) {
        if(scores[i] == highest_score) {
            result.push_back(i + 1); // 번호는 1-base
        }
    }

    return result;
}

int calculate_score(const vector<int>& answers, const vector<int>& pattern) {
    int score = 0;
    for(int i = 0; i < answers.size(); i++) {
        if(answers[i] == pattern[i % pattern.size()]) {
            score++;
        }
    }

    return score;
}