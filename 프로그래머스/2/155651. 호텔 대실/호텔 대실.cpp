#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

// 아이디어1 : 방이 필요한 경우는 시간이 겹칠 때이다. 즉, 구간 중에서 최대 겹친 것의 개수가 필요한 방의 개수이다.
// 아이디어2 : 청소 시간이 10분 있으므로 처음부터 10분을 늘려서 처리
// 아이디어3 : 겹친다는 것은 [start, end] 구간에 다른 start가 존재한다는 것이다. start 별로 정렬하고 가장 빠른 start부터 다른 것의 start를 확인한다. start별로 정렬하는 이유는 현재 range 보다 더 빠른 start를 가지지 않게 하기 위해서이다.
// 아이디어4 : 동일 시간 예약이 가능하지만 어차피 최대 개수만 구하면 되기 때문에 첫번째 동일 시간에서 최대 값을 가진다. 따라서 같은 방식으로 처리한다.

// Fix1. 겹치는 것을 세는 알고리즘에 문제가 있었다. 겹치는 부분만 구하는 것이 아니라 범위가 포함하는 overlap을 한 번에 세고 있어서 문제가 생겼다. 이러한 이슈는 예전에 풀었던 단속 카메라 문제에서 발생한 이슈와 동일하다.
// 단속 카메라 : https://school.programmers.co.kr/learn/courses/30/lessons/42884
// 그러면 이것도 마찮가지로 종료 시간을 기준으로 정렬하고 비교하면 해결할 수 있을 것 같다.

// fix2. 첫번째 구현은 O(n^2) 시간 복잡도였는데 스위핑 알고리즘을 사용하면 O(n)의 시간 복잡도로 해결 가능하다고 한다.
// 스위핑 알고리즘은 시간축을 따라 이벤트를 순차적으로 처리하는 알고리즘이라고 한다. 구간 겹침, 회의실 문제, 선분 교차 문제 등에서 사용된다고 한다.
// 스위핑 알고리즘 아이디어 : 시작과 끝을 이벤트로 분리해서 시간 순으로 정렬한다. 그리고 이벤트를 순회하면서 값을 계산한다.
// 이 문제에서는 start에서는 +1, end에서는 -1을 해서 특정 순간에 사람의 개수를 확인한다.

using namespace std;

// pair first : 시간을 second로 나타낸 시작 시간, pair second : 시간을 second로 나타낸 종료 시간
vector<pair<int, int>> convert_to_range(const vector<vector<string>>& book_time);
int convert_string_to_seconds(const string& time);

int solution2(vector<vector<string>> book_time) {
    vector<pair<int, int>> book_range = convert_to_range(book_time);
    for(pair<int, int>& range : book_range) {
        range.second += 10;
    }
    sort(book_range.begin(), book_range.end(), [](auto& a, auto& b) {
        return a.second < b.second; // 종료 시간을 기준으로 정렬
    });
    

    int max_overlap = numeric_limits<int>::min();
    for(int i = 0; i < book_range.size(); i++) {
        // overlap의 개수 세기
        int overlap = 0;
        for(int j = i + 1; j < book_range.size(); j++) {
            // range start < cur range end
            if(book_range[j].first < book_range[i].second) {
                overlap++;
            }
        }
        
        max_overlap = max(max_overlap, overlap);
    }
    
    return max_overlap + 1;
}

int solution(vector<vector<string>> book_time) {
    // event = pair : first : time, second : +1 or -1(인원 증감)
    vector<pair<int, int>> events;
    for(const vector<string>& book : book_time) {
        int start = convert_string_to_seconds(book[0]);
        int end = convert_string_to_seconds(book[1]) + 10;
        events.emplace_back(start, 1);
        events.emplace_back(end, -1);
    }
    
    // 시작 시간을 기준으로 정렬하고 시작 시간이 같다면 종료 이벤트를 우선으로 한다.
    sort(events.begin(), events.end(), [](const auto& a, const auto& b) {
       return a.first == b.first ? a.second < b.second : a.first < b.first; 
    });
    
    int max_overlap = 0;
    int cur_overlap = 0;
    for(const auto& event : events) {
        cur_overlap += event.second;
        max_overlap = max(max_overlap, cur_overlap);
    }
    
    return max_overlap;
}

vector<pair<int, int>> convert_to_range(const vector<vector<string>>& book_time) {
    vector<pair<int, int>> result;
    for(const vector<string>& range : book_time) {
        int start = convert_string_to_seconds(range[0]);
        int end = convert_string_to_seconds(range[1]);
        result.emplace_back(start, end);
    }
    
    return result;
}

// hh:mm -> seconds
int convert_string_to_seconds(const string& time) {
    return stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3, 2));
}