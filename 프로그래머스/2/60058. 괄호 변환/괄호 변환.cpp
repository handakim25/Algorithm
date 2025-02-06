#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 일단은 단순 구현 문제라고 생각한다.
// 전제 조건 : 괄호의 개수는 짝이 맞는다.
// step1. if p == empty return emtpy
// step2.
// 균형잡힌 괄호 문자열로 분리 : 괄호 개수만 판별을 해서 처음 쌍이 맞게 된다면 해당 괄호 부분이 더 이상 쪼갤 수 없는 u가 된다.
// step3.
// u가 올바를 경우 u를 출력
// step4.
// u가 올바를 않을 경우 올바른 문자열로 변형해서 출력
// 아이디어.
// 쪼개서 작동하므로 재귀함수를 이용하면 해결할 수 있다.
// output, pattern, start, end
// 기본적으로 쪼개고 합치는 과정이니까 merge sort와 유사한 구조를 가질 것 같다.
// 하지만, merge sort랑 다르게 쪼개지는 부분은 다르니까 이 부분은 quick sort의 pivot 구하는 부분이랑 유사하다.

string correct_parentheses(string pattern);
int partition(string& pattern, bool& is_correct);
string balanced_to_correct(const string& pattern);

string solution(string p) {
    return correct_parentheses(p);
}

string correct_parentheses(string pattern) {
    // step1
    if(pattern.empty()) {
        return "";
    }
    
    // step2
    bool is_correct;
    int find = partition(pattern, is_correct);
    string u = pattern.substr(0, find + 1);
    string v = pattern.substr(find + 1);
    
    // step3
    if(is_correct) {
        return u + correct_parentheses(v);
    }
    // step4
    else {
        return "(" + correct_parentheses(v) + ")" + balanced_to_correct(u);
    }
    return "";
}

// 균형잡힌 괄호 문자열로 분리, u는 더 이상 쪼갤 수 없다.
// return : 균형잡힌 문자열의 마지막 인덱스
int partition(string& pattern, bool& is_correct) {
    // 괄호 개수를 세어서 정확히 맞아 떨어지는 순간 쪼갤 수 없는 균형잡힌 괄호 문자열이다.
    int open_close_count = 0;
    // fix1. 조건식을 바로 대입하는 것은 가독성이 안 좋은 것 같아서 괄호를 이용하기로 했다.
    is_correct = (pattern[0] == '(');
    
    for(int i = 0; i < pattern.length(); i++) {
        if(pattern[i] == '(') {
            open_close_count++;
        }
        else {
            open_close_count--;
        }
        
        if(open_close_count == 0) {
            return i;
        }
    }
    
    return -1;
}

// 첫 문자와 마지막자를 제거하고 나머지 문자열의 괄호를 뒤집는다.
// 전제조건 : pattern : 더 이상 쪼갤 수 없는 균형잡힌 문자열(but, 올바르진 앟음)
string balanced_to_correct(const string& pattern) {
    // fix2. 공간을 미리 할당하는 방식으로 변경
    if(pattern.length() < 2) {
        return "";
    }
    
    string result(pattern.length() - 2, ' ');
    for(int i = 1; i < pattern.length() - 1; i++) {
        result[i - 1] = (pattern[i] == ')' ? '(' : ')');
    }
    
    return result;
}