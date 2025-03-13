#include <string>
#include <vector>
#include <queue>

using namespace std;

// 범위가 있고 거기서 최대 효율로 무적권을 사용하면 된다.
// 그러니까 도중에 모자르게 되면 기존 것들 제일 많이 소모한 라운드를 무적권을 소모해서 롤백하면 된다.

// n : 병사 수, k : 무적권의 개수, enemy : round 별 enemy의 수
int solution(int n, int k, vector<int> enemy) {
    priority_queue<int> pq;
    int round = 0;
    
    for(int e : enemy) {
        n -= e;
        pq.push(e);
        
        if(n < 0) {
            if(k > 0) {
                n += pq.top();
                pq.pop();
                k--;
            }
            else {
                break;
            }
        }
        
        round++;
    }
    
    return round;
}