#include <iostream>
#include <vector>

using namespace std;

void hanoi(int n, int a, int b, vector<pair<int, int>>& result);

int main() {
    int n = 0;

    cin >> n;

    vector<pair<int, int>> result;
    hanoi(n, 1, 3, result);

    cout << result.size() << endl;
    for(auto [v1, v2] : result) {
        printf("%d %d\n", v1, v2);
    }
    
    return 0;
}

void hanoi(int n, int a, int b, vector<pair<int, int>>& result) {
    // base case) n == 1
    if(n == 1) {
        result.emplace_back(a, b);
        return;
    }

    int c = 6 - a - b;

    hanoi(n -1 , a, c, result);
    hanoi(1, a, b, result);
    hanoi(n - 1, c, b, result);
}