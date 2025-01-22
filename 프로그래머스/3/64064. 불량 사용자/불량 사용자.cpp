#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;

// 경우의 수를 카운팅하는 문제라고 생각한다.
// 대신, 제재 아이디 부분에서 중복된 경우를 카운팅할 수 있는 방법이 필요하다.
// banned id에서 그냥 해당 되는 문자열을 모두 구한 다음, 각각 하나씩 고르면서 카운팅하면 되지 않을까?
// 하나씩 고르는 부분은 순열이니까 백트랙킹을 이용하면 될 것 같다.

vector<string> FindMatchingID(const vector<string>& ids, const string& matching_pattern);
bool IsMatch(const string& str, const string& pattern);
void SelectUniqueIDs(vector<vector<string>>& groups, set<string>& current_selected, set<vector<string>>& result);

int solution(vector<string> user_id, vector<string> banned_id) {
    vector<vector<string>> groups;
    for(const string& banned : banned_id) {
        vector<string> match_ids = FindMatchingID(user_id, banned);
        groups.push_back(match_ids);
    }
    
    set<string> current_selected;
    set<vector<string>> result;
    SelectUniqueIDs(groups, current_selected, result);
        
    return result.size();
}

vector<string> FindMatchingID(const vector<string>& ids, const string& matching_pattern) {
    vector<string> result;
    // for(const string& id : ids) {
    //     if(IsMatch(id, matching_pattern)) {
    //         result.push_back(id);
    //     }
    // }
    // Filtering 작업도 copy_if를 이용해서 표현할 수 있다.
    copy_if(ids.begin(), ids.end(), back_inserter(result), [&matching_pattern](const string& id) {
        return IsMatch(id, matching_pattern);
    });
    
    return result;
}

bool IsMatch(const string& str, const string& pattern) {
    // Equal을 사용하면 다르게 표현할 수도 있다.
//     if(str.length() != pattern.length()) {
//         return false;
//     }
    
//     for(int i = 0; i < str.length(); i++) {
//         if(pattern[i] == '*') {
//             continue;
//         }
//         else if(pattern[i] != str[i]) {
//             return false;
//         }
//     }
    
//     return true;
    return str.length() == pattern.length() &&
        equal(str.begin(), str.end(), pattern.begin(), [](char c1, char c2) {
           return c2 == '*' || c1 == c2; 
        });
}

void SelectUniqueIDs(vector<vector<string>>& groups, set<string>& current_selected, set<vector<string>>& result) {
    // base case: 모든 선택이 완료
    // 현재 결과를 result에 출력
    if(current_selected.size() == groups.size()) {
        vector<string> selected = vector(current_selected.begin(), current_selected.end());
        result.insert(selected);
        return;
    }
    
    int n = current_selected.size();
    const vector<string>& candidate = groups[n];
    
    for(const string& candidate_id : candidate) {
        if(current_selected.find(candidate_id) == current_selected.end()) {
            current_selected.insert(candidate_id);
            SelectUniqueIDs(groups, current_selected, result);
            current_selected.erase(candidate_id);
        }
    }
}