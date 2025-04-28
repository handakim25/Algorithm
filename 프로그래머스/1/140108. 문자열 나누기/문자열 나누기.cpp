#include <string>
#include <vector>

using namespace std;

int solution(string s) {
    int split_count = 0;
    int match_count = 0;
    char target_ch = ' ';
    for(const char ch : s) {
        if(target_ch == ' ') {
            target_ch = ch;
            match_count = 1;
            split_count++;
        }
        else {
            match_count += target_ch == ch ? 1 : -1;
            if(match_count == 0) {
                target_ch = ' ';
            }
        }
    }
    
    return split_count;
}