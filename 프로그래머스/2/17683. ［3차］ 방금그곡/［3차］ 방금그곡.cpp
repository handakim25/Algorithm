#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

// 음악 제목, 재생 시각, 악보가 주어짐
// 음은 12개
// 1분에 하나의 음이 재생, 재생 시간이 넘을 경우 반복 재생
// 00:00까지 재생
// 조건 중에서 제일 긴 음악을 반환, 재생 시간도 같을 경우 먼저 입력된 제목 반환
// 없을 경우 None

// musicinfos : 시작 시간, 끝난 시간, 음악 제목, 악보 정보
// m : 음
// 각각의 배열에서 같은 것이 있는지 파악되지 않을까?
// 조건 중에서 제일 긴 음악을 반환해야 하므로 해당 되는 조건들을 찾고 정렬이 필요하다.
// 먼저 입력된 제목을 반환해야 하므로 stable sort가 필요

// 이 문제는 문자열의 포함여부를 찾는 것이므로 find를 구현하거나 아니면 find를 이용하는 것이다.
// 첫번째 해결책으로는 #을 변형시키는 것이다. C#을 c, D#을 d, F#을 f, 이런 식으로 치환을 하면 find 알고리즘을 사용할 수 있다.
// 두번째 해결책으로는 find를 자체적으로 구현하는 것이다.
// 아니면 TRIE를 이용?
// 일단은 가장 쉬운 첫번째 방법을 이용하도록 한다.

using namespace std;

int to_minute(const string& time);
string convert_to_single_melody(const string& melody);
void parse_musicinfo(const string& musicinfo, string& start_time, string& end_time, string& music_name, string& melody);
bool is_include_melody(const string& melody, const string& music, int play_time);

string solution(string m, vector<string> musicinfos) {
    string find_str = convert_to_single_melody(m);
    
    // fix2. 가장 큰 값을 찾는 것은 정렬을 하는 것보다 루프 중에서 최대값을 찾는 것이 더 쉽다.
    pair<int, string> best_match = {-1, "(None)"};
    
    // 해당 되는 값들 찾기
    // first : length, second : music name
    vector<pair<int, string>> candidates;
    for(const string& musicinfo : musicinfos) {
        string start_time_str, end_time_str, music_name, melody;
        parse_musicinfo(musicinfo, start_time_str, end_time_str, music_name, melody);
        
        int start_time = to_minute(start_time_str);
        int end_time = to_minute(end_time_str);
        int play_time = end_time - start_time;
        
        melody = convert_to_single_melody(melody);
        
        // 원하는 값을 찾았을 경우
        if(is_include_melody(find_str, melody, play_time) 
          && play_time > best_match.first) {
            // fix1. 멜로디의 가장 긴 시간이 아니라 라디오의 재생에서 가장 긴 시간이었다.
            // 문제 조건을 구체적으로 명시화하고 의사 코드 작성할 때 해당 내용을 같이 적어둘 필요가 있다.
            // 원하는 값을 찾았을 경우 -> 설명적인 주석이고 필요 없다. 어떠한 값을 집어 넣는지가 여기서는 문제 포인트였다.
            best_match = {play_time, music_name};
        }
    }
    
    return best_match.second;
}

int to_minute(const string& time) {
    string hour = time.substr(0, 2);
    string min = time.substr(3, 2);
    return stoi(hour) * 60 + stoi(min);
}

// C, C#->c
// D, D#->d
// E
// F, F#->f
// G, G#->g
// A, A#->a
// B
string convert_to_single_melody(const string& melody) {
    string result;
    
    for(int i = 0; i < melody.length(); i++) {
        if(i + 1 < melody.length() && melody[i + 1] == '#') {
            result.push_back(tolower(melody[i]));
            i++;
        }
        else {
            result.push_back(melody[i]);
        }
    }
    
    return result;
}

void parse_musicinfo(const string& musicinfo, string& start_time, string& end_time, string& music_name, string& melody) {
    string token;
    vector<string> tokens;
    stringstream ss(musicinfo);
    
    while(getline(ss, token, ',')) {
        if(!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    start_time = tokens[0];
    end_time = tokens[1];
    music_name = tokens[2];
    melody = tokens[3];
}

bool is_include_melody(const string& melody, const string& music, int play_time) {
    size_t music_length = music.length();
    
    
    for(int i = 0; i < play_time; i++) {
        bool match = true;
        for(int j = 0; j < melody.length(); ++j) {
            int index = (i + j) % music_length;
            if(music[index] != melody[j]) {
                match = false;
                break;
            }
        }
        
        if(match) {
            return true;
        }
    }
    
    return false;
}