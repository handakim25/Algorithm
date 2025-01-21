#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iostream>

// 개수가 적으므로 brute force를 이용할 수 있지 않을까?
// 크기가 가장 작은 것부터 나열한 다음에 작은 것부터 큰 것까지 차례대로 o(n^2) intersection을 구하고
// intersection들을 result에 넣으면 되지 않을까?
// 모든 intersection이 필요한 건 아니니까 intersection의 길이가 course의 개수이면 남기고 아니면 버리면 될 것 같다.

// 예시 테스트
// AC CDE ACDE BCFG ABCFG
// - AC
// CDE : C 불가능
// ACDE : AC++
// BCGF : C 불가능
// BCFG : C 불가능
// ABCFG : AC++
// ...
// 견적 잡으니까 ordered_set을 만들고 각각 intersection 모두 구하고
// intersection크기가 2 이상일 경우 map에다가 insert하고
// course에 따라서 값을 반환하면 될 것 같다.

using namespace std;

// key : 조합 문자열, int : count
vector<vector<string>> CountIntersections(const vector<string>& orders);
string FindIntersection(const set<char>& s1, const set<char>& s2);
void AddSubstringToCount(const string& intersect, unordered_map<int, unordered_map<string, int>>& length_group);
void GenerateCombinations(const string& intersect, unordered_map<int, unordered_map<string, int>>& length_group);

int MAX_COURSE_LEN = 10;

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<vector<string>> grouped_freq_intersections = CountIntersections(orders);
    
    vector<string> result;
    for(int num : course) {
        for(const string& str : grouped_freq_intersections[num]) {
            result.push_back(str);
        }
    }
    
    sort(result.begin(), result.end());
    
    return result;
}

vector<vector<string>> CountIntersections(const vector<string>& orders) {
    // set으로 변경
    int n = orders.size();
    vector<set<char>> order_set;
    for(const string& order : orders) {
        order_set.emplace_back(order.begin(), order.end());
    }

    // 문자열 길이별 그룹화 및 빈도 계산
    // key : length
    // value : <key : str, value : count>
    unordered_map<int, unordered_map<string, int>> lengthGroups;
    // intersection들을 기록
    for(int i = 0; i < order_set.size(); i++) {
        for(int j = i + 1; j < order_set.size(); j++) {
            string intersect = FindIntersection(order_set[i], order_set[j]);
            int length = intersect.length();
            
            if(length >= 2) {
                // Fix1. 부분 문자열이 아니라 조합(Combination)이다.
                GenerateCombinations(intersect, lengthGroups);
            }
        }
    }

    vector<vector<string>> result(MAX_COURSE_LEN + 1);
    for(const auto&[length, freq_map] : lengthGroups) {
        int max_freq = 0;
        vector<string>& most_freq_strings = result[length];
        
        for(const auto&[str, count] : freq_map) {
            if(count > max_freq) {
                max_freq = count;
                most_freq_strings = {str};
            }
            else if(count == max_freq) {
                most_freq_strings.push_back(str);
            }
        }
    }
    
    return result;
}

string FindIntersection(const set<char>& s1, const set<char>& s2) {
    string result;
    const set<char>& smaller = s1.size() < s2.size() ? s1 : s2;
    const set<char>& bigger = s1.size() < s2.size() ? s2 : s1;
    
    for(char ch : smaller) {
        if(bigger.count(ch)) {
            result.push_back(ch);
        }
    }
    
    return result;
}

void AddSubstringToCount(const string& intersect, unordered_map<int, unordered_map<string, int>>& length_group)
{
    for(int i = 0; i < intersect.length(); i++) {
        for(int j = i + 1; j <= intersect.length(); j++) {
            // i : 시작 인덱스, j - i : 복사할 문자열의 길이, [i, j)를 substr
            string sub = intersect.substr(i, j - i);
            int length = sub.length();
            if(length >= 2) {
                length_group[length][sub]++;
            }
        }
    }
}

void GenerateCombinations(const string& intersect, unordered_map<int, unordered_map<string, int>>& length_group)
{
    int len = intersect.length();
    
    for(int subset_size = 2; subset_size <= len; subset_size++) {
        vector<bool> selector(len, false);
        fill(selector.begin(), selector.begin() + subset_size, true);
        
        do{
            string combination;
            for(int i = 0; i < len; i++) {
                if(selector[i]) {
                    combination.push_back(intersect[i]);
                }
            }
            
            int len = combination.length();
            length_group[len][combination]++;
        }while(prev_permutation(selector.begin(), selector.end()));
    }
}