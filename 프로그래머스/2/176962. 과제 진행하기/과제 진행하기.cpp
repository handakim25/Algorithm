#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

// 구현 문제로 추정
// 새로운 과제가 들어왔을 경우 항상 새로운 과제를 수행
// 과제 종료 시에 멈춘 과제가 있으면 가장 최근 과제부터 수행
// 가장 최근이므로 순서대로가 아니라 Stack 같은 구조를 이용
// 스케줄링 문제로 분류할 수 있을듯 하다. 스케줄링 문제를 하나의 유형으로 설정해서 정리해야 될 필요가 있다.

// 스케줄링 로직 설계
// for all task
// work time = task time - prev time
// process tasks in stack for work time
// push current task to stack
// update time
// 
// pop all tasks from stack

using namespace std;

// return : 완료한 태스크 리스트
vector<string> process_task_in_stack(stack<pair<string, int>>& task_stack, int work_time);
// hh:mm -> min
int convert_time_to_min(const string& time);

vector<string> solution(vector<vector<string>> plans) {
    sort(plans.begin(), plans.end(), [](const vector<string>& planA, const vector<string>& planB) {
        return convert_time_to_min(planA[1]) < convert_time_to_min(planB[1]);
    });
    
    int time = 0; // min 단위
    vector<string> result;
    // first : subject name, second: remain time(minute)
    stack<pair<string, int>> task_stack;
    for(const vector<string>& plan : plans) {
        const string& subject_name = plan[0];
        int task_start_time = convert_time_to_min(plan[1]);
        int task_time = stoi(plan[2]);
        
        // stack을 처리한다.
        int work_time = task_start_time - time;
        vector<string> finish_task = process_task_in_stack(task_stack, work_time);
        result.insert(result.end(),
                      make_move_iterator(finish_task.begin()),
                      make_move_iterator(finish_task.end())
        );
        
        task_stack.push(make_pair(subject_name, task_time));
        time = task_start_time;
    }
    
    // pop all stack
    while(!task_stack.empty()) {
        pair<string, int>& task = task_stack.top();
        result.push_back(task.first);
        task_stack.pop();
    }
    
    return result;
}

vector<string> process_task_in_stack(stack<pair<string, int>>& task_stack, int work_time) {
    vector<string> result;
    
    while(!task_stack.empty() && work_time > 0) {
        pair<string, int>& task = task_stack.top();
        string& task_name = task.first;
        int remain_time = task.second;
        
        // work time이 충분하면 task가 종료,
        // work time이 부족하면 work time을 0으로 설정하고 task를 유지
        if(work_time >= remain_time) {
            work_time -= remain_time;
            result.push_back(task_name);
            task_stack.pop();
        }
        else {
            task.second -= work_time;
            work_time = 0;
        }
    }   
    return result;
}

int convert_time_to_min(const string& time) {
    string hour = time.substr(0, 2);
    string min = time.substr(3, 2);
    return stoi(hour) * 60 + stoi(min);
}