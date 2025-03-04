#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 아이디어 : s의 길이가 크지 않으므로 모든 경우의 수를 센다.
// 절반 이상으로는 압축이 되지 않으므로 절반까지 센다.

int calculate_compress_len(const string& s, int compress_len);

int solution(string s) {
    if(s.length() == 1) {
        return 1;
    }
    
    int len = s.length();
    int min_len = 1001;
    for(int i = 1; i < len; i++) {
        int compress_len = calculate_compress_len(s, i);
        min_len = min(min_len, compress_len);
    }
    
    return min_len;
}

int calculate_compress_len(const string& s, int compress_len) {
    // Fix. Split 과정을 제거하고 한 번에 처리하도록 변경
//     vector<string> split;
//     for(int i = 0; i < s.length(); i += compress_len) {
//         split.push_back(s.substr(i, compress_len));
//     }
    
//     string result;
//     for(int i = 0; i < split.size(); i++) {
//         int j = 0;
//         while(i + j < split.size() && split[i] == split[i + j]) {
//             j++;
//         }
        
//         if(j == 1) {
//             result += split[i];
//         }
//         else {
//             result += (to_string(j) + split[i]);    
//         }
        
//         i = i + j - 1;
//     }
    
//     return result.length();
    
    string result;
    
    for(int i = 0; i < s.length();) {
        // Fix2. j란 모호한 변수명을 변경
        int match_index = 0;
        string token = s.substr(i, compress_len);
        while(i + match_index < s.length() && token == s.substr(i + match_index, compress_len)) {
            match_index += compress_len;
        }
        
        if(match_index == compress_len) {
            result += token;
        }
        else {
            result += (to_string(match_index / compress_len) + token);
        }
        
        i += match_index;
    }
    
    return result.length();
}