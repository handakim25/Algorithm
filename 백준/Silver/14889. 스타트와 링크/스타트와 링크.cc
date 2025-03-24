#include <iostream>
#include <vector>
#include <limits>

// 완전 탐색
// N개 중에서 2개의 팀을 나누는 방법은 N / 2개를 선택하는 것과 같다. N / 2개를 선택하게 되면 나머지 팀은 결정된다.
// 반대편 N / 2를 선택할 수도 있지만 현재는 고려하지 않는다.
// N / 2개를 고르는 방법을 고려하면
// 1. N개의 순열을 생성하기
// 2. DFS 식으로 구하기
// 2-1. 6개를 고르면 종료
// 2-2. 원소는 유일하다. 즉, 이전에 1, 2를 고르면 이후에 1, 2를 고를 수 없다.
// 2-3. 순서는 고려하지 않는다. 1-2-3 를 고를 경우 1-3-2를 고르면 안 된다. 선택에 지향성을 가지게 함으로써 순서를 배제할 수 있다.

// 팀 파워 계산
// 임의의 하나를 선택했을 때 나머지 원소들과의 파워를 더하면 된다.
// a, b가 있을 경우 c가 더해지면 (a, c), (b, c), (c, a), (c, b)가 더해진다.

// 팀 파워 차이 계산
// 0번째 팀 조합의 반대는 n번째 팀 조합
// 1번째 팀 조합의 반대는 n - 1번째 팀의 조합이다.
// 이를 이용하면 차이를 계산할 수 있다.

using namespace std;

void permutate_team_list(vector<int>& team, int start, int team_size, vector<vector<int>>& out_team_powers);
int calculate_team_power(const vector<int>& team, const vector<vector<int>> team_pair_power);

int main() {
    int num = 0;
    cin >> num;
    
    vector<vector<int>> team_pair_power(num, vector<int>(num));
    for(int row = 0; row < num; row++) {
        for(int col = 0; col < num; col++) {
            cin >> team_pair_power[row][col];
        }
    }

    vector<int> team;
    vector<vector<int>> team_list;
    permutate_team_list(team, 0, num, team_list);

    vector<int> team_powers;
    for(const vector<int>& team : team_list) {
        int power = calculate_team_power(team, team_pair_power);
        team_powers.push_back(power);
    }

    int min_power = numeric_limits<int>::max();
    for(int i = 0; i < team_powers.size() / 2; i++) {
        int powerA = team_powers[i];
        int powerB = team_powers[team_powers.size() - i - 1];
        int power_diff = abs(powerA - powerB);
        min_power = min(min_power, power_diff);
    }

    cout << min_power << endl;
    
    return 0;
}

// start : start 순서부터 팀에 들어간다.
// pre-condition : start 이전의 팀원들은 이미 고려됨
void permutate_team_list(vector<int>& team, int start, int team_size, vector<vector<int>>& out_team_powers) {
    if(team.size() >= team_size / 2) {
        out_team_powers.push_back(team);
        return;
    }

    for(int i = start; i < team_size; i++) {
        team.push_back(i);
        permutate_team_list(team, i + 1, team_size, out_team_powers);
        team.pop_back();
    }
}

int calculate_team_power(const vector<int>& team, const vector<vector<int>> team_pair_power) {
    int total_power = 0;
    for(int i = 0; i < team.size(); i++) {
        for(int j = 0; j < team.size(); j++) {
            total_power += team_pair_power[team[i]][team[j]];
        }
    }

    return total_power;
}