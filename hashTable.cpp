#include <iostream>
#include <list>
#include <vector>

#define MIN_CAPACITY 2
#define DEFAULT_LF 0.75

// Uses sequence chaining
class HashTable {   
    int capacity;
    double loadFactor;
    int size;
    std::vector<std::list<int> > table;
    
    int hash(int key) {
        return key % capacity;
    }

    std::list<int>::iterator search(int key) {
        int h = hash(key);
        return find(table[h].begin(), table[h].end(), key);
    }

    void rehash() {
        size = 0;
        capacity = std::max(MIN_CAPACITY, capacity);

        std::vector<std::list<int> > old(std::move(table));
        table = std::vector<std::list<int> > (capacity);

        for(int i = 0; i < old.size(); i++) {
            for(auto it : old[i]) {
                add(it);
            }
        }
    }

public:

    HashTable() {
        loadFactor = DEFAULT_LF;
        capacity = MIN_CAPACITY;
        table = std::vector<std::list<int> > (capacity);
        size = 0;
    }

    void add(int key) {
        if (contains(key)) return;
    
        int h = hash(key);
        size++;
        table[h].push_back(key);

        if (size >= loadFactor * capacity) {
            capacity *= 2;
            rehash();
        }
    }

    void remove(int key) {
        int h = hash(key);

        if (search(key) == table[h].end()) return;

        size--;
        table[h].erase(search(key));

        if (size <= loadFactor * capacity/2) {
            capacity /= 2;
            rehash();
        }
    }

    bool contains(int key) {
        int h = hash(key);
        return (search(key) != table[h].end());
    }
};

int main(void) {

    HashTable ht;
    ht.add(5);

    std::cout << ht.contains(5) << ht.contains(3) << std::endl;
    return 0; 
}