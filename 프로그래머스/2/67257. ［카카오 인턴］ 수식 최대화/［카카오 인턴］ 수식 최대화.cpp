#include <string>
#include <map>
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// 아이디어
// 문제의 본질은 연산 식을 계산하는 문제이다.
// 모르고 들어갔을 경우는 좀 어려운데 결국은 파싱을 해서 해결하라는 문제로 보인다.
// 연산 문자는 3개이고 우선순위를 재설정하면 6개의 경우가 있으니까 해당 부분을 전부 고려해서 문제를 풀이하면 된다.
// 함수를 작성할 때 우선순위를 설정할 수 있게 해서 해결하면 된다.

// 수식을 계산하는 방법은 중위 표기를 후위 표기로 바꾼 다음에 stack에서 차례대로 계산을 하면 된다.
// 해당 알고리즘을 Shunting Yard Algorithm이라고 부르고 차량기지 알고리즘이라고 부른다.
// 참고 : https://ko.wikipedia.org/wiki/차량기지_알고리즘
// 알고리즘과는 상관 없지만 놀랍게도 다익스트라가 고안한 알고리즘이라고 한다.

// 아니면 단순하게 문자열 파싱하고 우선 순위가 높은 연산자부터 차례로 처리하면 되지 않을까?
// 이번은 연습을 위해서 일단은 차량 기지 알고리즘을 구현하도록 한다.

vector<string> infix_to_postfix(const string& expression, map<char,int>& precedence);
// 나눗셈이 없으므로 실수는 결과값에 없다.
long long evaluate_postfix(const vector<string>& postfix_expression);

long long solution(string expression) {
    map<char, int> precedence;
    char operators[] = {'+', '-', '*'};
    int operator_precedences[] = {1, 2, 3};
    sort(operator_precedences, operator_precedences + 3);
    
    long long max_val = numeric_limits<long long>::min();
    do {
        for(int i = 0; i < 3; i++) {
            precedence[operators[i]] = operator_precedences[i];
        }
        
        vector<string> postfix = infix_to_postfix(expression, precedence);
        
        long long eval = abs(evaluate_postfix(postfix));
        max_val = max(max_val, eval);
    }while(next_permutation(operator_precedences, operator_precedences + 3));
    
    return max_val;
}

// 차량 기지 알고리즘을 이용해서 후위 표기로 변경한다.
// 출력, 연산자 스택이 필요하고 숫자는 출력으로 보내고 연산자 스택은 규칙에 따라서 스택에 넣는다.
// 1. 스택이 비워있을 경우 스택에 연산자를 넣는다.
// 2. 새로운 연산자가 우선 순위가 높거나 같을 경우 스택의 연산자를 출력으로 보낸다. 이를 반복한다. 그 후에 연산자를 연산자 스택에 넣는다.
vector<string> infix_to_postfix(const string& expression, map<char, int>& precedence) {
    vector<string> output;
    stack<char> operator_stack;
    string number_buffer;
    
    for(int i = 0; i < expression.size(); i++) {
        char current_char = expression[i];
        
        // 숫자인 경우 buffer에 넣은다.
        if(isdigit(current_char)) {
            number_buffer += current_char;
        }
        // 연산자일 경우
        else {
            // 이전 입력의 숫자가 있을 경우 처리한다.
            if(!number_buffer.empty()) {
                output.push_back(number_buffer);
                number_buffer.clear();
            }
            
            // 연산자 우선 순위가 같거나 높은 연산자들을 출력으로 보낸다.
            while(!operator_stack.empty() && precedence[operator_stack.top()] >= precedence[current_char]) {
                output.push_back(string(1, operator_stack.top()));
                operator_stack.pop();
            }
            operator_stack.push(current_char);
        }
    }
    
    // 숫자로 끝나므로 숫자에 가장 마지막 수가 버퍼에 남아있다. 해당 값을 출력
    if(!number_buffer.empty()) {
        output.push_back(number_buffer);
    }
    
    // 남은 연산자 출력
    while(!operator_stack.empty()) {
        output.push_back(string(1, operator_stack.top()));
        operator_stack.pop();
    }
    
    return output;
}

// 후위 표기식을 이용하는 것은 Stack을 이용하면 계산할 수 있다.
long long evaluate_postfix(const vector<string>& postfix_expression) {
    stack<long long> eval_stack;
    
    for(const string& token : postfix_expression) {
        // 숫자일 경우 stack에 집어넣는다.
        if(isdigit(token[0])) {
            eval_stack.push(stoi(token));
        }
        // 연산자일 경우 제일 위의 2개에 연산을 하고 다시 집어 넣는다.
        else {
            // Fix1. -, /와 같이 순서가 중요한 연산자가 있다.
            // 가장 뒤에 것이 - 대상이 되어야 하므로 처음 나온 것이 b, 그 뒤에 나온 것이 a가 된다.
            long long b = eval_stack.top();
            eval_stack.pop();
            long long a = eval_stack.top();
            eval_stack.pop();
            long long result = 0;
            
            switch(token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '-':
                    result = a - b;
                    break;
            }
            eval_stack.push(result);
        }
    }
    
    return eval_stack.top();
}