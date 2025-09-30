#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// 셔틀은 09:00부터 t분 간격 도착
// n회, t분 간격, m명이 탑승
// timetable : 대기열에 도착하는 시간, HH:MM 형식(01:01~23:59) 사이
// 대기 순서대로 태우고 출발, 도착 시간이 동일할 경우 탑승 가능

// 셔틀을 타고 무사히 사무실에 도착할 수 있는 가장 늦은 시각
// 일단, 두가지 경우의 수를 할 수 있다.
// 가장 마지막 셔틀 버스에 자리가 존재할 경우, 해당 버스가 도착할 시간이 가장 늦은 시각이다.
// 가장 마지막 셔틀 버스에 자리가 존재하지 않을 경우, 가장 마지막 버스에 탑승할 수 있을 시간이 가장 늦은 시각이다.

// 일단은 남은 시간 동안 최대한 탈 수 있는 인원을 구해보는 것은 어떨까?

// idea1. 모두 고려해서 한 번에 풀기에는 상당히 어려운 문제이다.
// 가장 간단한 방법부터 시작해서 문제를 풀이한다.
// 첫번째로는 모든 승객을 태울 수 있을 경우이다.

using namespace std;

int convert_to_min(const string& time);
string convert_to_time(int min);

string solution(int n, int t, int m, vector<string> timetable) {
    // crew_times로 sort를 해야 하기 때문에 timetable을 이용하지 않는 방향으로 간다.
    vector<int> crew_times(timetable.size());
    transform(timetable.begin(), timetable.end(), crew_times.begin(), [](auto time) {
        return convert_to_min(time);
    });
    sort(crew_times.begin(), crew_times.end());
    
    // think1. for문 밖의 변수도 이용해서 문제를 해결할 수 있다. for문 안에만 변수를 넣을려고 하면 오히려 어렵다.
    int bus_time = convert_to_min("09:00");
    int index = 0;
    int answer_time = 0;
    for(int i = 0; i < n; i++) {
        int passenger = 0;
        
        // for문을 통해서 파악하기에는 조건이 복잡하다.
        // 1. timetable의 수보다는 적어야 한다.(for문이라면 중간에 break)를 통해서 나와야 한다.
        // 2. 승객이 먼저 버스에 다 탈 수도 있고 아니면 승객이 다 차서 못 탈 수도 있다.
        // 2-1. 탈 수 있는 승객 : timetable[i] <= bus_time;
        // 3. for문이었다면 j를 넣어서 반복문을 돌았겠지만, while문을 사용했으므로 따로 변수를 생성한다.
        // 이를 passenger 변수로 한다.
        // 이러한 것을 통합적으로 표현하려면 for문 보다는 while문을 통해서 문제를 해결한다.
        while(index < crew_times.size() // 1. 최대 인원을 넘어가면 안 된다.
             && crew_times[index] <= bus_time // 2. 버스 시간 이전에 도착하면 탑승 가능하다.
             && passenger < m) { // 2. 버스 인원까지 탑승 가능하다.
            passenger++;
            index++;
        }
            
        // 종료 조건, 가장 마지막 버스에 도착
        if(i == n - 1) {
            // 버스에 자리가 남을 경우, 버스 도착 시간에 도착하면 된다.
            if(passenger < m) {
                answer_time = bus_time;
            }
            // 버스에 자리가 없을 경우 가장 마지막 사람보다 1분 더 일찍 도착하면 된다.
            else {
                answer_time = crew_times[index - 1] - 1;
            }
        }
        
        bus_time += t;
    }
    
    return convert_to_time(answer_time);
}

int convert_to_min(const string& time) {
    int hour = stoi(time.substr(0, 2));
    int min = stoi(time.substr(3, 2));
    
    return hour * 60 + min;
}
              
string convert_to_time(int min) {
    int hour = min / 60;
    int mins = min % 60;
    
    char temp[6];
    sprintf(temp, "%02d:%02d", hour, mins);
    return string(temp);
}