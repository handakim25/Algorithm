#include <string>
#include <vector>
#include <iostream>

using namespace std;

// schedules : 희망 출근 시간(i번째 사람의)
// vector<vector<int>> timelogs : 출근 시간, 하나의 배열이 한 사람의 출근 기록
// startday : 시작 요일, 토-일을 결정한다.

bool is_weekend(int day, int startday);
// fix2: is_attend -> is_on_time : 출결 여부가 아니라 지각 여부이므로 더 적절한 이름으로 수정
bool is_on_time(int desired_time, int attend_time);
int convert_to_min(int time);

int solution(vector<int> schedules, vector<vector<int>> timelogs, int startday) {
    int count = 0;
    for(int person_index = 0; person_index < schedules.size(); person_index++) {
        // fix3 : 코드 구조 변경, 현재 루프에서 필요한 변수 값을 설정하는 것이 제일 처음 나와야 한다.
        // is_all_attendance는 뒤의 루프에 관련된 내용이므로 뒤의 루프와 가까이 있어야 한다.
        // fix : 참조로 변경
        const vector<int>& timelog = timelogs[person_index];
        const int desired_time = schedules[person_index];
        
        bool is_all_attendance = true;
        for(int day = 0; day < timelog.size(); day++) {
            if(!is_weekend(day, startday)
              && !is_on_time(desired_time, timelog[day])) {
                is_all_attendance = false;
                break;
            }
        }
        
        if(is_all_attendance) {
            count++;
        }
    }    
    
    return count;
}

bool is_weekend(int day, int startday) {
    // day가 0부터 시작하므로 -2가 아니라 -1을 해준다.
    int index = (startday + day - 1) % 7;
    return index == 5 || index == 6;
}

bool is_on_time(int desired_time, int attend_time) {
    int desired_min = convert_to_min(desired_time);
    int attend_min = convert_to_min(attend_time);
    
    return attend_min <= desired_min + 10;
}

int convert_to_min(int time) {
    int hour = time / 100;
    int min = time % 100;
    
    return hour * 60 + min;
}