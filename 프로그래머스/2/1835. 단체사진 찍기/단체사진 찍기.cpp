#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

// 완전 탐색 중에서 특정 조건을 만족시키는 문제이다.
// 이러한 문제는 백트랙킹을 이용해서 해결할 수 있다.
// k번째 수가 정해지면 해당 K번째와 나머지 수와의 조건을 판단하면 된다.(k-1번째의 수는 조건을 만족하므로)

int count_combinations(vector<char>& elems, string& current, vector<bool>& chosen, const vector<string>& conditions);
bool has_met(const string& current, char next, const vector<string>& conditions);

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    vector<char> elems = {'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T'};
    int size = elems.size();
    string current;
    vector<bool> chosen(size, false);
    return count_combinations(elems, current, chosen, data);
}

int count_combinations(vector<char>& elems, string& current, vector<bool>& chosen, const vector<string>& conditions) {
    if(current.size() == elems.size()) {
        return 1;
    }
    
    int count = 0;
    for(int i = 0; i < elems.size(); i++) {
        if(!chosen[i] && has_met(current, elems[i], conditions)) {
            chosen[i] = true;
            current.push_back(elems[i]);
            count += count_combinations(elems, current, chosen, conditions);
            current.pop_back();
            chosen[i] = false;
        }
    }
    
    return count;
}

bool has_met(const string& current, char next, const vector<string>& conditions) {
    if(current.size() == 0) {
        return true;
    }
        
    for(const string& condition : conditions) {
        char targetA = condition[0];
        char targetB = condition[2];
        char check = condition[3];
        int num = condition[4] - '0';
        
        if(targetA != next && targetB != next) {
            continue;
        }
        
        char target_to_check = targetA == next ? targetB : targetA;
        
        // chosen을 이용하면 이미 존재하는지 판단 가능하다.
        // map의 형식을 이용하면 위치만을 기록할 수 있지 않을까?
        if(size_t found = current.find(target_to_check); found != string::npos) {
            int new_index = current.size();
            int gap = new_index - found - 1;
            if(check == '=') {
                if(gap != num) return false;
            }else if(check == '>') {
                if(gap <= num) return false;
            }else if(check == '<') {
                if(gap >= num) return false;
            }
        }
    }
    
    return true;
}