#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// 소인수 문제인가?
// Array A에서 최대 a를 구하고 Array B에서 최대 a를 구하고 두 값 중 최대 값을 구하면 된다.
// 모든 숫자를 나눌 수 있다는 것은 최대 공약수인 것이다.
// 최대 공약수들 중에서 약수들이 모든 숫자를 나눌 수 있는 숫자의 후보군이 되고
// 해당 약수들을 다른 배열에 비교를 하게 되면 나눌 수 있는지 확인할 수 있게 된다.

int gcd(int a, int b);
int CalculateBiggestA(vector<int>& divideable, vector<int>& not_divideable);
vector<int> CalculateDivisors(int n);

int solution(vector<int> arrayA, vector<int> arrayB) {
    int largestA = CalculateBiggestA(arrayA, arrayB);
    int largestB = CalculateBiggestA(arrayB, arrayA);
    
    return largestA > largestB ? largestA : largestB;
}

int gcd(int a, int b) {
    while(b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int CalculateBiggestA(vector<int>& divideable, vector<int>& not_divideable) {
    // Group A의 최대 공약수 구하기
    int gcdA = divideable.front();
    for(int num : divideable) {
        gcdA = gcd(num, gcdA);
    }
    
    // 최대 공약수의 약수가 후보가 된다.
    vector<int> candidates = CalculateDivisors(gcdA);
    int largest_a = 0;
    for(int candidate : candidates) {
        bool is_valid = true;
        for(int n : not_divideable) {
            if(n % candidate == 0) {
                is_valid = false;
                break;
            }
        }
        
        if(is_valid) {
            largest_a = max(largest_a, candidate);
        }
    }
    
    return largest_a;
}

vector<int> CalculateDivisors(int n) {
    vector<int> divisors;
    
    for(int i = 1; i * i <= n; i++) {
        if(n % i == 0) {
            divisors.push_back(i);
            if(i != n / i ) {
                divisors.push_back(n / i);
            }
        }
    }
    
    return divisors;
}