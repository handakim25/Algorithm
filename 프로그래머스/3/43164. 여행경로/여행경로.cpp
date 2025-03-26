#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

// adj list를 이용해서 그래프 표현
// - 비가중치 방향 그래프

// 탐색
// - dfs를 이용해서 방문
// - 항공권을 모두 사용 -> 모든 노드를 방문, 방문 여부를 저장해야 한다.
// - 알파벳 순서가 앞서는 경로를 선택

// fix. 중복 티켓 문제 해결이 필요, 방문 여부를 판단하는 것이 아니라 남은 티켓의 개수를 기준으로 판단해야 한다.
// 문제가 바뀌어서 weight graph와 유사하게 되었다.

class TravelPath
{
public:
    TravelPath() {}
    void AddEdge(const string& from, const string& to);
    vector<string> FindTravelPath(const string& start);
    
protected:
    void CalculatePath(vector<string>& path, string node);
    
private:
    int edge_count = 0;
    map<string, map<string, int>> _AdjList;
    vector<string> result;
};

void TravelPath::AddEdge(const string& from, const string& to)
{
    _AdjList[from][to]++;
    edge_count++;
}

vector<string> TravelPath::FindTravelPath(const string& start)
{  
    vector<string> path = {start};
    CalculatePath(path, start);
    
    return result;
}

void TravelPath::CalculatePath(vector<string>& path, string node)
{
    if(path.size() == edge_count + 1)
    {
        if(result.empty() || path < result)
        {
            result = path;
        }
        return;
    }
    
    for(auto& [neighbor, tickets] : _AdjList[node])
    {
        if(_AdjList[node][neighbor] > 0)
        {
            _AdjList[node][neighbor]--;
            path.push_back(neighbor);
            CalculatePath(path, neighbor);
            _AdjList[node][neighbor]++;
            path.pop_back();
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    TravelPath path;
    for(const vector<string>& ticket : tickets)
    {
        const string& from = ticket[0];
        const string& to = ticket[1];
        path.AddEdge(from, to);        
    }
    
    return path.FindTravelPath("ICN");
}