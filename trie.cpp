#include <iostream>

/*
    TrieNode contains array of children
    isLeaf == true if it is end of a word
*/
class TrieNode {
public:

    TrieNode *arr[26];
    bool isLeaf;

    TrieNode(bool leaf) {
        for(int i = 0; i < 26; i++) {
            arr[i] = NULL;
        }
        isLeaf = leaf;
    }
};

class Trie {
    TrieNode *root;
public:

    // constructor
    Trie() {
        root = new TrieNode(false);
    }

    // insert string to trie
    void insert(std::string s) {

        TrieNode *curr = root;
        for(int i = 0; i < s.length(); i++) {
            int j = s[i] - 'a';

            if (curr->arr[j] == NULL) {
                bool isLeaf = (i == s.length() - 1);
                curr->arr[j] = new TrieNode(isLeaf);
            }

            curr = curr->arr[j];
        }
    }

    // search for given string in trie
    bool search(std::string s) {
        TrieNode *curr = root;
        for(int i = 0; i < s.length(); i++) {
            int j = s[i] - 'a';
            assert(j < 26);

            if (curr->arr[j] == NULL) return false;
            curr = curr->arr[j];
        }
        return curr->isLeaf;
    }
};

int main(void) {
    Trie t;
    t.insert("hello");
    std::cout << t.search("helloo") << t.search("hello");
}