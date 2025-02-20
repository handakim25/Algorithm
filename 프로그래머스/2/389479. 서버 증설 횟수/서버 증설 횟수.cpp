#include <string>
#include <vector>
#include <queue>
#include <iostream>

// 단순 구현 문제로 파악한다.
// 매 시간마다 현재 서버 개수, 필요 개수를 계산, 필요하면 증설한다.
// 결과값은 증설한 개수이다.
// 증설해서 유지 시간은 항상 같으므로 먼저 증설한 서버가 먼저 종료된다. 이를 따르면 큐의 구조라고 할 수 수 있다.

using namespace std;

void close_expired_server(int cur_time, queue<int>& servers);

int solution(vector<int> players, int m, int k) {
    // int : Server 만료 시간
    int count = 0;
    queue<int> servers;
    for(int time = 0; time < 24; time++) {
        // 현재 가능 서버 개수 확인
        close_expired_server(time, servers);
        
        // 현재 필요한 서버 개수 확인
        // [0, n) : 0, [n, 2n) : 1, ...
        int required_server_count = players[time] / m;
        
        
        // 서버 증가 및 count 기록
        if(required_server_count > servers.size()) {
            int scale_out_servers_count = required_server_count - servers.size();
            for(int i = 0; i < scale_out_servers_count; i++) {
                // k = 5, 2시에 시작하면 6~7에서 종료, 7이 시작할 때 종료
                servers.push(time + k);
            }
            
            count += scale_out_servers_count;
        }
    }
    
    return count;
}

void close_expired_server(int cur_time, queue<int>& servers) {
    while(!servers.empty() && servers.front() <= cur_time) {
        servers.pop();
    }
}