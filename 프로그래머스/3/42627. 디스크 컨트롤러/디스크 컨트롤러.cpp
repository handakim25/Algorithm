#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 단순 구현 문제 같은데?
// job : 번호, 요청 시각, 소요 시간
// priority : 소요 시간 <, 요청 시각 <, 번호 < : 따로 구현하기 귀찮으면 struct 쓰는게 나을듯
// 완료 시간과 요청 시간이 같을 경우 요청 시간의 job을 큐에 삽입
// 반환 시간 : 요청 시간 - 종료 시간, 처리하고 나면 반환 시간을 기록할 필요가 있다.
// 구조적으로 보면 job이 끝날 때까지, priority queue가 empty가 될 때까지 돌아야 할 필요가 있다.
// 그리고 현재 작업 시간을 기록해서 현재 job을 결정
// loop에 들어왔을 때는
// 1. job에서 현재 시간에 맞춰서 꺼내오기
// 2. priority queue가 비어 있을 경우 현재 시간을 job 시간만큼 당기기

struct Job {
    // 작업 번호
    int work_index;
    // 요청 시간
    int request_time;
    // 소요 시간
    int work_time;
    
    bool operator>(const Job& other_job) const {
        if(work_time == other_job.work_time)
        {
            if(request_time == other_job.request_time)
            {
                return work_index > other_job.work_index;
            }
            else
            {
                return request_time > other_job.request_time;
            }
        }
        return work_time > other_job.work_time;
    }
    
    bool operator<(const Job& other_job) const {
        if(work_time == other_job.work_time)
        {
            if(request_time == other_job.request_time)
            {
                return work_index < other_job.work_index;
            }
            else
            {
                return request_time < other_job.request_time;
            }
        }
        return work_time < other_job.work_time;
    }
};

Job parse_job(const vector<int>& data);
void print_job(const Job& job);

// job : 인덱스 = 작업 번호, job[0] = 요청 시각, job[1] = 소요 시간, 그러면 이거는 정렬이 되어 있는 건가?
int solution(vector<vector<int>> jobs) {
    int n = jobs.size();    
    
    vector<Job> job_list;
    for(int i = 0; i < jobs.size(); i++) {
        Job job = parse_job(jobs[i]);
        job.work_index = i;
        job_list.push_back(job);
    }
    sort(job_list.begin(), job_list.end(), [](const Job& jobA, const Job& jobB) {
        return jobA.request_time < jobB.request_time;
    });
    
    queue<Job> job_queue;
    for(Job job : job_list) {
        job_queue.push(job);
    }
    
    int total_turn_around_time = 0;
    int cur_time = 0;
    priority_queue<Job, vector<Job>, greater<Job>> pq;
    while(!pq.empty() || !job_queue.empty()) {
        // 현재 시간에 기반해서 pq에 삽입(request_time <= cur_time)
        // pq에 작업할 것이 없을 경우 cur time을 진행시키고 다음 큐의 내용물을 삽입
        // pq에 작업할 것이 없고 job_queue가 없을 경우는?
        while(!job_queue.empty()
             && job_queue.front().request_time <= cur_time)
        {
            pq.push(job_queue.front());
            job_queue.pop();
        }
        
        if(pq.empty()) {
            cur_time = job_queue.front().request_time;
            continue;
        }
        
        // pq에서 우선 순위가 가장 높은 것을 실행
        // - 현재 시간을 갱신
        // - turn around time을 계산하고 갱신
        Job job = pq.top();
        pq.pop();
        cur_time += job.work_time;
        int turn_around_time = cur_time - job.request_time;
        total_turn_around_time += turn_around_time;
    }    
    
    return total_turn_around_time / n;
}


// data : [요청 시간, 작업 종료 시간]
Job parse_job(const vector<int>& data) {
    Job result;
    result.request_time = data[0];
    result.work_time = data[1];
    
    return result;
}