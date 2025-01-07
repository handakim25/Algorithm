#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <unordered_map>

using namespace std;

// 아이디어1
// 특정 조건을 만족시키는 범위의 문제의 경우 슬라이싱 윈도우 알고리즘으로 풀이가 가능할 수 있다.
// 슬라이싱 윈도우의 문제를 해결할 수 있는 방법은 일단 기본적으로 start의 위치를 적절하게 움직이는 것이다.
// start의 범위를 모든 것이 존재할 때까지 start의 범위를 줄이면 된다.
// 단, 항상 값을 기록할 수 있는 것은 아니고 모든 유효값이 들어와야 된다.
// 아이디어2
// 특정 값의 존재 유무에 대해서 개수를 파악해야 되니까 unordered_multiset이 유효하다고 생각한다.
// 아이디어3
// 모든 것이 존재하는 것을 파악해야 하니까 모든 값을 조회할 필요가 있다.
// 아이디어4
// 인덱스가 1부터 시작이니까 출력할 때는 인덱스를 맞춰줘야 한다.
// 회고
// multiset을 제대로 활용한 적이 없어서 시간이 걸렸다. 자주 사용하지 않은 자료구조에 대해서 정리해야 할 필요가 있다.

int count_type(const vector<string> gems);

vector<int> solution(vector<string> gems) {
    int type_count = count_type(gems);
    
    // key : gem, value : count
    unordered_map<string, int> gem_map;
    // 슬라이싱 윈도우 초기화
    int start = 0, min_length = numeric_limits<int>::max();
    int min_start = 0, min_end = 0;
    for(int end = 0; end < gems.size(); end++) {
        gem_map[gems[end]]++;
        
        // set에 2개 이상 존재하면 지워도 된다.
//         while(gem_set.count(gems[start]) >= 2) {
//             cout << "remove" << endl;
            
//             // Fix1. 값을 하나만 삭제하려고 하면 iterator를 삭제해야 한다.
//             // set의 삭제는 처음해봐서 해당 사항을 파악하지 못햇다.
//             // gem_set.erase(gems[start++]);
            
//             // Fix2. multiset의 count가 종류가 아니라 모든 개수를 더한 것을 반환을 해서 적합하지 않다.
//             // unordered_map으로 변경
//             auto iter = gem_set.find(gems[start++]);
//             gem_set.erase(iter);
//         }
        
        // fix4. start는 항상 map에 존재하므로 존재를 미리 확인하지 않아도 된다.
        // while(gem_map.find(gems[start]) != gem_map.end() && gem_map[gems[start]] >= 2) {
        while(gem_map[gems[start]] >= 2) {
            gem_map[gems[start]]--;
            if(gem_map[gems[start]] == 0) {
                gem_map.erase(gems[start]);
            }
            start++;
        }

        // 모든 보석이 모여 있을 경우
        if(gem_map.size() == type_count) {
            if(end - start + 1 < min_length) {
                min_length = end - start + 1;
                min_start = start;
                min_end = end;
            }
        }
    }
    
    return {min_start + 1, min_end + 1};
}

int count_type(const vector<string> gems) {
    // fix3. 단순 대입이라면 생성자를 이용해서 처리하면 된다.
//     unordered_set<string> gem_set;
//     for(const string& str : gems) {
//         gem_set.insert(str);
//     }
    
//     return gem_set.size();
    return unordered_set<string>(gems.begin(), gems.end()).size();
}