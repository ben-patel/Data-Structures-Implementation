#include <iostream>
#include <unordered_map>
using namespace std;

/* 
   Holds key value pairs
   Forms a doubly-linked list
*/
class Node {
public:
    int Val;
    int Key;    
    Node *next;
    Node *prev;

    Node(int key, int val) {
        Key = key, Val = val;
        next = NULL, prev = NULL;
    }
};

/* 
    LRU Cache class, stores K-V pairs and discards 
    least recently used element when max capacity is reached 
*/
class LRUCache {
public:
    LRUCache(int capacity) {
        Capacity = capacity;
        left = new Node(0,0);
        right = new Node(0,0);

        left->next = right, right->prev = left;
    }

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            remove(cache[key]);
            insertEnd(cache[key]);
            return cache[key]->Val;
        }

        return -1;
    }

    void put(int key, int val) {
        if (cache.find(key) != cache.end()) {
            remove(cache[key]);
        }
        cache[key] = new Node(key,val);
        insertEnd(cache[key]);

        if (cache.size() > Capacity) {
            Node *lru = left->next;
            remove(left);
            cache.erase(lru->Key);
        }
    }

private:

    int Capacity;
    Node *left;
    Node *right;
    unordered_map<int, Node*> cache;

    void remove(Node *ptr) {
        Node *prev = ptr->prev;
        Node *next = ptr->next;

        prev->next = next;
        next->prev = prev;

        free(ptr);
    }

    void insertEnd(Node *ptr) {
        Node *prev = right->prev;
        Node *next = right;

        prev->next = ptr;
        next->prev = ptr;
        ptr->next = next;
        ptr->prev = prev;
    }


};
int main(void) {

    LRUCache c(3);
    c.put(5,6);
    c.put(4,3);
    c.put(3,9);
    cout << c.get(3);
     
    return 0;
}