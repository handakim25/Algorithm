#include <iostream>
#include <vector>

// 전형적인 TRIE 알고리즘이다.
// TRIE 알고리즘의 경우 트리 구조로 이루어져 있고 숫자를 기준으로 Child를 연결하면 된다.
// 또한, 접두사 여부를 판단하기 위해 end 여부를 포함하고 있다.

using namespace std;

struct Node {
    vector<Node*> children; // 0~9, size : 10
    bool is_end;
    Node()
        : children(10, nullptr), is_end(false) {}
};

bool is_unique(const vector<string>& data);
bool insert_to_trie(Node* root, const string& word);

int main() {
    int test_count;
    cin >> test_count;

    for(int i =  0; i < test_count; i++) {
        int input_count;
        cin >> input_count;
        
        vector<string> data_list(input_count);
        for(string& input : data_list) {
            cin >> input;
        }

       cout << (is_unique(data_list) ? "YES" : "NO") << endl;
    }
    
    return 0;
}

bool is_unique(const vector<string>& data_list) {
    Node* head = new Node();
    for(const string& data : data_list) {
        if(!insert_to_trie(head, data)) {
            return false;
        }
    }
    
    return true;
}

bool insert_to_trie(Node* head, const string& word) {
    Node* node = head;
    for(char ch : word) {
        int num = ch - '0';
        if(node->children[num] == nullptr) {
            node->children[num] = new Node();
        }
        node = node->children[num];
        
        if(node->is_end) {
            return false;
        }
    }
    
    for (const Node* child : node->children) {
        if (child != nullptr) {
            return false;
        }
    }

    node->is_end = true;
    
    return true;
}