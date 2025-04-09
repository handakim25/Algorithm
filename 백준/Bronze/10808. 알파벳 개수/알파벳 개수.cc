#include <iostream>
#include <vector>

using namespace std;

int main() {
    string input;
    cin >> input;

    int alphabet_count = 'z' - 'a' + 1;
    vector<int> freq(alphabet_count);
    for(char ch : input) {
        freq[ch - 'a']++;
    }

    for(int i = 0; i < alphabet_count; i++) {
        cout << freq[i] << " ";
    }

    return 0;
}