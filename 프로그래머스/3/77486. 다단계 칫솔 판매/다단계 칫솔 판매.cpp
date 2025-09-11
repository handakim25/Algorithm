#include <string>
#include <vector>
#include <unordered_map>

// 분배 규칙 : 이득 배분 시에 이득의 10%를 추천인에게 배분
// 하위 추천인에게서 얻은 이득까지 포함해서 상위 추천인에게 배분
// 원 단위 절삭, 1원 미만인 경우 분배하지 않음

// enroll : 판매원 이름, 조직에 참여한 순서
// referral : 추천인 이름, 판매원 i번째의 추천인의 이름은 i번째이다. -가 기입될 경우 추천인이 없는 상태, center를 기준으로 한다.
// seller : 판매원 이름
// amount : 판매 수량, 1개 이익금은 100원
// result : enroll 순서대로 총 이익금을 반환

// 절삭의 단위가 한 번 판매를 기준으로 발생하므로 따로 모아서 계산하지 않고 각각의 이득금 발생을 추적해서 수행하면 된다.
// Center의 이득금은 필요 없다.

using namespace std;

void apply_profit(const string& seller, int profit, unordered_map<string, string>& person_referral_map, unordered_map<string, int>& person_profit_map);

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    int num = enroll.size();
    
    // key : person, value : referral
    unordered_map<string, string> person_referral_map;
    for(int i = 0; i < num; i++) {
        person_referral_map[enroll[i]] = referral[i];
    }
    
    // key : person, value : 이득금
    unordered_map<string, int> person_profit_map;
    
    for(int i = 0; i < seller.size(); i++) {
        int profit = amount[i] * 100;
        apply_profit(seller[i], profit, person_referral_map, person_profit_map);
    }

    vector<int> result(num);
    for(int i = 0; i < num; i++) {
        const string& name = enroll[i];
        result[i] = person_profit_map[name];
    }
    
    return result;
}

void apply_profit(const string& seller, int profit, unordered_map<string, string>& person_referral_map, unordered_map<string, int>& person_profit_map) {
    int referral_profit = profit / 10;
    int pure_profit = profit - referral_profit;
    
    person_profit_map[seller] += pure_profit;
    
    const string& referral = person_referral_map[seller];
    if(referral_profit > 0 && referral != "-") {
        apply_profit(referral, referral_profit, person_referral_map, person_profit_map);
    }
}