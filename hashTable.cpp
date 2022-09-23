/*
 *   Hash Table that uses key-value pairs, wheres key == int, value == string
 *   Compile using "g++ -std=c++11 -stdlib=libc++ hashTable.cpp" + "./a.out"
 */
#include <iostream>
#include <list>
#include <cstring>

class HashTable {
    private:
        // const number of lists
        static const int hashGroups = 10;
        std::list<std::pair<int, std::string> > table[hashGroups]; 
    
    public:
        bool isEmpty(); 
        int hashFunction(int key); // fetch value at key
        void insertItem(int key, std::string value); // insert key-val pair
        void removeItem(int key);
        void printTable();

};

// will return true if every list in table has size 0
bool HashTable::isEmpty() {
    int sum = 0;
    for(int i = 0; i < hashGroups; i++) {
        sum += table[i].size();
    }

    return (!sum); 
}

// returns index of given key
int HashTable::hashFunction(int key) {
    return key % hashGroups; // Key: 905 will return 5, which is the 6th list in the table.
}

// adds key value pair to tables
void HashTable::insertItem(int key, std::string value) {
    int hashValue = hashFunction(key);

    // point to list at given index
    auto& cell = table[hashValue]; 
    auto bgn = begin(cell);
    bool keyExists = false;

    for(; bgn != end(cell); bgn++) {
        if (bgn->first == key) {
            keyExists = true;
            bgn->second = value;
            std::cout << "Key exists, value has been replaced!" << '\n';
            break;
        }
    }

    if (!keyExists) {
        cell.emplace_back(key,value);
    }
    return;
}

void HashTable::removeItem(int key) {
    int hashValue = hashFunction(key);

    auto&cell = table[hashValue];
    auto bgn = begin(cell);
    bool keyExists = false;

    for(; bgn != end(cell); bgn++) {
        if (bgn->first == key) {
            keyExists = true;
            bgn = cell.erase(bgn); // returns iterator to next 
            break;
        }
    }

    if (!keyExists) std::cout << "ERR: Key does not exist in table!\n" << '\n';
    return;
}

void HashTable::printTable() {
    for (int i = 0; i < hashGroups; i++) {
        if (table[i].size() == 0) continue;

        auto bgn = table[i].begin();
        for(; bgn != table[i].end(); i++) {
            std::cout << "Key :" << bgn->first << " Value: " << bgn->second << '\n';
        }
    }

    return;
}

// stesting
int main(void) {
    HashTable HT;

    if (HT.isEmpty()) {
        std::cout << "empty!" << std::endl;
    }

    return 0;
}