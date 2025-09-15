#include <string>
#include <vector>
#include <limits>

// 정수로 표현되는 교점을 찾은 다음에 출력

using namespace std;

// intersection은 2차원 평면 상에 존재하는 좌표로 구한다.
vector<pair<long, long>> get_all_intersections(const vector<vector<int>>& lines);
bool get_intersection(const vector<int>& lineA, const vector<int>& lineB, pair<long, long>& out_line);
vector<string> draw_intersections(const vector<pair<long, long>>& intersections);

vector<string> solution(vector<vector<int>> line) {
    vector<pair<long, long>> intersections = get_all_intersections(line);    
    
    return draw_intersections(intersections);
}

vector<pair<long, long>> get_all_intersections(const vector<vector<int>>& lines) {
    vector<pair<long, long>> result;
    
    for(int i = 0; i < lines.size(); i++) {
        for(int j = i + 1; j < lines.size(); j++) {
            const vector<int>& lineA = lines[i];
            const vector<int>& lineB = lines[j];
            
            // 평행하지 않고, 정수 점이어야 한다.
            pair<long, long> out_line;
            if(get_intersection(lineA, lineB, out_line)) {
                result.push_back(out_line);
            }
        }
    }
    
    return result;
}

bool get_intersection(const vector<int>& lineA, const vector<int>& lineB, pair<long, long>& out_line) {
    long A = lineA[0];
    long B = lineA[1];
    long E = lineA[2];
    long C = lineB[0];
    long D = lineB[1];
    long F = lineB[2];
    
    long denominator = A * D - B * C;
    if(denominator == 0) {
        return false;
    }
    
    long x_numerator = B * F - E * D;
    long y_numerator = E * C - A * F;
    
    if( x_numerator % denominator != 0 || y_numerator % denominator != 0) {
        return false;
    }
        
    out_line.first =  x_numerator / denominator;
    out_line.second = y_numerator / denominator;
    
    return true;
}

// 좌상, 좌하단, 우상, 우하단의 값을 구한다. x 값 중에서 가장 큰 값과 작은 값, y 값 중에서 가장 큰 값과 작은 값을 구한다.
vector<string> draw_intersections(const vector<pair<long, long>>& intersections) {
    long min_x = numeric_limits<long>::max();
    long max_x = numeric_limits<long>::min();
    long min_y = numeric_limits<long>::max();
    long max_y = numeric_limits<long>::min();
    
    for(auto [x, y] : intersections) {
        min_x = min(min_x, x);
        max_x = max(max_x, x);
        min_y = min(min_y, y);
        max_y = max(max_y , y);
    }
    
    // 좌상단 좌표가 0,0 기준이 된다.
    // x는 그대로 늘어나지만, y의 값의 경우 y축이 반전된다.
    // x, y 좌표가 반전되어서 들어가게 된다.
    long width = max_x - min_x + 1;
    long height = max_y - min_y + 1;
    long pivot_x = min_x;
    long pivot_y = max_y;
    
    vector<string> result(height, string(width, '.'));
    for(auto [x, y] : intersections) {
        
        long pos_x = x - pivot_x;
        long pos_y = - y + pivot_y;
        
        result[pos_y][pos_x] = '*';
    }
    
    return result;
}