#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <algorithm>

// info
// program : cpp, java, python
//  backend, frontend
// junior, senior
// chicken, pizza
// test score

// query를 바탕으로 구하기
// 언어 직군 경력 소울푸드 순으로 나열, - 가 들어가면 고려하지 않음
    
// info : 1~50,000
// query : 1~100,000

// 특정 인원이 부합하는지 확인할려면
// unordered_set을 이용할 경우, 각각 O(1) 시간 복잡도로 실행 가능
// info : O(n)개
// query 1개 처리 : O(n)
// query n개 처리 : O(n ^ n)

// indexing을 세분화하기
// info 보다 query의 수도 많기 때문에 이를 최적화할려면 각각 indexing을 하는 것이 아니라
// 조합에 따른 indexing을 해야 한다.
// 그렇게 함으로써 query를 O(log n) 시간에 처리가 가능하다.

// indexing
// 4가지 조건이 있기 때문에 이 4가지를 선택한 조합을 만들어내면 된다.
// - 4중 반복문 : 간단하긴 하지만 4중은 번거롭다
// - 재귀 : 강력하지만 번거롭다
// - 비트 마스크 : 상대적으로 간단하다. 이러한 경우를 위해서 정리를 할 필요가 있다.

using namespace std;

unordered_map<string, vector<int>> score_map;

void parse_info(const vector<string>& info);
int match_count(const string& query);

vector<int> solution(vector<string> info, vector<string> query) {
    parse_info(info);

    vector<int> result;
    for(const string& query_str : query) {
        int match = match_count(query_str);
        result.push_back(match);
    }
    
    return result;
}

void parse_info(const vector<string>& info) {
    for(int i = 0; i < info.size(); i++) {
        const string& line = info[i];
        
        stringstream ss(line);
        string lang, job, career, food;
        int score;
        
        ss >> lang >> job >> career >> food >> score;
        
        vector<string> attrs = {lang, job, career, food};
        // mask : 0000~1111
        for(int mask = 0; mask < (1 << 4); mask++) {
            string key;
            for(int i = 0; i < 4; i++) {
                key += (mask & (1 << i)) ? attrs[i] : "-";
            }
            score_map[key].push_back(score);  
        }
    }
    
    for(auto& pair : score_map) {
        sort(pair.second.begin(), pair.second.end());
    }
}

int match_count(const string& query) {
    stringstream ss(query);
    string token;
    vector<string> tokens;
    while(ss >> token) {
        if(token != "and") {
            tokens.push_back(token);
        }
    }
    string key = tokens[0] + tokens[1] + tokens[2] + tokens[3];
    int score = stoi(tokens[4]);
    
    if(score_map.find(key) == score_map.end()) return 0;
    
    const vector<int>& scores = score_map[key];
    return scores.end() - lower_bound(scores.begin(), scores.end(), score);
}