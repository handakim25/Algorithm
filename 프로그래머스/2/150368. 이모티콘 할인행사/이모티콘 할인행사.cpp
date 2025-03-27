#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

// users : 구매 기준 : n개
// [비율, 가격]
// 일정 비율 이상 할인하는 이모티콘 모두 구매
// 가격 이상 구매하면 이모티콘 플러스 가입
// emoticons : 정가 : m개
// 10%, 20%, 30%, 40% 할인률 가능
// 이모티콘 플러스 가입자를 최대한 늘리는 부분은 매출을 최대한 늘리는 것과 관계가 있다.
// 판매액을 최대한 늘리는 것은 1. 조건을 만족한 시점에서 할인률을 최소화하는 것이다.

// 1. 완전 탐색, 이모티콘의 모든 할인률을 적용해서 계산하면 이모티콘, 사용자로 O(n^2) 구현이 가능하다.
// 2. 각 사람 별로 해서 공통 할인률을 찾는 것은 어려운 것이 한 사람을 기준으로 이모티콘 플러스 가입이 가능해도 다른 사람으로는 안 될 수 있다. 왜냐하면 할인률이 늘어나게 되면 다른 사람의 구매 비용이 줄어들기 때문이다.

// 완전 탐색이란 것은 결국은 나열이란 것이고 어느 것을 기준으로 나열을 해야 되나면 할인율 기준으로 나열을 실행하면 된다.
// 각 계산 state를 저장하고 계산 state를 기반으로 current를 update하면 될 것 같다.

// 완전 탐색 dfs 알고리즘
// - current state : 가격만 기록하면 될 것 같은데 나중에 total 가격에서 이모티콘 플러스 여부만 판단하면 될 것 같다.
// - current emoticon : 현재 emoticon
// - context users
// - context emoticons
// - result(output) : price, plus 가입자 수 2개가 필요
// permutate한 결과를 하나씩 저장하기에는 용량이 너무 큰 문제가 있다. 어쩔 수 없이 dfs 종료 시에 evaluate를 진행한다.
// fix. current_prices -> accumulated_prices : 현재 자체의 가격이라기 보다는 가격의 합산이므로 변수의 이름을 변경
void permutate_emoticon(vector<int>& accmulated_prices, int depth, const vector<vector<int>>& users, const vector<int>& emoticons, int& out_price, int& out_plus_count);
// pair first : total plus count, second : total price
pair<int, int> evaluate_emoticon_purchase(const vector<int>& prices, const vector<vector<int>>& users);
int try_purchase_emoticon(const vector<int>& user, int discount_rate, int discount_price);

const int discount_rates[] = {10, 20, 30, 40};
const int discount_count = 4;

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> accmulated_prices(users.size(), 0);
    int price = 0;
    int plus_count = 0; // fix2. 구매 횟수는 0이 최소이므로 0으로 초기화
    
    permutate_emoticon(accmulated_prices, 0, users, emoticons, price, plus_count);
    
    return {plus_count, price};
}

void permutate_emoticon(vector<int>& accmulated_prices, int depth, const vector<vector<int>>& users, const vector<int>& emoticons, int& out_price, int& out_plus_count) {
    // base case : 모든 이모티콘을 나열햇을 경우
    if(depth >= emoticons.size()) {
        pair<int, int> plus_price = evaluate_emoticon_purchase(accmulated_prices, users);
        int plus_count = plus_price.first;
        int price = plus_price.second;
        
        if(plus_count > out_plus_count) {
            out_plus_count = plus_count;
            out_price = price;
        }
        else if(plus_count == out_plus_count) {
            out_price = max(out_price, price);
        }
        
        return;
    }
    
    for(int i = 0; i < discount_count; i++) {
        int discount = discount_rates[i];
        int discount_price = emoticons[depth] * (100 - discount) / 100;
        
        for(int j = 0; j < users.size(); j++) {
            accmulated_prices[j] += try_purchase_emoticon(users[j], discount, discount_price);
        }
        permutate_emoticon(accmulated_prices, depth + 1, users, emoticons, out_price, out_plus_count);
        for(int j = 0; j < users.size(); j++) {
            accmulated_prices[j] -= try_purchase_emoticon(users[j], discount, discount_price);
        }
    }
}

// 일정 가격 이상이면 plus 가입, 미만일 경우 그대로 계산
pair<int, int> evaluate_emoticon_purchase(const vector<int>& prices, const vector<vector<int>>& users) {
    int total_plus_count = 0;
    int total_price = 0;
    
    for(int i = 0; i < users.size(); i++) {
        const vector<int>& user = users[i];
        const int user_plus_threshold = user[1];
        const int user_purchase_price = prices[i];
        
        if(user_purchase_price >= user_plus_threshold) {
            total_plus_count++;
        }
        else {
            total_price += user_purchase_price;
        }
    }
    
    return {total_plus_count, total_price};
}

// discount rate가 일정 이상이면 구매 아닐 경우 구매하지 않음
int try_purchase_emoticon(const vector<int>& user, int discount_rate, int discount_price) {
    const int user_discount_threshold = user[0];
    // fix3. if문은 삼항 연산자로 줄일 수 있다.
    return discount_rate >= user_discount_threshold ? discount_price : 0;
}